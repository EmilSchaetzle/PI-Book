#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#define PIN 4
#define BAUD 5000
const int bit_dur = 1000000 / BAUD;
int gpio_irq;
struct timeval last;
bool receiving = false;
bool start_bit_handled;
int received_bits;
bool bits[8];
int status = 0;
int err = 0;
int cnt = 0;
int lt;
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
    lt = time;
    return time;
}
static int get_bit_durs(void)
{
    int time;
    int total_bit_durs;
    int fraction_bit_durs;
    time = get_time_difference();
    total_bit_durs = (time + bit_dur / 2) / bit_dur;
    fraction_bit_durs = 1000 * (time - total_bit_durs * bit_dur) / bit_dur;
    if (fraction_bit_durs > 500)
    {
        total_bit_durs++;
    }
    return total_bit_durs;
}
static void data_received(void)
{
    int x = 0;
    x += 1 * bits[0];
    x += 2 * bits[1];
    x += 4 * bits[2];
    x += 8 * bits[3];
    x += 16 * bits[4];
    x += 32 * bits[5];
    x += 64 * bits[6];
    x += 128 * bits[7];
    //printk(KERN_INFO "Keyboard: Received byte %i[%i%i%i%i%i%i%i%i]\n", x, bits[0], bits[1], bits[2], bits[3], bits[4], bits[5], bits[6], bits[7]);
    cnt++;
    if (x != status)
    {
        err++;
        printk(KERN_INFO "Keyboard: %i - %i", x, status);
        status = x;
    }
    if (status == 255)
    {
        status = -1;
        printk(KERN_INFO "Keyboard: %i of %i\n", err, cnt);
    }
    status++;
}
static void rising(void)
{
    if (receiving)
    {
        // Data is currently beeing received
        int bit_durs;
        int i;
        bit_durs = get_bit_durs();
        //printk(KERN_INFO "Got l%i", bit_durs);
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
            // Error occured > log & abort receiving
            printk(KERN_INFO "Keyboard: Received %i instead of 8 bits, %i\n", received_bits + bit_durs, lt);
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
        int bit_durs;
        int i;
        bit_durs = get_bit_durs();
        //printk(KERN_INFO "Got h%i", bit_durs);
        for (i = 0; i < bit_durs && i < 8; i++)
        {
            bits[received_bits + i] = true;
        }
        if (received_bits + bit_durs > 8)
        {
            // Error occured > log & abort receiving
            //printk(KERN_INFO "Keyboard: Received %i instead of 8 bits\n", received_bits + bit_durs);
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
