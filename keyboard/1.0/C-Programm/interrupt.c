#include "interrupt.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
int interrupt_setup(int gpio_pin)
{
    interrupt_pin = gpio_pin;
    int dir;
    char dir_path[interrupt_buf_size];
    snprintf(dir_path, sizeof(dir_path), "/sys/class/gpio/gpio%i/direction", interrupt_pin);
    if ((dir = open(dir_path, O_WRONLY)) < 0)
    {
        printf("Pin not exported yet, doing that\n");
        int exp;
        if ((exp = open("/sys/class/gpio/export", O_WRONLY)) < 0)
        {
            printf("Can't export pin!");
            return 1;
        }
        char exp_pin[interrupt_buf_size];
        snprintf(exp_pin, sizeof(exp_pin), "%i", interrupt_pin);
        write(exp, exp_pin, sizeof(exp_pin));
        close(exp);
        dir = open(dir_path, O_WRONLY);
    }
    write(dir, "in", 2);
    close(dir);
    int edge;
    char edge_path[interrupt_buf_size];
    snprintf(edge_path, sizeof(edge_path), "/sys/class/gpio/gpio%i/edge", interrupt_pin);
    if ((edge = open(edge_path, O_WRONLY)) < 0)
    {
        printf("Can't setup interrupt!");
        return 2;
    }
    write(edge, "both", 4);
    close(edge);
    int pin;
    char pin_path[interrupt_buf_size];
    snprintf(pin_path, sizeof(pin_path), "/sys/class/gpio/gpio%i/value", interrupt_pin);
    if ((pin = open(pin_path, O_RDONLY)) < 0)
    {
        printf("Can't attempt to read value!");
        return 3;
    }
    interrupt_pin_fd = pin;
    memcpy(interrupt_value_path, pin_path, interrupt_buf_size);
    return 0;
}
int interrupt_wait(int timeout)
{
    struct pollfd p;
    p.fd = interrupt_pin_fd;
    p.events = POLLPRI;
    lseek(interrupt_pin_fd, 0, SEEK_SET); /* consume any prior interrupt */
    char r_buf[interrupt_buf_size];
    read(interrupt_pin_fd, r_buf, sizeof r_buf);
    return poll(&p, 1, timeout);
}
void interrupt_wait_inf(){
    interrupt_wait(-1);
}
bool interrupt_pin_read()
{
    // We have to open a new instance
    int fd = open(interrupt_value_path, O_RDONLY);
    char buf[2];
    read(fd, buf, 2);
    close(fd);
    return buf[0] == '1';
}
void interrupt_destroy()
{
}