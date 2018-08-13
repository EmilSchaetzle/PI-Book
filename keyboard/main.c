#include "std_headers.h"
#include "keyboard.h"
#include <linux/uinput.h>
#include <fcntl.h>
int main()
{
    int key;
    scanf("%i", &key);
    bool val[KEY_CNT];
    for (int i = 0; i < KEY_CNT; i++)
    {
        val[i] = false;
    }
    val[key] = true;
    keyboard_setup(val);
    sleep(1);
    keyboard_sendKeyDown(key);
    keyboard_sendKeyUp(key);
    sleep(1);
    keyboard_destroy();
    return 0;
}