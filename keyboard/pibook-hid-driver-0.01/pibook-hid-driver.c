#include <linux/init.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>
#include <linux/moduleparam.h>
#include <linux/delay.h>

#include <asm/irq.h>
#include <asm/io.h>

#define DATA_PIN 4
#define POWER_PIN 17
#define BIT_DUR 504000
#define PIN_MAX 77

#define HIGH true
#define LOW false
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emil Schätzle");
MODULE_DESCRIPTION("Driver for the PI-Book keyboard");
MODULE_VERSION("0.01");

// Declare mouse_factor as a module parameter
static int mouse_factor = 15;
module_param(mouse_factor, int, 0644);
MODULE_PARM_DESC(mouse_factor, "Factor to scale the mouse movement.");

// List of keys in correct order
const int pin_to_key[] = {KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_DELETE, KEY_GRAVE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_CAPSLOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_LEFTSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT, KEY_LEFTCTRL, KEY_102ND, KEY_LEFTMETA, KEY_LEFTALT, KEY_SPACE, KEY_RIGHTALT, KEY_COMPOSE, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT};

int GPIO_IRQ;
ktime_t last;
bool receiving = false;
bool start_bit_handled = false;
int received_bits = 0;
bool bits[8];

static struct input_dev *input_device;

// Calculates the time since the last call
static int get_time_difference(void)
{
    long long int time;
    ktime_t now;
    now = ktime_get();
    time = ktime_to_ns(ktime_sub(now, last));
    last = now;
    if (time <= INT_MAX)
    {
        return time;
    }
    else
    {
        return -1;
    }
}
// Calculates the bit durations passed since last call
static int get_BIT_DURs(void)
{
    int time;
    int total_BIT_DURs;
    time = get_time_difference();
    if (time != -1)
    {
        total_BIT_DURs = (time + BIT_DUR / 2) / BIT_DUR;
        return total_BIT_DURs;
    }
    else
    {
        return -1;
    }
}
// Converts a received pin value to an LINUX Key Value
static int map_pin(int pin)
{
    if (pin >= 0 && pin <= PIN_MAX)
    {
        return pin_to_key[pin];
    }
    else
    {
        return -1;
    }
}
static void set_key_state(int key, int state)
{
    if (key != -1)
    {
        input_report_key(input_device, key, state);
    }
}
static void key_down(int pin)
{
    // printk(KERN_INFO "Keyboard: keydown\n");
    set_key_state(map_pin(pin), 1);
    input_sync(input_device);
}
static void key_up(int pin)
{
    // printk(KERN_INFO "Keyboard: keyup\n");
    set_key_state(map_pin(pin), 0);
    input_sync(input_device);
}
static void tilt_x(int x)
{
    // printk(KERN_INFO "Keyboard: rel_x %i\n", x);
    input_report_rel(input_device, REL_X, (x * mouse_factor) / 100);
    input_sync(input_device);
}
static void tilt_y(int y)
{
    // printk(KERN_INFO "Keyboard: rel_y %i\n", y);
    input_report_rel(input_device, REL_Y, (y * mouse_factor) / 100);
    input_sync(input_device);
}
static void data_received(void)
{
    int data = 0;
    data += 1 * bits[0];
    data += 2 * bits[1];
    data += 4 * bits[2];
    data += 8 * bits[3];
    data += 16 * bits[4];
    data += 32 * bits[5];
    data += 64 * bits[6];
    data += 128 * bits[7];
    // HANDLE RECEIVED DATA
    // printk(KERN_INFO "Keyboard: %i\n", data);

    if (data <= 77)
    {
        key_down(data);
    }
    else if (data <= 155)
    {
        key_up(data - 78);
    }
    else if (data == 156)
    {
        // printk(KERN_INFO "Keyboard: mouse button down\n");
        set_key_state(BTN_LEFT, 1);
        input_sync(input_device);
    }
    else if (data == 157)
    {
        // printk(KERN_INFO "Keyboard: mouse button up\n");
        set_key_state(BTN_LEFT, 0);
        input_sync(input_device);
    }
    else if (data <= 206)
    {
        tilt_x(data - 182);
    }
    else
    {
        tilt_y(data - 231);
    }
}
static void rising(void)
{
    if (receiving)
    {
        // Data is currently beeing received
        int i;
        int BIT_DURs;
        BIT_DURs = get_BIT_DURs();
        if (BIT_DURs != -1)
        {
            // printk(KERN_INFO "Keyboard: low for %i\n", BIT_DURs);
            // Ignore startbit
            if (!start_bit_handled && BIT_DURs > 0)
            {
                BIT_DURs--;
                start_bit_handled = true;
            }
            for (i = 0; i < BIT_DURs && i < 8; i++)
            {
                bits[received_bits + i] = false;
            }
            if (received_bits + BIT_DURs > 8)
            {
                // Error occured > abort receiving
                receiving = false;
                //printk(KERN_INFO "Keyboard: malicious byte\n");
            }
            else
            {
                received_bits += BIT_DURs;
                if (received_bits == 8)
                {
                    receiving = false;
                    data_received();
                }
            }
        }
    }
    else
    {
        // Not receiving, reset timer anyway
        last = ktime_get();
    }
}
static void falling(void)
{
    if (receiving)
    {
        // Data is currently beeing received
        int i;
        int BIT_DURs;
        BIT_DURs = get_BIT_DURs();
        if (BIT_DURs != -1)
        {
            //printk(KERN_INFO "Keyboard: high for %i\n", BIT_DURs);
            for (i = 0; i < BIT_DURs && i < 8; i++)
            {
                bits[received_bits + i] = true;
            }
            if (received_bits + BIT_DURs > 8)
            {
                // Error occured > abort receiving
                receiving = false;
                // printk(KERN_INFO "Keyboard: malicious byte\n");
            }
            else
            {
                received_bits += BIT_DURs;
                if (received_bits == 8)
                {
                    receiving = false;
                    data_received();
                }
            }
        }
    }
    else
    {
        // New transmission starts, thus reset clock
        last = ktime_get();
        receiving = true;
        received_bits = 0;
        start_bit_handled = false;
    }
}
static irqreturn_t interrupt(int irq, void *dev_id)
{
    // Is the interrupt a rising or a falling Edge?
    if (gpio_get_value(DATA_PIN))
    {
        rising();
    }
    else
    {
        falling();
    }
    return IRQ_HANDLED;
}
static inline void register_key(int key)
{
    input_device->keybit[BIT_WORD(key)] |= BIT_MASK(key);
}
static int __init pibook_hid_driver_init(void)
{
    int result;
    int i;
    printk(KERN_INFO "Keyboard: Claiming power pin %i\n", POWER_PIN);
    result = gpio_request(POWER_PIN, "Keyboard power pin");
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Can't allocate pin %i\n", POWER_PIN);
        return result;
    }
    // Disable power supply
    result = gpio_direction_output(POWER_PIN, LOW);
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Can't set pin %i to output (initial state: low)\n", POWER_PIN);
        gpio_free(POWER_PIN);
        return result;
    }
    printk(KERN_INFO "Keyboard: Initialising on pin %i\n", DATA_PIN);
    result = gpio_request(DATA_PIN, "Keyboard data pin");
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Can't allocate pin %i\n", DATA_PIN);
        gpio_free(POWER_PIN);
        return result;
    }
    result = gpio_direction_input(DATA_PIN);
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Can't set pin %i to input\n", DATA_PIN);
        gpio_free(POWER_PIN);
        gpio_free(DATA_PIN);
        return result;
    }
    // printk(KERN_INFO "Keyboard: First value: %i\n", gpio_get_value(DATA_PIN));
    GPIO_IRQ = gpio_to_irq(DATA_PIN);
    if (GPIO_IRQ < 0)
    {
        printk(KERN_ERR "Keyboard: Can't find corresponding IRQ\n");
        gpio_free(POWER_PIN);
        gpio_free(DATA_PIN);
        return GPIO_IRQ;
    }
    result = request_irq(GPIO_IRQ, interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "Keyboard and joystick interrupt", interrupt);
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Can't allocate IRQ %d\n", GPIO_IRQ);
        gpio_free(POWER_PIN);
        gpio_free(DATA_PIN);
        return result;
    }
    printk(KERN_INFO "Keyboard: Initialising input device\n");
    input_device = input_allocate_device();
    if (!input_device)
    {
        printk(KERN_ERR "Keyboard: Not enough memory\n");
        gpio_free(POWER_PIN);
        free_irq(GPIO_IRQ, interrupt);
        gpio_free(DATA_PIN);
        return -ENOMEM;
    }
    input_device->evbit[BIT_WORD(EV_KEY)] = BIT_MASK(EV_KEY);
    input_device->evbit[BIT_WORD(EV_REP)] |= BIT_MASK(EV_REP);
    input_device->evbit[BIT_WORD(EV_REL)] |= BIT_MASK(EV_REL);
    input_device->relbit[BIT_WORD(REL_X)] = BIT_MASK(REL_X);
    input_device->relbit[BIT_WORD(REL_Y)] |= BIT_MASK(REL_Y);
    input_device->name = "Pi-Book keyboard and joystick";
    input_device->id.bustype = BUS_RS232;
    input_device->id.version = 0;
    // Register all keys
    for (i = 0; i <= PIN_MAX; i++)
    {
        register_key(map_pin(i));
    }
    // Register mouse button
    register_key(BTN_LEFT);
    result = input_register_device(input_device);
    if (result != 0)
    {
        printk(KERN_ERR "Keyboard: Failed to register input device\n");
        gpio_free(POWER_PIN);
        input_free_device(input_device);
        free_irq(GPIO_IRQ, interrupt);
        gpio_free(DATA_PIN);
        return result;
    }
    printk(KERN_INFO "Keyboard: Waiting for keyboard to run out of power\n");
    msleep(10);
    last = ktime_get();
    gpio_set_value(POWER_PIN, HIGH);
    printk(KERN_INFO "Keyboard: Initialised\n");
    return 0;
}
static void __exit pibook_hid_driver_exit(void)
{
    printk(KERN_INFO "Keyboard: Releasing resources\n");
    // Disable power supply
    gpio_set_value(POWER_PIN, LOW);

    gpio_free(POWER_PIN);
    input_unregister_device(input_device);
    free_irq(GPIO_IRQ, interrupt);
    gpio_free(DATA_PIN);
    printk(KERN_INFO "Keyboard: Exit\n");
}
module_init(pibook_hid_driver_init);
module_exit(pibook_hid_driver_exit);
