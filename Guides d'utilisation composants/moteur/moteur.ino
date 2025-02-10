#include "Servo.h"

Servo servo; // création de l'objet "servo"

void setup() {
   servo.attach(10); // attache le servo au pin spécifié
   Serial.begin(9600);
   servo.write(0);
   delay(1000); // ouvre le port série
}

int ang = 0;

void loop() {
  /*servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
  */
  servo.write(ang);
  delay(200);
  if (ang < 180){
    ang = ang+2;
  }
  else{ang = 0;}


  
}