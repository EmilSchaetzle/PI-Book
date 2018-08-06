#include "std_headers.c"
#include <linux/uinput.h>
#include <fcntl.h>

bool key_decl[KEY_CNT];
int kb;
// Send event
void send(int type, int code, int val){
    if(kb >= 0){
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
}
void keyDown(int code){
    if(key_decl[code]){
        send(EV_KEY, code, 1);
        send(EV_SYN, SYN_REPORT, 0);
    }
}
void keyUp(int code){
    if(key_decl[code]){
        send(EV_KEY, code, 0);
        send(EV_SYN, SYN_REPORT, 0);
    }
}
int setupKeyboard(bool key_declaration[]){
    memcpy(key_decl, key_declaration, KEY_CNT);
    // Creating keyboard configuration
    struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_RS232;
    strcpy(usetup.name, "PI-Book keyboard");
    // Creating instance
    kb = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    // Setting available keys
    ioctl(kb, UI_SET_EVBIT, EV_KEY);
    for(int code = 0; code < KEY_CNT; code++){       
        if(key_decl[code]){ 
            ioctl(kb, UI_SET_KEYBIT, code);
        }
    } 
    // Creating device
    ioctl(kb, UI_DEV_SETUP, &usetup);
    ioctl(kb, UI_DEV_CREATE);
}
void destroyKeyboard(){
    // Destroy keyboard
    ioctl(kb, UI_DEV_DESTROY);
    close(kb);
}