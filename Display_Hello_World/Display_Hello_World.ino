// Objective: Print text to an external LCD screen, (Mitsubishi HD44780) without a library over a custom data bus 
// Unfinished: WIP

const int RS_pin = 2;
const int RW_pin = 3;
const int E_pin = 4;
const int DB4_pin = 8;

void debug_wait(){
/*
  delay(300);
  //wait for a button press on an input pin
  Serial.println("Wait for keypress");
  while(digitalRead(13) == LOW)
  {
   delay(100); 
  }
  delay(1000);
*/
}


void write4b(int RS, int data, bool checkBusy){
  int busy = true;
  while(checkBusy && busy){
    digitalWrite(RS_pin, LOW);
    digitalWrite(RW_pin, HIGH);
    digitalWrite(E_pin, HIGH);
    Serial.println("debug 0");
    debug_wait(); delay(1);
    busy = digitalRead(DB4_pin + 3);
    digitalWrite(E_pin, LOW);
    Serial.println("debug 1");
    debug_wait(); delay(1);
  }
  digitalWrite(RS_pin, RS);
  digitalWrite(RW_pin, 0);
  for(int i = 0; i <= 3; i++){
    pinMode(DB4_pin + i, OUTPUT);
  }
  for(uint8_t i = 0; i <= 3; i++)
  {
    digitalWrite(DB4_pin + i, data & 1<<i);
  }
  digitalWrite(E_pin, HIGH);
  Serial.println("debug 2");
  debug_wait(); delay(1);
  digitalWrite(E_pin, LOW);
  for(int i = 0; i <= 3; i++){
    pinMode(DB4_pin + i, INPUT);
  }
  Serial.println("debug 3");
  debug_wait(); delay(1);
}

void write8b(int RS, int data){
  write4b(RS, (data & 0xf0) >> 4, true);
  write4b(RS, data & 0xf, false);
}

void initialize(){
  delay(15);
  Serial.println("init 1");
  write4b(0, 0x3, false);
  delay(4);
  Serial.println("init 2");
  write4b(0, 0x3, false);
  delay(1);
  Serial.println("init 3");
  write4b(0, 0x3, false);
  Serial.println("init 4");
  write4b(0, 0x2, true);
  Serial.println("init 5");
  write8b(0, 0x24);  // n = 0, F = 1
  Serial.println("init 6");
  write8b(0, 0x08);
  Serial.println("init 7");
  write8b(0, 0x01);
  Serial.println("init 8");
  write8b(0, 0x06);  // ID = 1, S= 0
  Serial.println("init 9");
  write8b(0, 0x0f);  // C = 1, R = 1
  Serial.println("init 10");
}

void displayStr(String string){
  write8b(0, 0x01); // Clear Display
  write8b(0, 0x80); // Set DD Ram address to 0
  for(int i = 0; i < string.length(); i++){
    write8b(1, string[i]);
  }
}

void loadCG(uint8_t customChar[10], uint8_t charNum){
  write8b(0, ((0x01 & 3) << 6) + ((charNum & 3) << 4) + (0x00 & 0xf)); // W CG Ram
  for(uint8_t i = 0; i > 10; i++)
  {
    write8b(1, customChar[i]);
  }
}

void setup() {
  pinMode(RS_pin, OUTPUT);
  pinMode(RW_pin, OUTPUT);
  pinMode(E_pin, OUTPUT);
  pinMode(DB4_pin, INPUT);
  pinMode(DB4_pin + 1, INPUT);
  pinMode(DB4_pin + 2, INPUT);
  pinMode(DB4_pin + 3, INPUT);
  Serial.begin(9600);
  delay(250);
  initialize();
}


void loop() {
  /*
  Serial.println("LP0");
  uint8_t smileFace[10] = {0x00, 0x00, 0x00, 0x11, 0x00, 0x11, 0xe, 0x00, 0x00, 0x00};
  Serial.println("LP1");
  loadCG(smileFace, 0);
  Serial.println("LP2");
  */
  displayStr("Hello World ");
  //Serial.println("LP3");
  //write8b(1, 0x00);
  delay(5000);
}
