/*
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

volatile bool wait_over = false;
volatile uint8_t LPINA, LPINB, LPINC, LPIND, LPINE, LPINH, LPINJ, LPINL, LPINK, LPING;

ISR(TIMER2_COMPA_vect){
    wait_over = true;
}

inline void del(){
    while(!wait_over){}
    wait_over = false;
}

inline void high(){
    PORTF |= (1 << PF0);
    del();
}

inline void low(){
    PORTF &= ~(1 << PF0);
    del();
}

void send(uint8_t value) {
  bool bits[8];
  uint8_t i;
  for (i = 0; i < 8; i++) {
    bits[i] = (value & (1 << i));
  }
  // Start bit
  del();
  del();
  low();
  // Send all the data bits
  for(i = 0; i < 8; i++){
    if(bits[i]){
      high();
    }else{
      low();
    }
  }
  // Trigger last interrupt
  if (bits[7]) {
    low();
  } else {
    high();
  }
  // Stop Bit
  high();

}

void send_state(uint8_t pin, bool state){
    send(pin + 78 * state);
}

void send_initial_state(){
    send_state(0x00, PINA & (1 << PA0));
    send_state(0x01, PINA & (1 << PA1));
    send_state(0x02, PINA & (1 << PA2));
    send_state(0x03, PINA & (1 << PA3));
    send_state(0x04, PINA & (1 << PA4));
    send_state(0x05, PINA & (1 << PA5));
    send_state(0x06, PINA & (1 << PA6));
    send_state(0x07, PINA & (1 << PA7));

    send_state(0x08, PINB & (1 << PB0));
    send_state(0x09, PINB & (1 << PB1));
    send_state(0x0A, PINB & (1 << PB2));
    send_state(0x0B, PINB & (1 << PB3));
    send_state(0x0C, PINB & (1 << PB4));
    send_state(0x0D, PINB & (1 << PB5));
    send_state(0x0E, PINB & (1 << PB6));
    send_state(0x0F, PINB & (1 << PB7));

    send_state(0x10, PINC & (1 << PC0));
    send_state(0x11, PINC & (1 << PC1));
    send_state(0x12, PINC & (1 << PC2));
    send_state(0x13, PINC & (1 << PC3));
    send_state(0x14, PINC & (1 << PC4));
    send_state(0x15, PINC & (1 << PC5));
    send_state(0x16, PINC & (1 << PC6));
    send_state(0x17, PINC & (1 << PC7));

    send_state(0x18, PIND & (1 << PD0));
    send_state(0x19, PIND & (1 << PD1));
    send_state(0x1A, PIND & (1 << PD2));
    send_state(0x1B, PIND & (1 << PD3));
    send_state(0x1C, PIND & (1 << PD4));
    send_state(0x1D, PIND & (1 << PD5));
    send_state(0x1E, PIND & (1 << PD6));
    send_state(0x1F, PIND & (1 << PD7));

    send_state(0x20, PINE & (1 << PE0));
    send_state(0x21, PINE & (1 << PE1));
    send_state(0x22, PINE & (1 << PE2));
    send_state(0x23, PINE & (1 << PE3));
    send_state(0x24, PINE & (1 << PE4));
    send_state(0x25, PINE & (1 << PE5));
    send_state(0x26, PINE & (1 << PE6));
    send_state(0x27, PINE & (1 << PE7));

    send_state(0x28, PINH & (1 << PH0));
    send_state(0x29, PINH & (1 << PH1));
    send_state(0x2A, PINH & (1 << PH2));
    send_state(0x2B, PINH & (1 << PH3));
    send_state(0x2C, PINH & (1 << PH4));
    send_state(0x2D, PINH & (1 << PH5));
    send_state(0x2E, PINH & (1 << PH6));
    send_state(0x2F, PINH & (1 << PH7));

    send_state(0x30, PINJ & (1 << PJ0));
    send_state(0x31, PINJ & (1 << PJ1));
    send_state(0x32, PINJ & (1 << PJ2));
    send_state(0x33, PINJ & (1 << PJ3));
    send_state(0x34, PINJ & (1 << PJ4));
    send_state(0x35, PINJ & (1 << PJ5));
    send_state(0x36, PINJ & (1 << PJ6));
    send_state(0x37, PINJ & (1 << PJ7));

    send_state(0x38, PINL & (1 << PL0));
    send_state(0x39, PINL & (1 << PL1));
    send_state(0x3A, PINL & (1 << PL2));
    send_state(0x3B, PINL & (1 << PL3));
    send_state(0x3C, PINL & (1 << PL4));
    send_state(0x3D, PINL & (1 << PL5));
    send_state(0x3E, PINL & (1 << PL6));
    send_state(0x3F, PINL & (1 << PL7));

    send_state(0x40, PINK & (1 << PK0));
    send_state(0x41, PINK & (1 << PK1));
    send_state(0x42, PINK & (1 << PK2));
    send_state(0x43, PINK & (1 << PK3));
    send_state(0x44, PINK & (1 << PK4));
    send_state(0x45, PINK & (1 << PK5));
    send_state(0x46, PINK & (1 << PK6));
    send_state(0x47, PINK & (1 << PK7));

    send_state(0x48, PING & (1 << PG0));
    send_state(0x49, PING & (1 << PG1));
    send_state(0x4A, PING & (1 << PG2));
    send_state(0x4B, PING & (1 << PG3));
    send_state(0x4C, PING & (1 << PG4));
    send_state(0x4D, PING & (1 << PG5));
}

void refresh_state(){
    if((PINA & (1 << PA0)) != (LPINA & (1 << PA0))) { send_state(0x00, (PINA & (1 << PA0))); LPINA ^= 1 << PA0; }
    if((PINA & (1 << PA1)) != (LPINA & (1 << PA1))) { send_state(0x01, (PINA & (1 << PA1))); LPINA ^= 1 << PA1; }
    if((PINA & (1 << PA2)) != (LPINA & (1 << PA2))) { send_state(0x02, (PINA & (1 << PA2))); LPINA ^= 1 << PA2; }
    if((PINA & (1 << PA3)) != (LPINA & (1 << PA3))) { send_state(0x03, (PINA & (1 << PA3))); LPINA ^= 1 << PA3; }
    if((PINA & (1 << PA4)) != (LPINA & (1 << PA4))) { send_state(0x04, (PINA & (1 << PA4))); LPINA ^= 1 << PA4; }
    if((PINA & (1 << PA5)) != (LPINA & (1 << PA5))) { send_state(0x05, (PINA & (1 << PA5))); LPINA ^= 1 << PA5; }
    if((PINA & (1 << PA6)) != (LPINA & (1 << PA6))) { send_state(0x06, (PINA & (1 << PA6))); LPINA ^= 1 << PA6; }
    if((PINA & (1 << PA7)) != (LPINA & (1 << PA7))) { send_state(0x07, (PINA & (1 << PA7))); LPINA ^= 1 << PA7; }

    if((PINB & (1 << PB0)) != (LPINB & (1 << PB0))) { send_state(0x08, (PINB & (1 << PB0))); LPINB ^= 1 << PB0; }
    if((PINB & (1 << PB1)) != (LPINB & (1 << PB1))) { send_state(0x09, (PINB & (1 << PB1))); LPINB ^= 1 << PB1; }
    if((PINB & (1 << PB2)) != (LPINB & (1 << PB2))) { send_state(0x0A, (PINB & (1 << PB2))); LPINB ^= 1 << PB2; }
    if((PINB & (1 << PB3)) != (LPINB & (1 << PB3))) { send_state(0x0B, (PINB & (1 << PB3))); LPINB ^= 1 << PB3; }
    if((PINB & (1 << PB4)) != (LPINB & (1 << PB4))) { send_state(0x0C, (PINB & (1 << PB4))); LPINB ^= 1 << PB4; }
    if((PINB & (1 << PB5)) != (LPINB & (1 << PB5))) { send_state(0x0D, (PINB & (1 << PB5))); LPINB ^= 1 << PB5; }
    if((PINB & (1 << PB6)) != (LPINB & (1 << PB6))) { send_state(0x0E, (PINB & (1 << PB6))); LPINB ^= 1 << PB6; }
    if((PINB & (1 << PB7)) != (LPINB & (1 << PB7))) { send_state(0x0F, (PINB & (1 << PB7))); LPINB ^= 1 << PB7; }

    if((PINC & (1 << PC0)) != (LPINC & (1 << PC0))) { send_state(0x10, (PINC & (1 << PC0))); LPINC ^= 1 << PC0; }
    if((PINC & (1 << PC1)) != (LPINC & (1 << PC1))) { send_state(0x11, (PINC & (1 << PC1))); LPINC ^= 1 << PC1; }
    if((PINC & (1 << PC2)) != (LPINC & (1 << PC2))) { send_state(0x12, (PINC & (1 << PC2))); LPINC ^= 1 << PC2; }
    if((PINC & (1 << PC3)) != (LPINC & (1 << PC3))) { send_state(0x13, (PINC & (1 << PC3))); LPINC ^= 1 << PC3; }
    if((PINC & (1 << PC4)) != (LPINC & (1 << PC4))) { send_state(0x14, (PINC & (1 << PC4))); LPINC ^= 1 << PC4; }
    if((PINC & (1 << PC5)) != (LPINC & (1 << PC5))) { send_state(0x15, (PINC & (1 << PC5))); LPINC ^= 1 << PC5; }
    if((PINC & (1 << PC6)) != (LPINC & (1 << PC6))) { send_state(0x16, (PINC & (1 << PC6))); LPINC ^= 1 << PC6; }
    if((PINC & (1 << PC7)) != (LPINC & (1 << PC7))) { send_state(0x17, (PINC & (1 << PC7))); LPINC ^= 1 << PC7; }

    if((PIND & (1 << PD0)) != (LPIND & (1 << PD0))) { send_state(0x18, (PIND & (1 << PD0))); LPIND ^= 1 << PD0; }
    if((PIND & (1 << PD1)) != (LPIND & (1 << PD1))) { send_state(0x19, (PIND & (1 << PD1))); LPIND ^= 1 << PD1; }
    if((PIND & (1 << PD2)) != (LPIND & (1 << PD2))) { send_state(0x1A, (PIND & (1 << PD2))); LPIND ^= 1 << PD2; }
    if((PIND & (1 << PD3)) != (LPIND & (1 << PD3))) { send_state(0x1B, (PIND & (1 << PD3))); LPIND ^= 1 << PD3; }
    if((PIND & (1 << PD4)) != (LPIND & (1 << PD4))) { send_state(0x1C, (PIND & (1 << PD4))); LPIND ^= 1 << PD4; }
    if((PIND & (1 << PD5)) != (LPIND & (1 << PD5))) { send_state(0x1D, (PIND & (1 << PD5))); LPIND ^= 1 << PD5; }
    if((PIND & (1 << PD6)) != (LPIND & (1 << PD6))) { send_state(0x1E, (PIND & (1 << PD6))); LPIND ^= 1 << PD6; }
    if((PIND & (1 << PD7)) != (LPIND & (1 << PD7))) { send_state(0x1F, (PIND & (1 << PD7))); LPIND ^= 1 << PD7; }

    if((PINE & (1 << PE0)) != (LPINE & (1 << PE0))) { send_state(0x20, (PINE & (1 << PE0))); LPINE ^= 1 << PE0; }
    if((PINE & (1 << PE1)) != (LPINE & (1 << PE1))) { send_state(0x21, (PINE & (1 << PE1))); LPINE ^= 1 << PE1; }
    if((PINE & (1 << PE2)) != (LPINE & (1 << PE2))) { send_state(0x22, (PINE & (1 << PE2))); LPINE ^= 1 << PE2; }
    if((PINE & (1 << PE3)) != (LPINE & (1 << PE3))) { send_state(0x23, (PINE & (1 << PE3))); LPINE ^= 1 << PE3; }
    if((PINE & (1 << PE4)) != (LPINE & (1 << PE4))) { send_state(0x24, (PINE & (1 << PE4))); LPINE ^= 1 << PE4; }
    if((PINE & (1 << PE5)) != (LPINE & (1 << PE5))) { send_state(0x25, (PINE & (1 << PE5))); LPINE ^= 1 << PE5; }
    if((PINE & (1 << PE6)) != (LPINE & (1 << PE6))) { send_state(0x26, (PINE & (1 << PE6))); LPINE ^= 1 << PE6; }
    if((PINE & (1 << PE7)) != (LPINE & (1 << PE7))) { send_state(0x27, (PINE & (1 << PE7))); LPINE ^= 1 << PE7; }

    if((PINH & (1 << PH0)) != (LPINH & (1 << PH0))) { send_state(0x28, (PINH & (1 << PH0))); LPINH ^= 1 << PH0; }
    if((PINH & (1 << PH1)) != (LPINH & (1 << PH1))) { send_state(0x29, (PINH & (1 << PH1))); LPINH ^= 1 << PH1; }
    if((PINH & (1 << PH2)) != (LPINH & (1 << PH2))) { send_state(0x2A, (PINH & (1 << PH2))); LPINH ^= 1 << PH2; }
    if((PINH & (1 << PH3)) != (LPINH & (1 << PH3))) { send_state(0x2B, (PINH & (1 << PH3))); LPINH ^= 1 << PH3; }
    if((PINH & (1 << PH4)) != (LPINH & (1 << PH4))) { send_state(0x2C, (PINH & (1 << PH4))); LPINH ^= 1 << PH4; }
    if((PINH & (1 << PH5)) != (LPINH & (1 << PH5))) { send_state(0x2D, (PINH & (1 << PH5))); LPINH ^= 1 << PH5; }
    if((PINH & (1 << PH6)) != (LPINH & (1 << PH6))) { send_state(0x2E, (PINH & (1 << PH6))); LPINH ^= 1 << PH6; }
    if((PINH & (1 << PH7)) != (LPINH & (1 << PH7))) { send_state(0x2F, (PINH & (1 << PH7))); LPINH ^= 1 << PH7; }

    if((PINJ & (1 << PJ0)) != (LPINJ & (1 << PJ0))) { send_state(0x30, (PINJ & (1 << PJ0))); LPINJ ^= 1 << PJ0; }
    if((PINJ & (1 << PJ1)) != (LPINJ & (1 << PJ1))) { send_state(0x31, (PINJ & (1 << PJ1))); LPINJ ^= 1 << PJ1; }
    if((PINJ & (1 << PJ2)) != (LPINJ & (1 << PJ2))) { send_state(0x32, (PINJ & (1 << PJ2))); LPINJ ^= 1 << PJ2; }
    if((PINJ & (1 << PJ3)) != (LPINJ & (1 << PJ3))) { send_state(0x33, (PINJ & (1 << PJ3))); LPINJ ^= 1 << PJ3; }
    if((PINJ & (1 << PJ4)) != (LPINJ & (1 << PJ4))) { send_state(0x34, (PINJ & (1 << PJ4))); LPINJ ^= 1 << PJ4; }
    if((PINJ & (1 << PJ5)) != (LPINJ & (1 << PJ5))) { send_state(0x35, (PINJ & (1 << PJ5))); LPINJ ^= 1 << PJ5; }
    if((PINJ & (1 << PJ6)) != (LPINJ & (1 << PJ6))) { send_state(0x36, (PINJ & (1 << PJ6))); LPINJ ^= 1 << PJ6; }
    if((PINJ & (1 << PJ7)) != (LPINJ & (1 << PJ7))) { send_state(0x37, (PINJ & (1 << PJ7))); LPINJ ^= 1 << PJ7; }

    if((PINL & (1 << PL0)) != (LPINL & (1 << PL0))) { send_state(0x38, (PINL & (1 << PL0))); LPINL ^= 1 << PL0; }
    if((PINL & (1 << PL1)) != (LPINL & (1 << PL1))) { send_state(0x39, (PINL & (1 << PL1))); LPINL ^= 1 << PL1; }
    if((PINL & (1 << PL2)) != (LPINL & (1 << PL2))) { send_state(0x3A, (PINL & (1 << PL2))); LPINL ^= 1 << PL2; }
    if((PINL & (1 << PL3)) != (LPINL & (1 << PL3))) { send_state(0x3B, (PINL & (1 << PL3))); LPINL ^= 1 << PL3; }
    if((PINL & (1 << PL4)) != (LPINL & (1 << PL4))) { send_state(0x3C, (PINL & (1 << PL4))); LPINL ^= 1 << PL4; }
    if((PINL & (1 << PL5)) != (LPINL & (1 << PL5))) { send_state(0x3D, (PINL & (1 << PL5))); LPINL ^= 1 << PL5; }
    if((PINL & (1 << PL6)) != (LPINL & (1 << PL6))) { send_state(0x3E, (PINL & (1 << PL6))); LPINL ^= 1 << PL6; }
    if((PINL & (1 << PL7)) != (LPINL & (1 << PL7))) { send_state(0x3F, (PINL & (1 << PL7))); LPINL ^= 1 << PL7; }

    if((PINK & (1 << PK0)) != (LPINK & (1 << PK0))) { send_state(0x40, (PINK & (1 << PK0))); LPINK ^= 1 << PK0; }
    if((PINK & (1 << PK1)) != (LPINK & (1 << PK1))) { send_state(0x41, (PINK & (1 << PK1))); LPINK ^= 1 << PK1; }
    if((PINK & (1 << PK2)) != (LPINK & (1 << PK2))) { send_state(0x42, (PINK & (1 << PK2))); LPINK ^= 1 << PK2; }
    if((PINK & (1 << PK3)) != (LPINK & (1 << PK3))) { send_state(0x43, (PINK & (1 << PK3))); LPINK ^= 1 << PK3; }
    if((PINK & (1 << PK4)) != (LPINK & (1 << PK4))) { send_state(0x44, (PINK & (1 << PK4))); LPINK ^= 1 << PK4; }
    if((PINK & (1 << PK5)) != (LPINK & (1 << PK5))) { send_state(0x45, (PINK & (1 << PK5))); LPINK ^= 1 << PK5; }
    if((PINK & (1 << PK6)) != (LPINK & (1 << PK6))) { send_state(0x46, (PINK & (1 << PK6))); LPINK ^= 1 << PK6; }
    if((PINK & (1 << PK7)) != (LPINK & (1 << PK7))) { send_state(0x47, (PINK & (1 << PK7))); LPINK ^= 1 << PK7; }

    if((PING & (1 << PG0)) != (LPING & (1 << PG0))) { send_state(0x48, (PING & (1 << PG0))); LPING ^= 1 << PG0; }
    if((PING & (1 << PG1)) != (LPING & (1 << PG1))) { send_state(0x49, (PING & (1 << PG1))); LPING ^= 1 << PG1; }
    if((PING & (1 << PG2)) != (LPING & (1 << PG2))) { send_state(0x4A, (PING & (1 << PG2))); LPING ^= 1 << PG2; }
    if((PING & (1 << PG3)) != (LPING & (1 << PG3))) { send_state(0x4B, (PING & (1 << PG3))); LPING ^= 1 << PG3; }
    if((PING & (1 << PG4)) != (LPING & (1 << PG4))) { send_state(0x4C, (PING & (1 << PG4))); LPING ^= 1 << PG4; }
    if((PING & (1 << PG5)) != (LPING & (1 << PG5))) { send_state(0x4D, (PING & (1 << PG5))); LPING ^= 1 << PG5; }
}

void set_last_state(){
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
}
int main(void)
{
    int i=0;
    cli();
    // Set up timer for 10000 Baud
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    OCR2A = 199;
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS21);
    TIMSK2 |= (1 << OCIE2A);
    sei();
    // Set up pins
    // Set up pins for keys

    // 8x(8 standard pins)
    DDRA = 0x00; // 0 - 7
    PORTA = 0xFF;// Enable pullup
    DDRB = 0x00; // 8 - 15
    PORTB = 0xFF;// Enable pullup
    DDRC = 0x00; // 16 - 23
    PORTC = 0xFF;// Enable pullup
    DDRD = 0x00; // 24 - 31
    PORTD = 0xFF;// Enable pullup
    DDRE = 0x00; // 32 - 39
    PORTE = 0xFF;// Enable pullup
    DDRH = 0x00; // 40 - 47
    PORTH = 0xFF;// Enable pullup
    DDRJ = 0x00; // 48 - 55
    PORTJ = 0xFF;// Enable pullup
    DDRL = 0x00; // 56 - 63
    PORTL = 0xFF;// Enable pullup

    // 8 analog-able pins
    DDRK = 0x00; // 64 - 71
    PORTK = 0xFF;// Enable pullup

    // 6 standard pins
    DDRG = 0x00; // 72-77
    PORTG = 0x3F;// Enable pullup

    // Setup transmission and joystick pins
    DDRF = 0x01; // PF0 for transmission, remaining for input

    high(); // Set line to high
    _delay_ms(10); // Wait until line normalizes

    // Transmit initial state
    send_initial_state();
    set_last_state();

    // Keep up-to-date
    while(true){
        refresh_state();
    }

    return 0;
}

