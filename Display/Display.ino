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
  debug_print("Wait for keypress");
  while(digitalRead(13) == LOW)
  {
   delay(100); 
  }
  delay(1000);
*/
}

void debug_print(String message) {
//  Serial.println(message);
}

void write4b(int RS, int data, bool checkBusy){
  int busy = true;
  while(checkBusy && busy){
    digitalWrite(RS_pin, LOW);
    digitalWrite(RW_pin, HIGH);
    digitalWrite(E_pin, HIGH);
    debug_print("debug 0");
    debug_wait(); delay(1);
    busy = digitalRead(DB4_pin + 3);
    digitalWrite(E_pin, LOW);
    debug_print("debug 1");
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
  debug_print("debug 2");
  debug_wait(); delay(1);
  digitalWrite(E_pin, LOW);
  for(int i = 0; i <= 3; i++){
    pinMode(DB4_pin + i, INPUT);
  }
  debug_print("debug 3");
  debug_wait(); delay(1);
}

void write8b(int RS, int data){
  write4b(RS, (data & 0xf0) >> 4, true);
  write4b(RS, data & 0xf, false);
}

void initialize(){
  delay(15);
  debug_print("init 1");
  write4b(0, 0x3, false);
  delay(4);
  debug_print("init 2");
  write4b(0, 0x3, false);
  delay(1);
  debug_print("init 3");
  write4b(0, 0x3, false);
  debug_print("init 4");
  write4b(0, 0x2, true);
  debug_print("init 5");
  write8b(0, 0x24);  // n = 0, F = 1
  debug_print("init 6");
  write8b(0, 0x08);
  debug_print("init 7");
  write8b(0, 0x01);
  debug_print("init 8");
  write8b(0, 0x06);  // ID = 1, S= 0
  debug_print("init 9");
  write8b(0, 0x0f);  // C = 1, R = 1
  debug_print("init 10");
}

void displayStr(String string){
  write8b(0, 0x01); // Clear Display
  write8b(0, 0x80); // Set DD Ram address to 0
  for(int i = 0; i < string.length(); i++){
    write8b(1, string[i]);
  }
}

void loadCG(uint8_t charNum, uint8_t len, uint8_t customChar[10]){
  uint8_t cg_addr;
  cg_addr = 0x40 | ((charNum << 4) & 0x30);
  write8b(0, cg_addr);
  for(uint8_t i = 0; i < len; i++)
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
  displayStr("Hello World");
  delay(2000);
  //displayStr("----- -----");
  //delay(2000);
  
  uint8_t zero[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  loadCG(0, 10, zero);
  loadCG(1, 10, zero);
  loadCG(2, 10, zero);
  loadCG(3, 10, zero);

  uint8_t box[10] = {0x1f, 0x15, 0x15, 0x1f, 0x15, 0x15, 0x1f, 0, 0, 0};
  //uint8_t slash[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x01, 0x02, 0, 0, 0};
  uint8_t slash[10] = {0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10};
  uint8_t frame[10] = {0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f, 0, 0, 0};
  uint8_t smileFace[10] = {0x00, 0x00, 0x00, 0x11, 0x00, 0x11, 0xe, 0, 0, 0};

  loadCG(0, 10, box);
  loadCG(1, 10, slash);
  loadCG(2, 10, frame);
  loadCG(3, 10, smileFace);
  
  write8b(0, 0x01); // Clear Display
  write8b(0, 0x80); // Set DD Ram address to 0
  write8b(1, 0x00); //Smiley
  write8b(1, 0x02); //Frame
  write8b(1, 0x04); //Slash
  write8b(1, 0x06); //Box
  write8b(1, 0x08);
  write8b(1, 0x0a);
  write8b(1, 0x0c);
  write8b(1, 0x0e);
  write8b(1, 0x41); //A
  write8b(1, 0x48); //H
  delay(10000);
}
