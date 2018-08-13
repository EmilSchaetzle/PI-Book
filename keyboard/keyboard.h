#include <linux/uinput.h>
#ifndef KEYBOARD_H
#define KEYBOARD_H
bool keyboard_keys[KEY_CNT];
int keyboard_descriptor;
void keyboard_sendEvent(int type, int code, int val);
void keyboard_sendKeyDown(int code);
void keyboard_sendKeyUp(int code);
int keyboard_setup(bool key_declaration[]);
void keyboard_destroy();
#endif