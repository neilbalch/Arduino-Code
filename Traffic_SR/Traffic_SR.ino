// Objective: Use a shift register to control two sets of "Traffic lights", going through the rotation of different lights
// Completed: Works

/*
**  Important Note:
**  The order of the lights in the shift register is as follows
**          1st Set | 2nd Set
**    D-- |-------------------|
**        |  G Y R  |  G Y R  |
**    Q-- |-------------------|
*/

// Set timing for each light
const uint8_t t_G = 3;
const uint8_t t_Y = 2;
const uint8_t t_R = t_G + t_Y;

void setup() {
  pinMode(4, OUTPUT);  // CLK
  pinMode(7, OUTPUT);  // Data
  Serial.begin(9600);
  delay(250);
}

void load_sr(uint8_t led_state[6]) {
   digitalWrite(4, LOW);
   for(uint8_t i = 6; i; i--) { // For loop to accumulate values in the shift register
     digitalWrite(7, led_state[i-1]);
     digitalWrite(4, HIGH);
     //delay(1);
     digitalWrite(4, LOW);
   }
}

void loop() {
  uint8_t light1[] = {0 /* G */, 0 /* Y */, 0 /* R */ };
  uint8_t light2[] = {0 /* G */, 0 /* Y */, 0 /* R */ };
  
  for(uint8_t i = 0; i < (t_R * 2); i++) { // State Counter (variable 'i' is counter)
    //  Find where we are in Sequence for Light Set 1
    if(i > 4) {         // Red State
      light1[0] = 1;
      light1[1] = 1;
      light1[2] = 0;
    } else if(i > 2) {  // Yellow State
      light1[0] = 1;
      light1[1] = 0;
      light1[2] = 1;
    } else {            // Green State
      light1[0] = 0;
      light1[1] = 1;
      light1[2] = 1;
    }
    //  Find where we are in Sequence for Light Set 2
    if(i < 5) {         // Red State
      light2[0] = 1;
      light2[1] = 1;
      light2[2] = 0;
    } else if(i > 7) {  // Yellow State
      light2[0] = 1;
      light2[1] = 0;
      light2[2] = 1;
    } else {            // Green State
      light2[0] = 0;
      light2[1] = 1;
      light2[2] = 1;
    }
    
    //  Make a long integer array from the bits
    uint8_t assembleTemp[6] = {light1[0], light1[1], light1[2], light2[0], light2[1], light2[2]};
    load_sr(assembleTemp);
    delay(1000);
  }
}
