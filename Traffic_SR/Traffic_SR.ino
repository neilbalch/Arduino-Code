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
const int t_G = 3;
const int t_Y = 2;
const int t_R = t_G + t_Y;

void setup() {
  pinMode(4, OUTPUT);  // CLK
  pinMode(7, OUTPUT);  // Data
  Serial.begin(9600);
  delay(250);
}

void load_sr(int led_state[6])
{
   digitalWrite(4, LOW);
   for(uint8_t i = 6; i; i--)  // For loop to accumulate values in the shift register
   {
     digitalWrite(7, led_state[i-1]);
     digitalWrite(4, HIGH);
     delay(1);
     digitalWrite(4, LOW);
   }
}



void loop() {
  int st_1G = 1;
  int st_1Y = 1;
  int st_1R = 1;
  int st_2G = 1;
  int st_2Y = 1;
  int st_2R = 1;
  for(uint8_t i = 0; i < (t_R * 2); i++)  // State Counter (variable 'i' is counter)
  {
    //  Find where we are in Sequence for Light Set 1
    if(i > 4)       // Red State
    {
      st_1G = 1;
      st_1Y = 1;
      st_1R = 0;
    }  
    else if(i > 2)  // Yellow State
    {
      st_1G = 1;
      st_1Y = 0;
      st_1R = 1;
    }           
    else            // Green State
    {
      st_1G = 0;
      st_1Y = 1;
      st_1R = 1;
    }
    //  Find where we are in Sequence for Light Set 2
    if(i < 5)       // Red State
    {
      st_2G = 1;
      st_2Y = 1;
      st_2R = 0;
    }  
    else if(i > 7)  // Yellow State
    {
      st_2G = 1;
      st_2Y = 0;
      st_2R = 1;
    }           
    else            // Green State
    {
      st_2G = 0;
      st_2Y = 1;
      st_2R = 1;
    }
    
    //  Make a long integer array from the bits
    int assembleTemp[6] = {st_1G, st_1Y, st_1R, st_2G, st_2Y, st_2R};
    load_sr(assembleTemp);
    delay(1000);
  }
}
