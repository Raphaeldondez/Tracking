//https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//https://github.com/TronixLab/DOIT_ESP32_DevKit-v1_30P

// Importation des librairies
#include <ESP32Servo.h>
#include "BluetoothSerial.h"

// Définition des pins
#define Broche_Echo_right 23 // Broche Echo du HC-SR04 sur D7 //
#define Broche_Trigger_right 22
#define Broche_Echo_left 18 // Broche Echo du HC-SR04 sur D7 //
#define Broche_Trigger_left 17
#define PIN_SERVO 21
//#define LASER 8 // Broche Trigger du HC-SR04 sur D8 //


// Definition des variables
Servo servo;
BluetoothSerial bt;

int gap;
int Distance_right=0;
int Distance_left=0;
int angle =0;
int dist = 0; 
String str;

// Variable pour l'étalonnage
int max_dist = 500; // Distance maximale des objets à prendre en compte en cm
int max_gap = 5; // Ecart à partir duquel on considère deux objets différents
int step = 5; // Amplitude des des décalages angulaires
int max_angle_right = 180;
int max_angle_left = 0;


// Définition des fonctions auxilliaires
int move_right(int ang);
int move_left(int ang);
int get_distance_right();
int get_distance_left();
int adjust_pos(int Distance_left, int Distance_right, int angle);
void transmit_data(int dist, int angle);

// Initialisation
void setup()
{
  // Initialisation capteurs ultrasons
  pinMode(Broche_Trigger_right, OUTPUT); // Broche Trigger en sortie //
  pinMode(Broche_Echo_right, INPUT);     // Borche echo en entrée
  pinMode(Broche_Trigger_left, OUTPUT); 
  pinMode(Broche_Echo_left, INPUT);
  
  // Initialisation moteur
  servo.attach(PIN_SERVO);
  servo.write(0);
  

  // Initialisation du laser 
  /*pinMode(LASER, OUTPUT);
  digitalWrite(LASER, HIGH);*/

  // Initialisation des canaux de transmissions
  Serial.begin (115200); 
  bt.begin("Tracker"); //Bluetooth device name
  Serial.println("Start");
  
  delay(3000);
}

//Boucle d'instructions
void loop() {
  Distance_right = get_distance_right(); 
  Distance_left = get_distance_left();
  angle = adjust_pos(Distance_left, Distance_right, angle);
  dist = min(Distance_left, Distance_right);

  //Envoie par bluetooth
  transmit_data(dist, angle);


  Serial.println("\n\n");
}


// Implémentation des fonctions auxilliaires
int move_right(int ang){ // Pivote le système vers la droite et renvoie la variable angle mise à jour
  ang = ang + step;
  servo.write(ang);
  return ang;
}

int move_left(int ang){ // Pivote le système vers la gauche et renvoie la variable angle mise à jour
  ang = ang - step;
  servo.write(ang);
  return ang;
}

//Mesure la distance avec le capteur droit et renvoie -1 si celle-ci est trop grande
int get_distance_right(){   
  // Debut de la mesure avec un signal de 10 μS applique sur TRIG //
  digitalWrite(Broche_Trigger_right, LOW); // On efface l'etat logique de TRIG //
  delayMicroseconds(2);
  digitalWrite(Broche_Trigger_right, HIGH); // On met la broche TRIG a "1" pendant 10μS //
  delayMicroseconds(10);
  digitalWrite(Broche_Trigger_right, LOW); // On remet la broche TRIG a "0" //
  // On mesure combien de temps le niveau logique haut est actif sur ECHO //
  int Duree = pulseIn(Broche_Echo_right, HIGH);
  int dist = Duree*0.034/2;
  Serial.print("Distance droite :"+String(dist));
  if (dist > max_dist){ // On renvoie une erreur si la distance est trop grande 
    return -1;           
  } else { return dist; }; 
}

//Mesure la distance avec le capteur gauche et renvoie -1 si celle-ci est trop grande
int get_distance_left(){
    // Debut de la mesure avec un signal de 10 μS applique sur TRIG //
  digitalWrite(Broche_Trigger_left, LOW); // On efface l'etat logique de TRIG //
  delayMicroseconds(2);
  digitalWrite(Broche_Trigger_left, HIGH); // On met la broche TRIG a "1" pendant 10μS //
  delayMicroseconds(10);
  digitalWrite(Broche_Trigger_left, LOW); // On remet la broche TRIG a "0" //
  // On mesure combien de temps le niveau logique haut est actif sur ECHO //
  int Duree = pulseIn(Broche_Echo_left, HIGH);
  int dist = Duree*0.034/2;
  Serial.print("Distance gauche :"+String(dist));
  if (dist > max_dist){ // On renvoie une erreur si la distance est trop grande 
    return -1;           
  } else { return dist; }; 
}

// Ajuste la position du système en fonction des distance droite et gauche et de l'angle actuel et renvoie la variable angle mise à jour.
// Ne réagit pas si une distance est négative ou si il doit sortir de la plage angulaire autorisée.
int  adjust_pos(int Distance_left, int Distance_right, int angle){
  gap = abs(Distance_left - Distance_right);
  if (Distance_right <0 || Distance_left <0){
    Serial.print("Distance négative");
  }
  else{
    if (gap >max_gap){
      if( (Distance_right > Distance_left) && angle < max_angle_right){
        angle = move_right(angle);
        Serial.println("d");
      }
      if( (Distance_left > Distance_right) && angle >max_angle_left){
        angle = move_left(angle);
        Serial.println("g");
      }
    }
  }
  return angle;
}

// Si un message est reçu en bluetooth, la distance et l'angle sont envoyées en réponse.
void transmit_data(int dist, int angle){
  Serial.println("\nTrying to connect");
  if (bt.available()){
    str = bt.readString();
    if(str!=""){
      Serial.println("Data asked by user");
      //bt.println("Distance: "+String(dist)+"  |  Angle: "+String(angle));
      bt.println(String(dist)+"|"+String(angle));

    }
  }
}


