// Objective: Use a shift register to control a 7 segment LED display, incrementing the number 0-9

// Completed: Works

int states[10] = {0x01, 0xC7, 0x22, 0x82, 0xC4, 0x88, 0x08, 0xC3, 0x00, 0x80};

void setup() {
  pinMode(4, OUTPUT);  // CLK
  pinMode(7, OUTPUT);  // Data
  Serial.begin(9600);
  delay(250);
}

void load_sr(int state, int shift)
{
   digitalWrite(4, LOW);
   for(uint8_t i = 0; i < shift; i++)  // For loop to accumulate values in the shift register
   {
     digitalWrite(7, (state >> i) & 1);
     Serial.println("1");
     digitalWrite(4, HIGH);
     Serial.println("2");
     delay(1);
     digitalWrite(4, LOW);
     Serial.println("3");
   }
}

void loop() {
  for(uint8_t i = 10; i; i--)
  {
    load_sr(states[i - 1], 8);
    Serial.println("A load_sr" + String(i));
    delay(1000);
  }
}
