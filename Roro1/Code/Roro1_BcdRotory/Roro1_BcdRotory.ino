
#define pin1  GPIO_NUM_36
#define pin8  GPIO_NUM_39
#define pin2  GPIO_NUM_26
#define pin4  GPIO_NUM_27

void setup() {
  //setup serial
  Serial.begin(115200); 
  Serial.println("BCD values: ");

  //pin modes
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin8, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(pin1);
  int b = digitalRead(pin2);
  int c = digitalRead(pin4);
  int d = digitalRead(pin8);
  
  Serial.print(a);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.print(c);
  Serial.print(" ");
  Serial.println(d);
  delay(5000);
}
