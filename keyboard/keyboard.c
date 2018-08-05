#include <stdio.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <string.h>
// Send event
void send(int kb, int type, int code, int val){
    struct input_event e;
    e.type = type;
    e.code = code;
    e.value = val;
    // Ignore timestamp values
    e.time.tv_sec = 0;
    e.time.tv_usec = 0;
    // Send event
    write(kb, &e, sizeof(e));
}
int main(){
    // Creating keyboard configuration
    struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;
    usetup.id.product = 0x5678;
    strcpy(usetup.name, "PI-Book keyboard");
    // Creating instance
    int kb = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    // Setting available keys
    ioctl(kb, UI_SET_EVBIT, EV_KEY);
    ioctl(kb, UI_SET_KEYBIT, KEY_A);
    // Creating device
    ioctl(kb, UI_DEV_SETUP, &usetup);
    ioctl(kb, UI_DEV_CREATE);
    sleep(1);
    // Send keys
    send(kb, EV_KEY, KEY_A, 1);
    send(kb, EV_SYN, SYN_REPORT, 0);
    send(kb, EV_KEY, KEY_A, 0);
    send(kb, EV_SYN, SYN_REPORT, 0);
    sleep(1);
    // Destroy keyboard
    ioctl(kb, UI_DEV_DESTROY);
    close(kb);
    return 0;
}