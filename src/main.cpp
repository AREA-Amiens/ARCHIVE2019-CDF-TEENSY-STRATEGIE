#include "strategie.h"
//
//maitre pas de scotch
byte etat=0,n=0,a=0,b=0,depar;
int deplacment[20][4];
byte cote=coteRouge;
void setup() {
/* example pour deplacement
  deplacment[0][0]=2;//pour un deplacement
  deplacment[0][1]=1350;//x
  deplacment[0][2]=2700;//y
  deplacment[0][3]=90;//alpha agle par rappor a x sance trigo

  example pour ouverture
  deplacment[2][0]=3;//pour une action
  deplacment[2][1]=2;//quelle action faire*/
  pinMode(22, INPUT_PULLUP);

  deplacment[0][0]=2;
  deplacment[0][1]=1300;
  deplacment[0][2]=300;
  deplacment[0][3]=270;

  deplacment[1][0]=2;
  deplacment[1][1]=1300;
  deplacment[1][2]=500;
  deplacment[1][3]=180;

  deplacment[2][0]=3;
  deplacment[2][1]=2;
  deplacment[2][2]=130;

  deplacment[3][0]=2;
  deplacment[3][1]=500;
  deplacment[3][2]=500;
  deplacment[3][3]=180;

  deplacment[4][0]=3;
  deplacment[4][1]=2;
  deplacment[4][2]=80;

  deplacment[5][0]=2;
  deplacment[5][1]=450;
  deplacment[5][2]=300;
  deplacment[5][3]=90;

  deplacment[6][0]=3;
  deplacment[6][1]=2;
  deplacment[6][2]=120;

  deplacment[7][0]=2;
  deplacment[7][1]=450;
  deplacment[7][2]=500;
  deplacment[7][3]=90;



  Wire.begin();
  Serial.begin(9600);

  //delay(10000);//trasmition des diférante trame(3)
  Wire.requestFrom(adr_deplacement,1);
  etat=1;
  do{
    depar=digitalRead(22);
    delay(10);
    Serial.println(depar);
  }while(depar==1);

}

void loop() {

  byte t[4];
  int e;
  switch (etat){
    case 1:
      Wire.requestFrom(adr_deplacement,1);
      a=Wire.read();
      Wire.requestFrom(adr_actionneur,1);
      b=Wire.read();
      if (a==0&&b==0){
        etat=deplacment[n][0];
      }
    break;

    case 2:
      if(cote==coteRouge){
        deplacment[n][2]=3000-deplacment[n][2];
        deplacment[n][3]=360-deplacment[n][3];
      }
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
        t[1]=deplacment[n][2];
        Wire.beginTransmission(adr_actionneur);
        Wire.write(t[0]);
        Wire.write(t[1]);
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
