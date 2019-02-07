/*
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

volatile uint8_t LPINA, LPINB, LPINC, LPIND, LPINE, LPINH, LPINJ, LPINL, LPINK, LPING;
volatile bool LBUTTON;

inline void del()
{
    while (!(TIFR2 & (1 << OCF2A)))
    {
    }
    TIFR2 |= (1 << OCF2A);
}

inline void high()
{
    PORTF |= (1 << PF0);
    del();
}

inline void low()
{
    PORTF &= ~(1 << PF0);
    del();
}
void send(uint8_t value)
{
    bool bits[8];
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        bits[i] = (value & (1 << i));
    }
    // Start bit
    del();
    del();
    low();
    // Send all the data bits
    for (i = 0; i < 8; i++)
    {
        if (bits[i])
        {
            high();
        }
        else
        {
            low();
        }
    }
    // Trigger last interrupt
    if (bits[7])
    {
        low();
    }
    else
    {
        high();
    }
    // Stop Bit
    high();
}

void send_key_state(uint8_t pin, bool state)
{
    send(pin + 78 * state);
}

void send_button_state(bool state)
{
    send(156 + 1 * state);
}
void send_rx_state(int8_t state)
{
    if (state != 0)
    {
        send(182 + state);
    }
}
void send_ry_state(int8_t state)
{
    if (state != 0)
    {
        send(231 + state);
    }
}
int16_t read_PF1()
{
    // Select ADC1 as input
    ADMUX |= (1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    // Start Conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    }
    uint16_t val = ADCL;
    val += (1 << 8) * ADCH;
    return val;
}
int16_t read_PF2()
{
    // Select ADC2 as input
    ADMUX &= ~(1 << MUX0);
    ADMUX |= (1 << MUX1);
    // Start Conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    }
    uint16_t val = ADCL;
    val += (1 << 8) * ADCH;
    return val;
}
int8_t read_rx()
{
    double val = read_PF2();
    val -= 511.5;
    val *= 49.0 / 1024;
    return (int8_t)round(val);
}
int8_t read_ry()
{
    double val = read_PF1();
    val -= 511.5;
    val *= 49.0 / 1024;
    return (int8_t)round(val);
}
void send_initial_state()
{
    // Send key states
    send_key_state(21, PINA & (1 << PA0));
    send_key_state(34, PINA & (1 << PA1));
    send_key_state(60, PINA & (1 << PA2));
    send_key_state(48, PINA & (1 << PA3));
    send_key_state(61, PINA & (1 << PA4));
    send_key_state(7, PINA & (1 << PA5));
    send_key_state(71, PINA & (1 << PA6));
    send_key_state(22, PINA & (1 << PA7));

    send_key_state(56, PINB & (1 << PB0));
    send_key_state(69, PINB & (1 << PB1));
    send_key_state(68, PINB & (1 << PB2));
    send_key_state(15, PINB & (1 << PB3));
    send_key_state(1, PINB & (1 << PB4));
    send_key_state(0, PINB & (1 << PB5));
    send_key_state(14, PINB & (1 << PB6));
    send_key_state(28, PINB & (1 << PB7));

    send_key_state(73, PINC & (1 << PC0));
    send_key_state(72, PINC & (1 << PC1));
    send_key_state(52, PINC & (1 << PC2));
    send_key_state(64, PINC & (1 << PC3));
    send_key_state(63, PINC & (1 << PC4));
    send_key_state(51, PINC & (1 << PC5));
    send_key_state(37, PINC & (1 << PC6));
    send_key_state(24, PINC & (1 << PC7));

    send_key_state(75, PIND & (1 << PD0));
    send_key_state(74, PIND & (1 << PD1));
    send_key_state(11, PIND & (1 << PD2));
    send_key_state(26, PIND & (1 << PD3));
    send_key_state(39, PIND & (1 << PD4));
    send_key_state(53, PIND & (1 << PD5));
    send_key_state(65, PIND & (1 << PD6));
    send_key_state(10, PIND & (1 << PD7));

    send_key_state(46, PINE & (1 << PE0));
    send_key_state(4, PINE & (1 << PE1));
    send_key_state(18, PINE & (1 << PE2));
    send_key_state(31, PINE & (1 << PE3));
    send_key_state(45, PINE & (1 << PE4));
    send_key_state(57, PINE & (1 << PE5));
    send_key_state(44, PINE & (1 << PE6));
    send_key_state(30, PINE & (1 << PE7));

    send_key_state(70, PINH & (1 << PH0));
    send_key_state(17, PINH & (1 << PH1));
    send_key_state(3, PINH & (1 << PH2));
    send_key_state(2, PINH & (1 << PH3));
    send_key_state(16, PINH & (1 << PH4));
    send_key_state(29, PINH & (1 << PH5));
    send_key_state(43, PINH & (1 << PH6));
    send_key_state(42, PINH & (1 << PH7));

    send_key_state(9, PINJ & (1 << PJ0));
    send_key_state(62, PINJ & (1 << PJ1));
    send_key_state(50, PINJ & (1 << PJ2));
    send_key_state(36, PINJ & (1 << PJ3));
    send_key_state(23, PINJ & (1 << PJ4));
    send_key_state(8, PINJ & (1 << PJ5));
    send_key_state(49, PINJ & (1 << PJ6));
    send_key_state(76, PINJ & (1 << PJ7));

    send_key_state(77, PINL & (1 << PL0));
    send_key_state(41, PINL & (1 << PL1));
    send_key_state(13, PINL & (1 << PL2));
    send_key_state(27, PINL & (1 << PL3));
    send_key_state(54, PINL & (1 << PL4));
    send_key_state(66, PINL & (1 << PL5));
    send_key_state(12, PINL & (1 << PL6));
    send_key_state(40, PINL & (1 << PL7));

    send_key_state(5, PINK & (1 << PK0));
    send_key_state(19, PINK & (1 << PK1));
    send_key_state(58, PINK & (1 << PK2));
    send_key_state(47, PINK & (1 << PK3));
    send_key_state(33, PINK & (1 << PK4));
    send_key_state(20, PINK & (1 << PK5));
    send_key_state(6, PINK & (1 << PK6));
    send_key_state(59, PINK & (1 << PK7));

    send_key_state(25, PING & (1 << PG0));
    send_key_state(38, PING & (1 << PG1));
    send_key_state(35, PING & (1 << PG2));
    send_key_state(55, PING & (1 << PG3));
    send_key_state(67, PING & (1 << PG4));
    send_key_state(32, PING & (1 << PG5));

    // Send button state:
    send_button_state((PINF & (1 << PF3)));
}

void refresh_state()
{
    if (PINA != LPINA)
    {
        if ((PINA & (1 << PA0)) != (LPINA & (1 << PA0)))
        {
            send_key_state(21, (PINA & (1 << PA0)));
            LPINA ^= 1 << PA0;
        }
        if ((PINA & (1 << PA1)) != (LPINA & (1 << PA1)))
        {
            send_key_state(34, (PINA & (1 << PA1)));
            LPINA ^= 1 << PA1;
        }
        if ((PINA & (1 << PA2)) != (LPINA & (1 << PA2)))
        {
            send_key_state(60, (PINA & (1 << PA2)));
            LPINA ^= 1 << PA2;
        }
        if ((PINA & (1 << PA3)) != (LPINA & (1 << PA3)))
        {
            send_key_state(48, (PINA & (1 << PA3)));
            LPINA ^= 1 << PA3;
        }
        if ((PINA & (1 << PA4)) != (LPINA & (1 << PA4)))
        {
            send_key_state(61, (PINA & (1 << PA4)));
            LPINA ^= 1 << PA4;
        }
        if ((PINA & (1 << PA5)) != (LPINA & (1 << PA5)))
        {
            send_key_state(7, (PINA & (1 << PA5)));
            LPINA ^= 1 << PA5;
        }
        if ((PINA & (1 << PA6)) != (LPINA & (1 << PA6)))
        {
            send_key_state(71, (PINA & (1 << PA6)));
            LPINA ^= 1 << PA6;
        }
        if ((PINA & (1 << PA7)) != (LPINA & (1 << PA7)))
        {
            send_key_state(22, (PINA & (1 << PA7)));
            LPINA ^= 1 << PA7;
        }
    }

    if (PINB != LPINB)
    {
        if ((PINB & (1 << PB0)) != (LPINB & (1 << PB0)))
        {
            send_key_state(56, (PINB & (1 << PB0)));
            LPINB ^= 1 << PB0;
        }
        if ((PINB & (1 << PB1)) != (LPINB & (1 << PB1)))
        {
            send_key_state(69, (PINB & (1 << PB1)));
            LPINB ^= 1 << PB1;
        }
        if ((PINB & (1 << PB2)) != (LPINB & (1 << PB2)))
        {
            send_key_state(68, (PINB & (1 << PB2)));
            LPINB ^= 1 << PB2;
        }
        if ((PINB & (1 << PB3)) != (LPINB & (1 << PB3)))
        {
            send_key_state(15, (PINB & (1 << PB3)));
            LPINB ^= 1 << PB3;
        }
        if ((PINB & (1 << PB4)) != (LPINB & (1 << PB4)))
        {
            send_key_state(1, (PINB & (1 << PB4)));
            LPINB ^= 1 << PB4;
        }
        if ((PINB & (1 << PB5)) != (LPINB & (1 << PB5)))
        {
            send_key_state(0, (PINB & (1 << PB5)));
            LPINB ^= 1 << PB5;
        }
        if ((PINB & (1 << PB6)) != (LPINB & (1 << PB6)))
        {
            send_key_state(14, (PINB & (1 << PB6)));
            LPINB ^= 1 << PB6;
        }
        if ((PINB & (1 << PB7)) != (LPINB & (1 << PB7)))
        {
            send_key_state(28, (PINB & (1 << PB7)));
            LPINB ^= 1 << PB7;
        }
    }

    if (PINC != LPINC)
    {
        if ((PINC & (1 << PC0)) != (LPINC & (1 << PC0)))
        {
            send_key_state(73, (PINC & (1 << PC0)));
            LPINC ^= 1 << PC0;
        }
        if ((PINC & (1 << PC1)) != (LPINC & (1 << PC1)))
        {
            send_key_state(72, (PINC & (1 << PC1)));
            LPINC ^= 1 << PC1;
        }
        if ((PINC & (1 << PC2)) != (LPINC & (1 << PC2)))
        {
            send_key_state(52, (PINC & (1 << PC2)));
            LPINC ^= 1 << PC2;
        }
        if ((PINC & (1 << PC3)) != (LPINC & (1 << PC3)))
        {
            send_key_state(64, (PINC & (1 << PC3)));
            LPINC ^= 1 << PC3;
        }
        if ((PINC & (1 << PC4)) != (LPINC & (1 << PC4)))
        {
            send_key_state(63, (PINC & (1 << PC4)));
            LPINC ^= 1 << PC4;
        }
        if ((PINC & (1 << PC5)) != (LPINC & (1 << PC5)))
        {
            send_key_state(51, (PINC & (1 << PC5)));
            LPINC ^= 1 << PC5;
        }
        if ((PINC & (1 << PC6)) != (LPINC & (1 << PC6)))
        {
            send_key_state(37, (PINC & (1 << PC6)));
            LPINC ^= 1 << PC6;
        }
        if ((PINC & (1 << PC7)) != (LPINC & (1 << PC7)))
        {
            send_key_state(24, (PINC & (1 << PC7)));
            LPINC ^= 1 << PC7;
        }
    }

    if (PIND != LPIND)
    {
        if ((PIND & (1 << PD0)) != (LPIND & (1 << PD0)))
        {
            send_key_state(75, (PIND & (1 << PD0)));
            LPIND ^= 1 << PD0;
        }
        if ((PIND & (1 << PD1)) != (LPIND & (1 << PD1)))
        {
            send_key_state(74, (PIND & (1 << PD1)));
            LPIND ^= 1 << PD1;
        }
        if ((PIND & (1 << PD2)) != (LPIND & (1 << PD2)))
        {
            send_key_state(11, (PIND & (1 << PD2)));
            LPIND ^= 1 << PD2;
        }
        if ((PIND & (1 << PD3)) != (LPIND & (1 << PD3)))
        {
            send_key_state(26, (PIND & (1 << PD3)));
            LPIND ^= 1 << PD3;
        }
        if ((PIND & (1 << PD4)) != (LPIND & (1 << PD4)))
        {
            send_key_state(39, (PIND & (1 << PD4)));
            LPIND ^= 1 << PD4;
        }
        if ((PIND & (1 << PD5)) != (LPIND & (1 << PD5)))
        {
            send_key_state(53, (PIND & (1 << PD5)));
            LPIND ^= 1 << PD5;
        }
        if ((PIND & (1 << PD6)) != (LPIND & (1 << PD6)))
        {
            send_key_state(65, (PIND & (1 << PD6)));
            LPIND ^= 1 << PD6;
        }
        if ((PIND & (1 << PD7)) != (LPIND & (1 << PD7)))
        {
            send_key_state(10, (PIND & (1 << PD7)));
            LPIND ^= 1 << PD7;
        }
    }

    if (PINE != LPINE)
    {
        if ((PINE & (1 << PE0)) != (LPINE & (1 << PE0)))
        {
            send_key_state(46, (PINE & (1 << PE0)));
            LPINE ^= 1 << PE0;
        }
        if ((PINE & (1 << PE1)) != (LPINE & (1 << PE1)))
        {
            send_key_state(4, (PINE & (1 << PE1)));
            LPINE ^= 1 << PE1;
        }
        if ((PINE & (1 << PE2)) != (LPINE & (1 << PE2)))
        {
            send_key_state(18, (PINE & (1 << PE2)));
            LPINE ^= 1 << PE2;
        }
        if ((PINE & (1 << PE3)) != (LPINE & (1 << PE3)))
        {
            send_key_state(31, (PINE & (1 << PE3)));
            LPINE ^= 1 << PE3;
        }
        if ((PINE & (1 << PE4)) != (LPINE & (1 << PE4)))
        {
            send_key_state(45, (PINE & (1 << PE4)));
            LPINE ^= 1 << PE4;
        }
        if ((PINE & (1 << PE5)) != (LPINE & (1 << PE5)))
        {
            send_key_state(57, (PINE & (1 << PE5)));
            LPINE ^= 1 << PE5;
        }
        if ((PINE & (1 << PE6)) != (LPINE & (1 << PE6)))
        {
            send_key_state(44, (PINE & (1 << PE6)));
            LPINE ^= 1 << PE6;
        }
        if ((PINE & (1 << PE7)) != (LPINE & (1 << PE7)))
        {
            send_key_state(30, (PINE & (1 << PE7)));
            LPINE ^= 1 << PE7;
        }
    }

    if (PINH != LPINH)
    {
        if ((PINH & (1 << PH0)) != (LPINH & (1 << PH0)))
        {
            send_key_state(70, (PINH & (1 << PH0)));
            LPINH ^= 1 << PH0;
        }
        if ((PINH & (1 << PH1)) != (LPINH & (1 << PH1)))
        {
            send_key_state(17, (PINH & (1 << PH1)));
            LPINH ^= 1 << PH1;
        }
        if ((PINH & (1 << PH2)) != (LPINH & (1 << PH2)))
        {
            send_key_state(3, (PINH & (1 << PH2)));
            LPINH ^= 1 << PH2;
        }
        if ((PINH & (1 << PH3)) != (LPINH & (1 << PH3)))
        {
            send_key_state(2, (PINH & (1 << PH3)));
            LPINH ^= 1 << PH3;
        }
        if ((PINH & (1 << PH4)) != (LPINH & (1 << PH4)))
        {
            send_key_state(16, (PINH & (1 << PH4)));
            LPINH ^= 1 << PH4;
        }
        if ((PINH & (1 << PH5)) != (LPINH & (1 << PH5)))
        {
            send_key_state(29, (PINH & (1 << PH5)));
            LPINH ^= 1 << PH5;
        }
        if ((PINH & (1 << PH6)) != (LPINH & (1 << PH6)))
        {
            send_key_state(43, (PINH & (1 << PH6)));
            LPINH ^= 1 << PH6;
        }
        if ((PINH & (1 << PH7)) != (LPINH & (1 << PH7)))
        {
            send_key_state(42, (PINH & (1 << PH7)));
            LPINH ^= 1 << PH7;
        }
    }

    if (PINJ != LPINJ)
    {
        if ((PINJ & (1 << PJ0)) != (LPINJ & (1 << PJ0)))
        {
            send_key_state(9, (PINJ & (1 << PJ0)));
            LPINJ ^= 1 << PJ0;
        }
        if ((PINJ & (1 << PJ1)) != (LPINJ & (1 << PJ1)))
        {
            send_key_state(62, (PINJ & (1 << PJ1)));
            LPINJ ^= 1 << PJ1;
        }
        if ((PINJ & (1 << PJ2)) != (LPINJ & (1 << PJ2)))
        {
            send_key_state(50, (PINJ & (1 << PJ2)));
            LPINJ ^= 1 << PJ2;
        }
        if ((PINJ & (1 << PJ3)) != (LPINJ & (1 << PJ3)))
        {
            send_key_state(36, (PINJ & (1 << PJ3)));
            LPINJ ^= 1 << PJ3;
        }
        if ((PINJ & (1 << PJ4)) != (LPINJ & (1 << PJ4)))
        {
            send_key_state(23, (PINJ & (1 << PJ4)));
            LPINJ ^= 1 << PJ4;
        }
        if ((PINJ & (1 << PJ5)) != (LPINJ & (1 << PJ5)))
        {
            send_key_state(8, (PINJ & (1 << PJ5)));
            LPINJ ^= 1 << PJ5;
        }
        if ((PINJ & (1 << PJ6)) != (LPINJ & (1 << PJ6)))
        {
            send_key_state(49, (PINJ & (1 << PJ6)));
            LPINJ ^= 1 << PJ6;
        }
        if ((PINJ & (1 << PJ7)) != (LPINJ & (1 << PJ7)))
        {
            send_key_state(76, (PINJ & (1 << PJ7)));
            LPINJ ^= 1 << PJ7;
        }
    }

    if (PINL != LPINL)
    {
        if ((PINL & (1 << PL0)) != (LPINL & (1 << PL0)))
        {
            send_key_state(77, (PINL & (1 << PL0)));
            LPINL ^= 1 << PL0;
        }
        if ((PINL & (1 << PL1)) != (LPINL & (1 << PL1)))
        {
            send_key_state(41, (PINL & (1 << PL1)));
            LPINL ^= 1 << PL1;
        }
        if ((PINL & (1 << PL2)) != (LPINL & (1 << PL2)))
        {
            send_key_state(13, (PINL & (1 << PL2)));
            LPINL ^= 1 << PL2;
        }
        if ((PINL & (1 << PL3)) != (LPINL & (1 << PL3)))
        {
            send_key_state(27, (PINL & (1 << PL3)));
            LPINL ^= 1 << PL3;
        }
        if ((PINL & (1 << PL4)) != (LPINL & (1 << PL4)))
        {
            send_key_state(54, (PINL & (1 << PL4)));
            LPINL ^= 1 << PL4;
        }
        if ((PINL & (1 << PL5)) != (LPINL & (1 << PL5)))
        {
            send_key_state(66, (PINL & (1 << PL5)));
            LPINL ^= 1 << PL5;
        }
        if ((PINL & (1 << PL6)) != (LPINL & (1 << PL6)))
        {
            send_key_state(12, (PINL & (1 << PL6)));
            LPINL ^= 1 << PL6;
        }
        if ((PINL & (1 << PL7)) != (LPINL & (1 << PL7)))
        {
            send_key_state(40, (PINL & (1 << PL7)));
            LPINL ^= 1 << PL7;
        }
    }

    if (PINK != LPINK)
    {
        if ((PINK & (1 << PK0)) != (LPINK & (1 << PK0)))
        {
            send_key_state(5, (PINK & (1 << PK0)));
            LPINK ^= 1 << PK0;
        }
        if ((PINK & (1 << PK1)) != (LPINK & (1 << PK1)))
        {
            send_key_state(19, (PINK & (1 << PK1)));
            LPINK ^= 1 << PK1;
        }
        if ((PINK & (1 << PK2)) != (LPINK & (1 << PK2)))
        {
            send_key_state(58, (PINK & (1 << PK2)));
            LPINK ^= 1 << PK2;
        }
        if ((PINK & (1 << PK3)) != (LPINK & (1 << PK3)))
        {
            send_key_state(47, (PINK & (1 << PK3)));
            LPINK ^= 1 << PK3;
        }
        if ((PINK & (1 << PK4)) != (LPINK & (1 << PK4)))
        {
            send_key_state(33, (PINK & (1 << PK4)));
            LPINK ^= 1 << PK4;
        }
        if ((PINK & (1 << PK5)) != (LPINK & (1 << PK5)))
        {
            send_key_state(20, (PINK & (1 << PK5)));
            LPINK ^= 1 << PK5;
        }
        if ((PINK & (1 << PK6)) != (LPINK & (1 << PK6)))
        {
            send_key_state(6, (PINK & (1 << PK6)));
            LPINK ^= 1 << PK6;
        }
        if ((PINK & (1 << PK7)) != (LPINK & (1 << PK7)))
        {
            send_key_state(59, (PINK & (1 << PK7)));
            LPINK ^= 1 << PK7;
        }
    }

    if (PING != LPING)
    {
        if ((PING & (1 << PG0)) != (LPING & (1 << PG0)))
        {
            send_key_state(25, (PING & (1 << PG0)));
            LPING ^= 1 << PG0;
        }
        if ((PING & (1 << PG1)) != (LPING & (1 << PG1)))
        {
            send_key_state(38, (PING & (1 << PG1)));
            LPING ^= 1 << PG1;
        }
        if ((PING & (1 << PG2)) != (LPING & (1 << PG2)))
        {
            send_key_state(35, (PING & (1 << PG2)));
            LPING ^= 1 << PG2;
        }
        if ((PING & (1 << PG3)) != (LPING & (1 << PG3)))
        {
            send_key_state(55, (PING & (1 << PG3)));
            LPING ^= 1 << PG3;
        }
        if ((PING & (1 << PG4)) != (LPING & (1 << PG4)))
        {
            send_key_state(67, (PING & (1 << PG4)));
            LPING ^= 1 << PG4;
        }
        if ((PING & (1 << PG5)) != (LPING & (1 << PG5)))
        {
            send_key_state(32, (PING & (1 << PG5)));
            LPING ^= 1 << PG5;
        }
    }

    if (((PINF & (1 << PF3)) != 0) != LBUTTON)
    {
        send_button_state((PINF & (1 << PF3)));
        LBUTTON = !LBUTTON;
    }

    if ((TIFR0 & (1 << OCF0A)))
    {
        TIFR0 |= (1 << OCF0A);
        send_rx_state(read_rx());
        send_ry_state(read_ry());
    }
}

void set_initial_state()
{
    // Set last key states
    LPINA = PINA;
    LPINB = PINB;
    LPINC = PINC;
    LPIND = PIND;
    LPINE = PINE;
    LPING = PING;
    LPINH = PINH;
    LPINJ = PINJ;
    LPINK = PINK;
    LPINL = PINL;

    // Set last button state
    LBUTTON = (PINF & (1 << PF3));
}
int main(void)
{
    cli();
    // Set up the systemclock to run at 125.000 Hz
    CLKPR = (1 << CLKPCE);
#if F_OSC == 8000000
    CLKPR = (1 << CLKPS2) | (1 << CLKPS1);
#elif F_OSC == 16000000
    CLKPR = (1 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0);
#else
#error "Invalid F_OSC"
#endif

    // Disable unused devices
    PRR0 = (1 << PRTWI) | (1 << PRTIM1) | (1 << PRSPI) | (1 << PRUSART0);
    PRR1 = (1 << PRTIM5) | (1 << PRTIM4) | (1 << PRTIM3) | (1 << PRUSART3) | (1 << PRUSART2) | (1 << PRUSART1);

    // Set up timer 2 for 1984,127 Hz (data transmission)
    // Stopping the timer
    TCCR2A = 0;
    TCCR2B = 0;
    // Set current value to 0
    TCNT2 = 0;
    // Set bit every 63 cycles
    OCR2A = 62;
    // Activate CTC Mode
    TCCR2A |= (1 << WGM21);
    // Set no prescaler
    TCCR2B |= (1 << CS20);

    // Set up timer 0 for 62,5 Hz (joystick)
    // Stopping the timer
    TCCR0A = 0;
    TCCR0B = 0;
    // Set the current value to 0
    TCNT0 = 0;
    // Set bit every 250 cycles
    OCR0A = 249;
    // Activate CTC Mode
    TCCR0A |= (1 << WGM01);
    // Set prescaler to 8
    TCCR0B |= (1 << CS01);

    // Set up ADC
    // Set reference voltage to Vcc
    ADMUX = (1 << REFS0);
    // Set prescaler to 2
    ADCSRA = (1 << ADEN) | (1 << ADPS0);
    ADCSRB = 0;

    // Set up pins
    // Set up pins for keys

    // 8x(8 standard pins)
    DDRA = 0x00;  // 0 - 7
    PORTA = 0xFF; // Enable pullup
    DDRB = 0x00;  // 8 - 15
    PORTB = 0xFF; // Enable pullup
    DDRC = 0x00;  // 16 - 23
    PORTC = 0xFF; // Enable pullup
    DDRD = 0x00;  // 24 - 31
    PORTD = 0xFF; // Enable pullup
    DDRE = 0x00;  // 32 - 39
    PORTE = 0xFF; // Enable pullup
    DDRH = 0x00;  // 40 - 47
    PORTH = 0xFF; // Enable pullup
    DDRJ = 0x00;  // 48 - 55
    PORTJ = 0xFF; // Enable pullup
    DDRL = 0x00;  // 56 - 63
    PORTL = 0xFF; // Enable pullup

    // 8 analog-able pins
    DDRK = 0x00;  // 64 - 71
    PORTK = 0xFF; // Enable pullup

    // 6 standard pins
    DDRG = 0x00;  // 72-77
    PORTG = 0x3F; // Enable pullup

    // Setup transmission and joystick pins
    PORTF = (1 << PF0) | (1 << PF3);                        // Enable pullup for the button pin (do before setting to output to prevent additional interrupt)
    DDRF = (1 << PF0)                                       // PF0 for transmission, PF1 for RX, PF2 for RY, PF3 for button
           | (1 << PF4) | (1 << PF5) | (1 << PF6) | (1 << PF7);    // PF4-PF7 as OUTPUT (energy saving)

    sei();

    high();        // Set line to high
    _delay_ms(10); // Wait until line normalizes

    // Transmit initial state
    send_initial_state();
    set_initial_state();
    // Keep up-to-date
    while (true)
    {
        refresh_state();
    }

    return 0;
}
