#include <Wire.h>    //Library for SPI communication
#include <DS3231.h>   //Library for RTC module 

#define DS3231_ADDRESS 0x68
DS3231 Clock;

#define BUT1 A1    // - switch
#define BUT2 A2    // + switch
#define BUT3 A3    // MENU switch

bool h12;
bool PM;
bool Century = false;
byte digit1 = 10;
byte digit2 = 11;
byte digit3 = 12;
byte digit4 = 9;
byte segA = 2; //Display pin 11
byte segB = 3; //Display pin 7
byte segC = 4; //Display pin 4
byte segD = 5; //Display pin 2
byte segE = 6; //Display pin 1
byte segF = 7; //Display pin 10
byte segG = 8; //Display pin 5
byte dp = A0;
int menu = 0;
int reglage_heure;
int reglage_minute;
long temps;
boolean etat_led;

void setup() {
  Wire.begin();
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);
  pinMode(dp, OUTPUT);
  etat_led = 0;
  digitalWrite(dp, etat_led);
  temps = millis();
}
void loop() {
  int h = Clock.getHour(h12, PM); //To get the Hour
  int m = Clock.getMinute();//TO get the
  int number = h * 100 + m;
  //for (int i = 0; i < 4000; i++) {
  //}
  if ((millis() - temps) > 1000)
  {
    etat_led = !etat_led; // on inverse l'état de la LED
    digitalWrite(dp, etat_led); // on allume ou éteint
    temps = millis(); // on stocke la nouvelle heure
  }
  if (menu == 0) {
    afficher(number);
  }
  if (digitalRead(BUT3) == 1)
  {
    menu = menu + 1;
    delay(250);
  }
  if (menu == 1) {
    int h = Clock.getHour(h12, PM); //To get the Hour
    reglageheure(h);
    if (digitalRead(BUT2) == 1)
    {
      reglage_heure++;
      if (reglage_heure > 23) reglage_heure = 0;
      reglage_heure = reglage_heure;
      Clock.setHour(reglage_heure);
      delay(250);
    }
    if (digitalRead(BUT1) == 1)
    {
      reglage_heure--;
      if (reglage_heure < 0 ) reglage_heure = 23;
      reglage_heure = reglage_heure;
      Clock.setHour(reglage_heure);
      delay(250);
    }
    Clock.setHour(reglage_heure);
    // delay(250);
    if (digitalRead(BUT3) == 1)
    { menu = 2;
      delay(250);
    }
  }
  if (menu == 2) {
    int m = Clock.getMinute(); //To get the Hour
    reglageminute(m);
    if (digitalRead(BUT2) == 1)
    {
      reglage_minute++;
      if (reglage_minute > 60) reglage_minute = 0;
      reglage_minute = reglage_minute;
      Clock.setMinute(reglage_minute);
      delay(250);
    }
    if (digitalRead(BUT1) == 1)
    {
      reglage_minute--;
      if (reglage_minute < 0 ) reglage_minute = 60;
      reglage_minute = reglage_minute;
      delay(250);
      Clock.setMinute(reglage_minute);
    }
    Clock.setMinute(reglage_minute);
    // delay(250);
    if (digitalRead(BUT3) == 1)
    { menu = 0;
      delay(250);
    }
  }
}
void reglageheure(int toDisplay) {
#define DISPLAY_BRIGHTNESS  750

#define DIGIT_ON  0
#define DIGIT_OFF 1
  for (int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch (digit) {
      case 1:
        digitalWrite(digit1, DIGIT_ON);
        lightNumber(11); // display degree symbol % 10
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 2:
        digitalWrite(digit2, DIGIT_ON);
        lightNumber(12); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
    }
    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);

  }
}

void reglageminute(int toDisplay) {
#define DISPLAY_BRIGHTNESS  750

#define DIGIT_ON  0
#define DIGIT_OFF 1
  for (int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch (digit) {
      case 1:
        digitalWrite(digit1, DIGIT_ON);
        lightNumber(13); // display degree symbol % 10
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 2:
        digitalWrite(digit2, DIGIT_ON);
        lightNumber(14); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
    }
    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);

  }
}

void afficher(int toDisplay) {
#define DISPLAY_BRIGHTNESS  250

#define DIGIT_ON  0
#define DIGIT_OFF 1
  for (int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch (digit) {
      case 1:
        digitalWrite(digit1, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol % 10
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 2:
        digitalWrite(digit2, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        lightNumber(toDisplay % 10); // display degree symbol
        toDisplay /= 10;
        delayMicroseconds(DISPLAY_BRIGHTNESS);
        break;
    }
    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);

  }
}

//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  1
#define SEGMENT_OFF 0

  switch (numberToDisplay) {

    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    // all segment are ON
    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      digitalWrite(13, SEGMENT_OFF);
      break;

    // degree symbol made by niq_ro

    case 11:                //H
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 12:                //R
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 13:                //M
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      digitalWrite(13, SEGMENT_OFF);
      break;

    case 14:                //N
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      digitalWrite(13, SEGMENT_OFF);
      break;
  }
}
