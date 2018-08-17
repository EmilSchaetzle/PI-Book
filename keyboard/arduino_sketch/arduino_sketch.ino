const int pin = 0;
const int baud = 5000;
void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  for (int i = 0; i < 25600; i++) {
    send(i % 256);
  }

}
void loop() {}
void send(byte key) {
  // Start bit
  digitalWrite(pin, LOW);
  delayMicroseconds(1000000 / baud);
  for (int i = 0; i < 8; i++) {
    digitalWrite(pin, bitRead(key, i));
    delayMicroseconds(1000000 / baud);
  }
  // Trigger last interrupt
  digitalWrite(pin, !bitRead(key, 7));
  delayMicroseconds(1000000 / baud);
  // Set back to high
  digitalWrite(pin, HIGH);
  delayMicroseconds(1000000 / baud);
}

