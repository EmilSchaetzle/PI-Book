#include <stdbool.h>
#ifndef INTERRUPT_H
#define INTERRUPT_H
int interrupt_pin_fd;
int interrupt_pin;
#define interrupt_buf_size 64
char interrupt_value_path[interrupt_buf_size];
int interrupt_setup(int gpio_pin);
void interrupt_destroy();
void interrupt_wait_inf();
int interrupt_wait(int timeout);
bool interrupt_pin_read();
#endif