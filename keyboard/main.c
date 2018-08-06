#include "std_headers.c"
#include "keyboard.c"
int main(){
    int key;
    scanf("%i", &key);
    bool val[KEY_CNT];
    for(int i = 0; i < KEY_CNT; i++){
        val[i] = false;
    }
    val[key] = true;
    setupKeyboard(val);
    sleep(1);
    keyDown(key);
    keyUp(key);
    sleep(1);
    destroyKeyboard();
    return 0;
}