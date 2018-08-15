#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "keyboard.h"
#include "interrupt.h"
#include <linux/uinput.h>
#include <fcntl.h>
#include <math.h>
int main()
{
    // int key;
    // scanf("%i", &key);
    // bool val[KEY_CNT];
    // for (int i = 0; i < KEY_CNT; i++)
    // {
    //     val[i] = false;
    // }
    // val[key] = true;
    // keyboard_setup(val);
    // sleep(1);
    // keyboard_sendKeyDown(key);
    // keyboard_sendKeyUp(key);
    // sleep(1);
    // keyboard_destroy();
    interrupt_setup(4);
    int last = 0;
    int err = 0;
    int tot = 0;
    while (true)
    {
        int baud = 300;
        double bit_dur = 1.0 / baud;
        bool bits[8];
        int bit_cnt = 0;
        while (bit_cnt != 8)
        {
            bit_cnt = 0;
            // Wait for low state
            do
            {
                interrupt_wait_inf();
            } while (interrupt_pin_read() == true);
            bool timeout = false;
            bool start_bit_erased = false;
            while (!timeout && bit_cnt < 8)
            {
                struct timeval start;
                struct timeval end;
                struct timeval total;
                bool state = interrupt_pin_read();
                gettimeofday(&start, NULL);
                timeout = 0 == interrupt_wait(ceil(15 * bit_dur * 1000));
                gettimeofday(&end, NULL);
                timersub(&end, &start, &total);
                double time = total.tv_sec + total.tv_usec / 1000000.0;
                int time_bit_durs = round(time / bit_dur);
                // Ignore the startbit
                if (!start_bit_erased)
                {
                    time_bit_durs -= 1;
                    start_bit_erased = true;
                }
                for (int i = 0; i < time_bit_durs && bit_cnt + i < 8; i++)
                {
                    bits[bit_cnt + i] = state;
                }
                bit_cnt += time_bit_durs;
                // Ignore the stopbit
                if (bit_cnt == 9 && !state)
                {
                    bit_cnt = 8;
                }
            }
        }
        //printf("Received %i bits:\n[", bit_cnt);
        int x = 0;
        for (int i = 1; i < bit_cnt && i < 8; i++)
        {
            //printf("%i", bits[i]);
            x += bits[i] * pow(2, i - 1);
        }
        //printf("]\n");
        //printf("%i\n", x);
        if ((last + 1) % 128 != x)
        {
            //printf("ERROR%i-%i\n", (last + 1) % 128, x);
            err++;
        }
        tot++;
        last = x % 128;
        printf("%i out of %i: %f\%\n", err, tot, 100.0 * err / tot);
    }

    return 0;
}