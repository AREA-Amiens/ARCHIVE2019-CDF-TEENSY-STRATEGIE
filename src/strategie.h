#include <Arduino.h>
#include <Wire.h>     //liaison I2C pour les cartes
#include <SPI.h>      //liaison SPI pour ecran
#include <U8g2lib.h>  //gestion de l'ecran lcd grafique
#include <FastCRC.h>  //gestion d'erreur sur bus I2C

#define adr_deplacement 10 //adr adresse
#define adr_actionneur  20

#define coteRouge 1
#define coteBleu  0
