#include <Arduino.h>
#include <Wire.h>     //liaison I2C pour les cartes
#include <SPI.h>      //liaison SPI pour ecran
#include <U8g2lib.h>  //gestion de l'ecran lcd grafique
#include <FastCRC.h>  //gestion d'erreur sur bus I2C


#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define adr_deplacement 10 //adr adresse
#define adr_actionneur  20

#define coteRouge 1
#define coteBleu  0

void aMenu(int blanc);
void aMenu1(int blanc);
void aMenu4(int blanc);
void aMenu3(int blanc);
void IntrerrupTimer()
