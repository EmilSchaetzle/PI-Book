#include "std_headers.h"
#include <linux/uinput.h>
#include <fcntl.h>
#include "keyboard.h"
// Send event
void keyboard_sendEvent(int type, int code, int val)
{
    if (keyboard_descriptor >= 0)
    {
        struct input_event e;
        e.type = type;
        e.code = code;
        e.value = val;
        // Ignore timestamp values
        e.time.tv_sec = 0;
        e.time.tv_usec = 0;
        // Send event
        write(keyboard_descriptor, &e, sizeof(e));
    }
}
void keyboard_sendKeyDown(int code)
{
    if (keyboard_keys[code])
    {
        keyboard_sendEvent(EV_KEY, code, 1);
        keyboard_sendEvent(EV_SYN, SYN_REPORT, 0);
    }
}
void keyboard_sendKeyUp(int code)
{
    if (keyboard_keys[code])
    {
        keyboard_sendEvent(EV_KEY, code, 0);
        keyboard_sendEvent(EV_SYN, SYN_REPORT, 0);
    }
}
int keyboard_setup(bool key_declaration[])
{
    memcpy(keyboard_keys, key_declaration, KEY_CNT);
    // Ckreating keyboard configuration
    struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_RS232;
    strcpy(usetup.name, "PI-Book keyboard");
    // Creating instance
    keyboard_descriptor = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    // Setting available keys
    ioctl(keyboard_descriptor, UI_SET_EVBIT, EV_KEY);
    for (int code = 0; code < KEY_CNT; code++)
    {
        if (keyboard_keys[code])
        {
            ioctl(keyboard_descriptor, UI_SET_KEYBIT, code);
        }
    }
    // Creating device
    ioctl(keyboard_descriptor, UI_DEV_SETUP, &usetup);
    ioctl(keyboard_descriptor, UI_DEV_CREATE);
}
void keyboard_destroy()
{ // Destroy keyboard
    ioctl(keyboard_descriptor, UI_DEV_DESTROY);
    close(keyboard_descriptor);
}