/*
 Name:      Roro1_NeoPixel-flash.ino
 Created:   2020/08/23
 Description: 
 - Basic Battery voltage measurement test
*/

#define BATPIN    GPIO_NUM_4  //bat voltage

void setup() {
  //setup serial
  Serial.begin(115200); 
  Serial.println("RORO1 Voltage measurement starting...");
}

void loop() {
  Serial.print("BATV=");
  Serial.println(measureBattery());
  delay(5000);
}

/* ===================================================================
  measureBattery() gets the battery level
====================================================================== */
String measureBattery() {
  String bat;
  float _bat;
  for(int i=0; i<=5; i++){
    _bat = analogRead(BATPIN);
    delay(100);
  }
  _bat = (_bat/565); //527=4.26 |540=4.13 |550=4.06 |555=4.04 |560=4.03
  bat = (String)_bat;
  return bat;
}
