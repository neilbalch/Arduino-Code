const uint8_t ledPin = PB5; // Translates to pin 13 on Arduino Uno, the onboard LED.

// Zero quantity used to reset the timer intially and after compare interrupt handled
const uint16_t t1_load = 0;

const double delayTime = 0.25; // sec
const uint16_t clock_freq = 16000000; // Hz
const uint8_t prescaler = 256; // prescaler
// T1 timer will rise to this quantity before triggering the compare interrupt
const uint16_t t1_comp = delayTime * (clock_freq / prescaler);

void setup() {
  // Set LED pin to output
  DDRB |= (1 << ledPin); // DataDirectionRegisterB

  // Rest Timer1 control register A, we don't use any of the features it controls
  TCCR1A = 0; // TimerCounterControlRegister1A

  // Set Timer1 prescaler to 256
  TCCR1B |= /*OR*/ (1 << CS12);  // TimerCounterControlRegister1B
  TCCR1B &= /*NAND*/ ~(1 << CS11); // TimerCounterControlRegister1B
  TCCR1B &= /*NAND*/ ~(1 << CS10); // TimerCounterControlRegister1B

  // Reset value of Timer1 and set "Output Compare Register" value
  TCNT1 = t1_load;  // TimerCouNTer1
  OCR1A = t1_comp;  // OutputCompareRegister1A

  // Enable Timer1 "Output Compare Tnterrupt Enable"
  TIMSK1 = (1 << OCIE1A); // Timer/counterMaSK1

  // Enable global interruptss
  sei();
}

void loop() {
  delay(10000); // Simulate the processor being really busy...
}

ISR(TIMER1_COMPA_vect) {
  // Reset Timer1 count
  TCNT1 = t1_load; // TimerCouNTer1
  
  // Toggle LED pin
  PORTB ^= /*XOR*/ (1 << ledPin);
}
