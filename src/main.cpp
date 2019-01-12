#include "strategie.h"

//maitre pas de scotch

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(adr_deplacement);
  Wire.write('N');
  Wire.endTransmission();
  Wire.requestFrom(adr_deplacement,1);
  while(Wire.available()){
    Serial.println(Wire.read());
  }
  delay(2000);
}
