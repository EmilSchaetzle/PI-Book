volatile bool wait_over = false;
void setup() {
  cli();
  // Set up timer for 10000 Baud
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 199;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS21);
  TIMSK2 |= (1 << OCIE2A);
  pinMode(0, OUTPUT);  
  sei();
  high();
  delay(10000);
  for (int i = 0; i < 25600; i++) {
    send(i % 256);
  }
}
void loop() {}
void send(byte key) {
  byte bits[8];
  for (int i = 0; i < 8; i++) {
    bits[i] = bitRead(key, i);
  }
  // Start bit
  del();
  low();
  // Send all the data bits
  for(int i=0; i<8;i++){
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
  del();
}
inline void low() {
  del();
  PORTE &= ~_BV(PE0);
}
inline void high() {
  del();
  PORTE |= _BV(PE0);
}
inline void del() {
  while (!wait_over) {}
  wait_over = false;
}
ISR(TIMER2_COMPA_vect) {
  wait_over = true;
}
