const uint8_t ledPin = PB5;

// Zero quantity used to reset the timer intially and after compare interrupt handled
const uint16_t t1_load = 0;
// T1 timer will rise to this quantity before triggering the compare interrupt
const uint16_t t1_comp = 0.5 /*s*/ * 16000000 /*Hz*/ / 256 /*prescaler*/;

void setup() {
  // Set LED pin to output
  DDRB |= (1 << ledPin); // DataDirectionRegisterB

  // Rest Timer1 control register A
  TCCR1A = 0; // TimerCounterControlRegister1A

  // Set Timer1 prescalar to 256
  TCCR1B |= (1 << CS12);  // TimerCounterControlRegister1B
  TCCR1B &= ~(1 << CS11); // TimerCounterControlRegister1B
  TCCR1B &= ~(1 << CS10); // TimerCounterControlRegister1B

  // Reset Timer1 and set comp value
  TCNT1 = t1_load;  // TimerCouNTer1
  OCR1A = t1_comp;  // OutputCompareRegister1A

  // Enable Timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A); // Timer/counterMaSK1

  // Enable global interruptss
  sei();
}

void loop() {
  delay(500);
}

ISR(TIMER1_COMPA_vect) {
  // Reset Timer1 count
  TCNT1 = t1_load; // TimerCouNTer1
  
  // Toggle LED pin
  PORTB ^= (1 << ledPin);
}
