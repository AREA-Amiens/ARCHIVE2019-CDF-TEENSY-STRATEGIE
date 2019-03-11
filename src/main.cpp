#include "strategie.h"

//maitre pas de scotch
byte etat=0,n=0,a=0;
int deplacment[20][3];
void setup() {
  deplacment[0][0]=540;
  deplacment[0][1]=2630;
  deplacment[0][2]=123;

  deplacment[1][0]=1350;
  deplacment[1][1]=2500;
  deplacment[1][2]=180;

  deplacment[2][0]=400;
  deplacment[2][1]=2500;
  deplacment[2][2]=180;

  deplacment[3][0]=450;
  deplacment[3][1]=2625;
  deplacment[3][2]=270;
  Wire.begin();
  Serial.begin(9600);

  delay(10000);//trasmition des diférante trame(3)
  Wire.requestFrom(adr_deplacement,1);
  etat=1;
}

void loop() {
  delay(1000);
  byte t[4],i;
  int e;
  switch (etat){
    case 1:
      etat=2;
    break;

    case 2:
    Wire.requestFrom(adr_deplacement,1);
    a=Wire.read();
      if (a==0){
        e=deplacment[n][2];
        t[1]=deplacment[n][0];
        t[2]=deplacment[n][1];
        t[3]=deplacment[n][2];
        t[0]=((deplacment[n][2]&=(1<<8))>>1);
        t[0]|=((deplacment[n][0]&=(0x700))>>4);
        t[0]|=((deplacment[n][1]&=(0xF00))>>8);
        Wire.beginTransmission(adr_deplacement);
        Wire.write(t[0]);
        Wire.write(t[1]);
        Wire.write(t[2]);
        Wire.write(t[3]);
        Wire.endTransmission();
        if(n==4)n=0;
      }
    break;
    case 3://prévision pour la carte adr_actionneur
    break;
  }
//Serial.println("la");
//  while(Wire.available()){//reception dune trame du mettre
//    Serial.println(Wire.read());
//  }
//  Serial.println(Wire.requestFrom(adr_deplacement,1));//recepetion dune trame

}
