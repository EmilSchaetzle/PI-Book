#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#define PIN 4
#define BAUD 10000
const int bit_dur = 1000000 / BAUD;
int gpio_irq;
struct timeval last;
bool receiving = false;
bool start_bit_handled;
int received_bits;
bool bits[8];
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emil Schätzle");
MODULE_DESCRIPTION("Driver for the PI-Book keyboard");
MODULE_VERSION("0.01");
static int get_time_difference(void)
{
    long long int time;
    struct timeval now;
    do_gettimeofday(&now);
    time = now.tv_sec - last.tv_sec;
    time *= 1000000;
    time += now.tv_usec - last.tv_usec;
    last = now;
    return time;
}
static int get_bit_durs(void)
{
    int time;
    int total_bit_durs;
    time = get_time_difference();
    total_bit_durs = (time + bit_dur / 2) / bit_dur;
    return total_bit_durs;
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
    //printk(KERN_INFO "Keyboard: %i\n", data);
}
static void rising(void)
{
    if (receiving)
    {
        // Data is currently beeing received
        int i;
        int bit_durs;
        bit_durs = get_bit_durs();
        // Ignore startbit
        if (!start_bit_handled && bit_durs > 0)
        {
            bit_durs--;
            start_bit_handled = true;
        }
        for (i = 0; i < bit_durs && i < 8; i++)
        {
            bits[received_bits + i] = false;
        }
        if (received_bits + bit_durs > 8)
        {
            // Error occured > abort receiving
            receiving = false;
        }
        else
        {
            received_bits += bit_durs;
            if (received_bits == 8)
            {
                receiving = false;
                data_received();
            }
        }
    }
}
static void falling(void)
{
    if (!receiving)
    {
        // New transmission starts, thus reset clock
        get_time_difference();
        receiving = true;
        received_bits = 0;
        start_bit_handled = false;
    }
    else
    {
        // Data is currently beeing received
        int i;
        int bit_durs;
        bit_durs = get_bit_durs();
        for (i = 0; i < bit_durs && i < 8; i++)
        {
            bits[received_bits + i] = true;
        }
        if (received_bits + bit_durs > 8)
        {
            // Error occured > abort receiving
            receiving = false;
        }
        else
        {
            received_bits += bit_durs;
            if (received_bits == 8)
            {
                receiving = false;
                data_received();
            }
        }
    }
}
static irq_handler_t interrupt(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    if (gpio_get_value(PIN))
    {
        rising();
    }
    else
    {
        falling();
    }
    return (irq_handler_t)IRQ_HANDLED;
}
static int __init kb_mod_init(void)
{
    int result;
    printk(KERN_INFO "Keyboard: Initialising on pin %i\n", PIN);
    gpio_request(PIN, "Keyboard pin");
    gpio_direction_input(PIN);
    printk(KERN_INFO "Keyboard: First value: %i\n", gpio_get_value(PIN));
    gpio_irq = gpio_to_irq(PIN);
    result = request_irq(gpio_irq, (irq_handler_t)interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "Keyboard interrupt", NULL);
    printk(KERN_INFO "Keyboard: Initialised\n");
    do_gettimeofday(&last);
    return 0;
}
static void __exit kb_mod_exit(void)
{
    printk(KERN_INFO "Keyboard: Releasing resources\n");
    free_irq(gpio_irq, NULL);
    gpio_free(PIN);
    printk(KERN_INFO "Keyboard: Exit\n");
}
module_init(kb_mod_init);
module_exit(kb_mod_exit);
