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
    switch (pin)
    {
    case 0:
        return KEY_ESC;
    case 1:
        return KEY_F1;
    case 2:
        return KEY_F2;
    case 3:
        return KEY_F3;
    case 4:
        return KEY_F4;
    case 5:
        return KEY_F5;
    case 6:
        return KEY_F6;
    case 7:
        return KEY_F7;
    case 8:
        return KEY_F8;
    case 9:
        return KEY_F9;
    case 10:
        return KEY_F10;
    case 11:
        return KEY_F11;
    case 12:
        return KEY_F12;
    case 13:
        return KEY_DELETE;
    case 14:
        return KEY_GRAVE;
    case 15:
        return KEY_1;
    case 16:
        return KEY_2;
    case 17:
        return KEY_3;
    case 18:
        return KEY_4;
    case 19:
        return KEY_5;
    case 20:
        return KEY_6;
    case 21:
        return KEY_7;
    case 22:
        return KEY_8;
    case 23:
        return KEY_9;
    case 24:
        return KEY_0;
    case 25:
        return KEY_MINUS;
    case 26:
        return KEY_EQUAL;
    case 27:
        return KEY_BACKSPACE;
    case 28:
        return KEY_TAB;
    case 29:
        return KEY_Q;
    case 30:
        return KEY_W;
    case 31:
        return KEY_E;
    case 32:
        return KEY_R;
    case 33:
        return KEY_T;
    case 34:
        return KEY_Y;
    case 35:
        return KEY_U;
    case 36:
        return KEY_I;
    case 37:
        return KEY_O;
    case 38:
        return KEY_P;
    case 39:
        return KEY_LEFTBRACE;
    case 40:
        return KEY_RIGHTBRACE;
    case 41:
        return KEY_BACKSLASH;
    case 42:
        return KEY_CAPSLOCK;
    case 43:
        return KEY_A;
    case 44:
        return KEY_S;
    case 45:
        return KEY_D;
    case 46:
        return KEY_F;
    case 47:
        return KEY_G;
    case 48:
        return KEY_H;
    case 49:
        return KEY_J;
    case 50:
        return KEY_K;
    case 51:
        return KEY_L;
    case 52:
        return KEY_SEMICOLON;
    case 53:
        return KEY_APOSTROPHE;
    case 54:
        return KEY_ENTER;
    case 55:
        return KEY_LEFTSHIFT;
    case 56:
        return KEY_Z;
    case 57:
        return KEY_X;
    case 58:
        return KEY_C;
    case 59:
        return KEY_V;
    case 60:
        return KEY_B;
    case 61:
        return KEY_N;
    case 62:
        return KEY_M;
    case 63:
        return KEY_COMMA;
    case 64:
        return KEY_DOT;
    case 65:
        return KEY_SLASH;
    case 66:
        return KEY_RIGHTSHIFT;
    case 67:
        return KEY_LEFTCTRL;
    case 68:
        return KEY_102ND;
    case 69:
        return KEY_LEFTMETA;
    case 70:
        return KEY_LEFTALT;
    case 71:
        return KEY_SPACE;
    case 72:
        return KEY_RIGHTALT;
    case 73:
        return KEY_COMPOSE;
    case 74:
        return KEY_LEFT;
    case 75:
        return KEY_UP;
    case 76:
        return KEY_DOWN;
    case 77:
        return KEY_RIGHT;
    default:
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
