#include "strategie.h"

//
//maitre pas de scotch
byte etat=0,m=1,a=1,b=0,depar,np,u[4];
boolean verifier(false),clic(false),pase=false;
int deplacment[40][6];
String s;
int val,menu,menu1=0,cMenu=1,menu2=0,menu3=0,menu4=0,strategie=0;
int PinCLK = 3;
int PinDT = 4;
int PinSW = 5;
static long encoderPos = 0;    // Au 1er démarrage, il passera à 0
int PinCLKLast = LOW,PinSWLast=LOW;
int nbPas = 20;                 // Résolution de l'encodeur
int n = LOW,n1=LOW;
int ndep,Time2;
byte cote=coteRouge;
boolean vEguille=false,vTierete=false,vMoteurGauche=false,vMoteurDroit=false,vCarte=false,vActionneur=false,vExperience=false,vRoboPlacer;

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 12, /* reset=*/ 8);




void setup() {
  delay(1000);

/* example pour deplacement
  deplacment[0][0]=2;//pour un deplacement
  deplacment[0][1]=1350;//x
  deplacment[0][2]=2700;//y
  deplacment[0][3]=90;//alpha agle par rappor a x sance trigo

  example pour ouverture
  deplacment[2][0]=3;//pour une action
  deplacment[2][1]=2;//quelle action faire*/
  pinMode(22, INPUT_PULLUP);
//  deplacment[1][0]=3;
//deplacment[1][1]=14;
//deplacment[1][2]=0;

deplacment[1][0]=2;
deplacment[1][1]=1300;
deplacment[1][2]=300;
deplacment[1][3]=270;
deplacment[1][4]=0;

deplacment[2][0]=2;
deplacment[2][1]=1300;
deplacment[2][2]=500;
deplacment[2][3]=180;
deplacment[2][4]=0;

deplacment[3][0]=3;
deplacment[3][1]=2;
deplacment[3][2]=130;

deplacment[4][0]=2;
deplacment[4][1]=500;
deplacment[4][2]=500;
deplacment[4][3]=180;
deplacment[4][4]=0;


deplacment[5][0]=3;
deplacment[5][1]=2;
deplacment[5][2]=80;

deplacment[6][0]=2;
deplacment[6][1]=450;
deplacment[6][2]=300;
deplacment[6][3]=90;
deplacment[6][4]=0;


deplacment[7][0]=3;
deplacment[7][1]=2;
deplacment[7][2]=120;

deplacment[8][0]=2;
deplacment[8][1]=450;
deplacment[8][2]=450;
deplacment[8][3]=90;
deplacment[8][4]=0;

deplacment[9][0]=3;
deplacment[9][1]=2;
deplacment[9][2]=0;

deplacment[10][0]=2;
deplacment[10][1]=1378;
deplacment[10][2]=200;
deplacment[10][3]=0;
deplacment[10][4]=0;//16

deplacment[11][0]=2;
deplacment[11][1]=1373;
deplacment[11][2]=200;
deplacment[11][3]=270;
deplacment[11][4]=0;//21

deplacment[12][0]=2;
deplacment[12][1]=1378;
deplacment[12][2]=500;
deplacment[12][3]=270;
deplacment[12][4]=0;

deplacment[13][0]=3;
deplacment[13][1]=2;
deplacment[13][2]=10;

deplacment[14][0]=2;
deplacment[14][1]=1378;
deplacment[14][2]=600;
deplacment[14][3]=270;
deplacment[14][4]=0;

deplacment[15][0]=3;
deplacment[15][1]=2;
deplacment[15][2]=0;

deplacment[16][0]=2;
deplacment[16][1]=1378;
deplacment[16][2]=700;
deplacment[16][3]=270;
deplacment[16][4]=0;

deplacment[17][0]=3;
deplacment[17][1]=2;
deplacment[17][2]=10;

deplacment[18][0]=2;
deplacment[18][1]=1378;
deplacment[18][2]=800;
deplacment[18][3]=270;
deplacment[18][4]=0;

deplacment[19][0]=3;
deplacment[19][1]=2;
deplacment[19][2]=0;

deplacment[20][0]=2;
deplacment[20][1]=1378;
deplacment[20][2]=900;
deplacment[20][3]=270;
deplacment[20][4]=0;

deplacment[21][0]=3;
deplacment[21][1]=2;
deplacment[21][2]=10;

deplacment[22][0]=2;
deplacment[22][1]=1378;
deplacment[22][2]=1000;
deplacment[22][3]=270;
deplacment[22][4]=0;

deplacment[23][0]=3;
deplacment[23][1]=2;
deplacment[23][2]=0;

deplacment[24][0]=2;
deplacment[24][1]=1418;
deplacment[24][2]=1320;
deplacment[24][3]=270;
deplacment[24][4]=0;

deplacment[25][0]=3;
deplacment[25][1]=2;
deplacment[25][2]=80;

deplacment[26][0]=3;
deplacment[26][1]=2;
deplacment[26][2]=0;

deplacment[27][0]=2;
deplacment[27][1]=1228;
deplacment[27][2]=1380;
deplacment[27][3]=135;
deplacment[27][4]=0;

deplacment[29][0]=2;
deplacment[29][1]=1300;
deplacment[29][2]=1300;
deplacment[29][3]=315;
deplacment[29][4]=0;

deplacment[30][0]=2;
deplacment[30][1]=400;
deplacment[30][2]=450;
deplacment[30][3]=270;
deplacment[30][4]=0;

  Wire.begin();
  Serial.begin(9600);

  //delay(10000);//trasmition des diférante trame(3)

  u8g2.begin();
  MsTimer2::set(1000,IntrerrupTimer);//tout les  seconde
  MsTimer2::start();
  pinMode (PinCLK,INPUT_PULLUP);
  pinMode (PinDT,INPUT_PULLUP);
  pinMode (PinSW,INPUT_PULLUP);
  Serial.begin (9600);
  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(30,30,"AREA");
  //  u8g2.blink(); //clignoter le msg
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(2000);
  //menu
  while(!verifier){
    Serial.println("1");
    clic=false;
    np=encoderPos;
    n1=digitalRead(PinSW);
    if (PinSWLast==LOW && n1==HIGH) {      // Reset la position si on appui sur le potentiomètre
      clic=true;
      if(cMenu==4){
        switch (menu4) {
          case 0:
            vEguille=true;
            encoderPos++;
          break;
          case 1:
            vTierete=true;
            encoderPos++;
          break;
          case 2:
            vMoteurDroit=true;
            encoderPos++;
          break;
          case 3:
            vMoteurGauche=true;
            encoderPos++;
          break;
          case 4:
            vCarte=true;
            encoderPos++;
          break;
          case 5:
            vActionneur=true;
            encoderPos++;
          break;
          case 6:
            vExperience=true;
            encoderPos++;
          break;
          case 7:
            vRoboPlacer=true;
            encoderPos++;
          break;
          case 8:
            cMenu=3;
            encoderPos=0;
          break;
          case 9:
            if(vEguille&&vTierete&&vMoteurDroit&&vMoteurGauche&&vCarte&&vActionneur&&vExperience&&vRoboPlacer){
              verifier=true;
            }
          break;
        }
      }
      if(cMenu==1){cMenu=menu+2;encoderPos=0;}
      if(cMenu==3&&menu2==4){cMenu=1;encoderPos=0;}
      if(cMenu==2&&menu1==3){cMenu=1;encoderPos=0;}
      if(cMenu==2&&menu2==2){cMenu=4;encoderPos=0;}
      if(cMenu==2&&menu1==0){
        if(cote==coteBleu)cote=coteRouge;
        else cote=coteBleu;
      }
      if(cMenu==2&&menu1==1){
        strategie++;
        if (strategie==11)strategie=0;
      }

    //  encoderPos=0;
      menu=encoderPos;
      menu1=encoderPos;
      menu2=encoderPos;
      menu3=encoderPos;
      menu4=encoderPos;

    }
    n = digitalRead(PinCLK);
    if ((PinCLKLast == LOW) && (n == HIGH)) {
      if (digitalRead(PinDT) == LOW) {
        encoderPos++;
      }
      else {
        encoderPos--;
      }
    }
    PinCLKLast = n;
    PinSWLast=n1;
    delay(10);
    if(encoderPos!=np||clic){
      switch(cMenu){
        case 1:
          if(encoderPos==2)encoderPos=0;
          if(encoderPos==-1)encoderPos=1;
          menu=encoderPos;
        break;
        case 2:
          if(encoderPos==4)encoderPos=0;
          if(encoderPos==-1)encoderPos=3;
          menu1=encoderPos;
        break;
        case 3:
          if(encoderPos==5)encoderPos=0;
          if(encoderPos==-1)encoderPos=4;
          menu3=encoderPos;
        break;
        case 4:
          if(encoderPos==10)encoderPos=0;
          if(encoderPos==-1)encoderPos=9;
          menu4=encoderPos;
        break;
      }
          // transfer internal memory to the display
      switch(cMenu){
        case 1:
        switch (menu){
          case 0://Match
             aMenu(0);
          break;
          case 1:
            aMenu(10);
          break;
        }
        break;
        case 2:
          switch(menu1){
            case 0:
              aMenu1(10);
            break;
            case 1:
              aMenu1(20);
            break;
            case 2:
              aMenu1(30);
            break;
            case 3:
              aMenu1(40);
            break;
          }
        break;
        case 3:
        switch(menu3){
          case 0:
          aMenu3(10);
          break;
          case 1:
          aMenu3(20);
          break;
          case 2:
          aMenu3(30);
          break;
          case 3:
          aMenu3(40);
          break;
          case 4:
          aMenu3(50);
          break;
        break;
        }
        break;
        case 4:
          aMenu4(menu4);
        break;
      }
    }
}
  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  if(cote==coteBleu)u8g2.drawStr(0,9,"Bleu");
  else u8g2.drawStr(0,9,"Roude");
  u8g2.drawStr(0,19,"Strategiet");
  u8g2.setCursor(90,19);
  u8g2.print(strategie);
  u8g2.drawStr(0,29,"inite");
  //  u8g2.blink(); //clignoter le msg
  u8g2.sendBuffer();
  Wire.requestFrom(adr_deplacement,1);
  while(a!=0){
    Wire.requestFrom(adr_deplacement,1);
    a=Wire.read();
  }
  deplacment[0][1]=750;
  deplacment[0][2]=300;
  deplacment[0][3]=0;

  if(cote==coteRouge)deplacment[0][2]=3000-deplacment[0][2];

  u[1]=deplacment[0][1];
  u[2]=deplacment[0][2];
  u[3]=deplacment[0][3];
  u[0]=((deplacment[0][3]&=(1<<8))>>1);
  u[0]|=((deplacment[0][1]&=(0x700))>>4);
  u[0]|=((deplacment[0][2]&=(0xF00))>>8);
  Wire.beginTransmission(adr_deplacement);
  Wire.write(u[0]);
  Wire.write(u[1]);
  Wire.write(u[2]);
  Wire.write(u[3]);
  Wire.endTransmission();
  a=1;
  Wire.requestFrom(adr_actionneur,1);
  while(a!=0){
    Serial.println(3);
    Wire.requestFrom(adr_actionneur,1);
    a=Wire.read();
  }
  Wire.beginTransmission(adr_actionneur);
  Wire.write(10);
  Wire.write(33);
  Wire.endTransmission();
  a=1;
  while(a!=0){
    Wire.requestFrom(adr_actionneur,1);
    a=Wire.read();
  }

  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  if(cote==coteBleu)u8g2.drawStr(0,9,"Bleu");
  else u8g2.drawStr(0,9,"Roude");
  u8g2.drawStr(0,19,"Strategiet");
  u8g2.setCursor(90,19);
  u8g2.print(strategie);
  u8g2.drawStr(0,29,"pret");
  //  u8g2.blink(); //clignoter le msg
  u8g2.sendBuffer();
  do{
    Serial.println(4);
    depar=digitalRead(22);
    delay(10);
    //Serial.println(depar);
  }while(depar==1);
  etat=1;
  Time2=0;
}

void loop() {
  byte t[4];
  int e;
  if(Time2==100)etat=4;
  //Serial.println(pase);
  switch (etat){
    case 1:
      Wire.requestFrom(adr_deplacement,1);
      a=Wire.read();
      Wire.requestFrom(adr_actionneur,1);
      b=Wire.read();
    //  Serial.println(a);
    //  Serial.println(b);
      if (a==0&&b==0){
        etat=deplacment[m][0];
      }
    break;
    case 2:
      if(cote==coteRouge){
        deplacment[m][2]=3000-deplacment[m][2];
        deplacment[m][3]=360-deplacment[m][3];
    /*    if(m>=12&&m<=22){
          if(cote==coteRouge){

          }
          else{

          }
        }*/
        if(deplacment[m][4]>=20){
          deplacment[m][4]+=2;
        }
      }
      e=deplacment[m][2];
      t[1]=deplacment[m][1];
      t[2]=deplacment[m][2];
      t[3]=deplacment[m][3];
      t[0]=((deplacment[m][3]&=(1<<8))>>1);
      t[0]|=((deplacment[m][1]&=(0x700))>>4);
      t[0]|=((deplacment[m][2]&=(0xF00))>>8);
      t[4]=deplacment[m][4];
      Wire.beginTransmission(adr_deplacement);
      Wire.write(t[0]);
      Wire.write(t[1]);
      Wire.write(t[2]);
      Wire.write(t[3]);
      Wire.write(t[4]);
      Wire.endTransmission();
      m++;
      etat=1;

    break;
    case 3://prévision pour la carte adr_actionneur

      t[0]=deplacment[m][1];
      t[1]=deplacment[m][2];
      Wire.beginTransmission(adr_actionneur);
      Wire.write(t[0]);
      Wire.write(t[1]);
      Wire.endTransmission();
      etat=1;
      m++;
      etat=1;
    break;
    case 4:
      Wire.beginTransmission(adr_actionneur);
      Wire.write(0);
      Wire.write(0);
      Wire.write(0);
      Wire.endTransmission();
    break;

  }
  if(pase==true){
    Serial.println("reusie");
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    if(cote==coteBleu)u8g2.drawStr(0,9,"Bleu");
    else u8g2.drawStr(0,9,"Roude");
    u8g2.drawStr(0,19,"Strategiet");
    u8g2.setCursor(90,19);
    u8g2.print(strategie);
    u8g2.drawStr(0,29,"point");
    u8g2.drawStr(0,39,"Temps");
    u8g2.setCursor(90,39);
    u8g2.print(Time2);
    //  u8g2.blink(); //clignoter le msg
    u8g2.sendBuffer();
    pase=false;
  }
//Serial.println("la");
//  while(Wire.available()){//reception dune trame du mettre
//    Serial.println(Wire.read());
//  }
//  Serial.println(Wire.requestFrom(adr_deplacement,1));//recepetion dune trame

}
void aMenu(int blanc){
  u8g2.clearBuffer();         // clear the internal memory
//  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setCursor(118,64);
  u8g2.print(encoderPos);
  u8g2.setFontMode(1);  /* activate transparent font mode */
  u8g2.setDrawColor(1); /* color 1 for the box */
  u8g2.drawBox(0, blanc, 128, 10);
  u8g2.setDrawColor(2);
  u8g2.drawStr(0,9, "Match");
  u8g2.drawStr(0,19, "Parametre");
  u8g2.sendBuffer();
}


void aMenu1(int blanc){
  u8g2.clearBuffer();         // clear the internal memory
  //  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setCursor(118,64);
  u8g2.print(encoderPos);
  u8g2.setFontMode(1);  /* activate transparent font mode */
  u8g2.setDrawColor(1); /* color 1 for the box */
  u8g2.drawBox(0, blanc, 128, 10);
  u8g2.setDrawColor(2);
  u8g2.drawStr(0,9, "               Match");
  u8g2.drawStr(0,19, "Choie cotée");
  if(cote==coteBleu)u8g2.drawStr(90,19,"Bleu");
  else u8g2.drawStr(100,19,"Roude");
  u8g2.drawStr(0,29,"Choie de strategie");
  u8g2.setCursor(116,29);
  u8g2.print(strategie);
  u8g2.drawStr(0,39,"verification -> match");
  u8g2.drawStr(0,49,"Retoure");
  u8g2.sendBuffer();
}


void aMenu3(int blanc){
  u8g2.clearBuffer();         // clear the internal memory
  //  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setCursor(118,64);
  u8g2.print(encoderPos);
  u8g2.setFontMode(1);  /* activate transparent font mode */
  u8g2.setDrawColor(1); /* color 1 for the box */
  u8g2.drawBox(0, blanc, 128, 10);
  u8g2.setDrawColor(2);
  u8g2.drawStr(0,9, "             Parametre");
  u8g2.drawStr(0,19, "Base roulante");
  u8g2.drawStr(0,29,"Actioneur");
  u8g2.drawStr(0,39,"Teste actioneur");
  u8g2.drawStr(0,49,"Teste base roulante");
  u8g2.drawStr(0,59,"Retoure");
  u8g2.sendBuffer();
}


void aMenu4(int blanc){
  u8g2.clearBuffer();         // clear the internal memory
  //  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.setCursor(98,64);
  u8g2.print(encoderPos);
  u8g2.setFontMode(1);  /* activate transparent font mode */
  u8g2.setDrawColor(1); /* color 1 for the box */
  u8g2.drawStr(0,9,"     verification");
  if(blanc>1 && blanc<8){
    u8g2.drawBox(0, 30, 128, 10);
    u8g2.setDrawColor(2);
    for (int i=(blanc-2); i <(blanc+3); i++) {
      switch (i) {
        case 0:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Eguille");
          if(vEguille)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 1:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Tirete de demarage");
          if(vTierete)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 2:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Moteur de droite");
          if(vMoteurDroit)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 3:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Moteur de gauche");
          if(vMoteurGauche)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 4:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Carte allmer");
          if(vCarte)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 5:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Actionneur");
          if(vActionneur)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 6:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Experience");
          if(vExperience)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 7:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Robot placer");
          if(vRoboPlacer)u8g2.drawStr(118,(3-blanc+i)*10+9,"v");
          else u8g2.drawStr(118,(3-blanc+i)*10+9,"x");
        break;
        case 8:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Retoure");
        break;
        case 9:
          u8g2.drawStr(0,(3-blanc+i)*10+9,"Valider fin -> Mathce");
        break;
      }
    }
  }else{
    switch (blanc) {
      case 0:
        u8g2.drawBox(0, 10, 128, 10);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0,19,"Eguille");
        if(vEguille)u8g2.drawStr(118,19,"v");
        else u8g2.drawStr(118,19,"x");
        u8g2.drawStr(0,29,"Tirete de demarage");
        if(vTierete)u8g2.drawStr(118,29,"v");
        else u8g2.drawStr(118,29,"x");
        u8g2.drawStr(0,39,"Moteur de gauche");
        if(vMoteurDroit)u8g2.drawStr(118,39,"v");
        else u8g2.drawStr(118,39,"x");
        u8g2.drawStr(0,49,"Carte allmer");
        if(vMoteurGauche)u8g2.drawStr(118,49,"v");
        else u8g2.drawStr(118,49,"x");
        u8g2.drawStr(0,59,"Actionneur");
        if(vActionneur)u8g2.drawStr(118,59,"v");
        else u8g2.drawStr(118,59,"x");
      break;
      case 1:
        u8g2.drawBox(0, 20, 128, 10);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0,19,"Eguille");
        if(vEguille)u8g2.drawStr(118,19,"v");
        else u8g2.drawStr(118,19,"x");
        u8g2.drawStr(0,29,"Tirete de demarage");
        if(vTierete)u8g2.drawStr(118,29,"v");
        else u8g2.drawStr(118,29,"x");
        u8g2.drawStr(0,39,"Moteur de gauche");
        if(vMoteurDroit)u8g2.drawStr(118,39,"v");
        else u8g2.drawStr(118,39,"x");
        u8g2.drawStr(0,49,"Carte allmer");
        if(vMoteurGauche)u8g2.drawStr(118,49,"v");
        else u8g2.drawStr(118,49,"x");
        u8g2.drawStr(0,59,"Actionneur");
        if(vActionneur)u8g2.drawStr(118,59,"v");
        else u8g2.drawStr(118,59,"x");
      break;
      case 8:
        u8g2.drawBox(0, 40, 128, 10);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0,19,"Actionneur");
        if(vActionneur)u8g2.drawStr(118,19,"v");
        else u8g2.drawStr(118,19,"x");
        u8g2.drawStr(0,29,"Experience");
        if(vExperience)u8g2.drawStr(118,29,"v");
        else u8g2.drawStr(118,29,"x");
        u8g2.drawStr(0,39,"Robot placer");
        if(vRoboPlacer)u8g2.drawStr(118,39,"v");
        else u8g2.drawStr(118,39,"x");
        u8g2.drawStr(0,49,"Retoure");
        u8g2.drawStr(0,59,"Valider fin -> Mathce");
      break;
      case 9:
        u8g2.drawBox(0,50, 128, 10);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0,19,"Actionneur");
        if(vActionneur)u8g2.drawStr(118,19,"v");
        else u8g2.drawStr(118,19,"x");
        u8g2.drawStr(0,29,"Experience");
        if(vExperience)u8g2.drawStr(118,29,"v");
        else u8g2.drawStr(118,29,"x");
        u8g2.drawStr(0,39,"Robot placer");
        if(vRoboPlacer)u8g2.drawStr(118,39,"v");
        else u8g2.drawStr(118,39,"x");
        u8g2.drawStr(0,49,"Retoure");
        u8g2.drawStr(0,59,"Valider fin -> Mathce");
      break;
    }
  }
  u8g2.sendBuffer();
}


void IntrerrupTimer(){
  Time2++;
  pase=true;
}
