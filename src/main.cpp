#include "strategie.h"
//
//maitre pas de scotch
byte etat=0,n=0,a=0,b=0;
int deplacment[20][4];
void setup() {
/* example pour deplacement
  deplacment[0][0]=2;//pour un deplacement
  deplacment[0][1]=1350;//x
  deplacment[0][2]=2700;//y
  deplacment[0][3]=90;//alpha agle par rappor a x sance trigo

  example pour ouverture
  deplacment[2][0]=3;//pour une action
  deplacment[2][1]=2;//quelle action faire*/


  deplacment[0][0]=2;//pour un deplacement
  deplacment[0][1]=1350;//x
  deplacment[0][2]=2700;//y
  deplacment[0][3]=90;//alpha agle par rappor a x sance trigo

  deplacment[1][0]=2;
  deplacment[1][1]=1350;
  deplacment[1][2]=2500;
  deplacment[1][3]=180;

  deplacment[2][0]=3;//pour une action
  deplacment[2][1]=2;//quelle action faire

  deplacment[3][0]=2;
  deplacment[3][1]=465;
  deplacment[3][2]=2500;
  deplacment[3][3]=180;

  deplacment[4][0]=2;
  deplacment[4][1]=450;
  deplacment[4][2]=2700;
  deplacment[4][3]=270;
  Wire.begin();
  Serial.begin(9600);

  delay(10000);//trasmition des diférante trame(3)
  Wire.requestFrom(adr_deplacement,1);
  etat=1;


}

void loop() {

  byte t[4],i;
  int e;
  switch (etat){
    case 1:
      Wire.requestFrom(adr_deplacement,1);
      a=Wire.read();
      Wire.requestFrom(adr_actionneur,1);
      b=Wire.read();
      Serial.print("a :");
      Serial.print(a);
      Serial.print(" b :");
      Serial.println(b);
      if (a==0&&b==0){
        etat=deplacment[n][0];
      }
    break;

    case 2:

        e=deplacment[n][2];
        t[1]=deplacment[n][1];
        t[2]=deplacment[n][2];
        t[3]=deplacment[n][3];
        t[0]=((deplacment[n][3]&=(1<<8))>>1);
        t[0]|=((deplacment[n][1]&=(0x700))>>4);
        t[0]|=((deplacment[n][2]&=(0xF00))>>8);
        Wire.beginTransmission(adr_deplacement);
        Wire.write(t[0]);
        Wire.write(t[1]);
        Wire.write(t[2]);
        Wire.write(t[3]);
        Wire.endTransmission();
        n++;
        etat=1;
    break;
    case 3://prévision pour la carte adr_actionneur

        t[0]=deplacment[n][1];
        Wire.beginTransmission(adr_actionneur);
        Wire.write(t[0]);
        Wire.endTransmission();
        etat=1;
        n++;
      etat=1;
    break;
  }
//Serial.println("la");
//  while(Wire.available()){//reception dune trame du mettre
//    Serial.println(Wire.read());
//  }
//  Serial.println(Wire.requestFrom(adr_deplacement,1));//recepetion dune trame

}
