// On définit l'angle 0 à droite

#include "Servo.h"

#define Broche_Echo_right 12 // Broche Echo du HC-SR04 sur D7 //
#define Broche_Trigger_right 13
#define Broche_Echo_left 7 // Broche Echo du HC-SR04 sur D7 //
#define Broche_Trigger_left 6

#define LASER 8 // Broche Trigger du HC-SR04 sur D8 //

// Definition des variables
Servo servo;

// Variable pour l'étalonnage
int T = 10 ;
int tau = 2 ;
int max_gap = 15;
int step = 5;

int gap;
int Distance_right;
int Distance_left;
int angle; 

//
int move_right(int ang){
  ang = ang + step;
  servo.write(ang);
  return ang;
}

int move_left(int ang){
  ang = ang - step;
  servo.write(ang);
  return ang;
}

int get_distance_right(int T, int tau){
  // Debut de la mesure avec un signal de 10 μS applique sur TRIG //
  digitalWrite(Broche_Trigger_right, LOW); // On efface l'etat logique de TRIG //
  delayMicroseconds(tau);
  digitalWrite(Broche_Trigger_right, HIGH); // On met la broche TRIG a "1" pendant 10μS //
  delayMicroseconds(T);
  digitalWrite(Broche_Trigger_right, LOW); // On remet la broche TRIG a "0" //
  // On mesure combien de temps le niveau logique haut est actif sur ECHO //
  int Duree = pulseIn(Broche_Echo_right, HIGH);
  // Calcul de la distance grace au temps mesure //
  return (Duree*0.034/2); // *** voir explications apres l'exemple de code *** //
}

int get_distance_left(int T, int tau){
    // Debut de la mesure avec un signal de 10 μS applique sur TRIG //
  digitalWrite(Broche_Trigger_left, LOW); // On efface l'etat logique de TRIG //
  delayMicroseconds(tau);
  digitalWrite(Broche_Trigger_left, HIGH); // On met la broche TRIG a "1" pendant 10μS //
  delayMicroseconds(T);
  digitalWrite(Broche_Trigger_left, LOW); // On remet la broche TRIG a "0" //
  // On mesure combien de temps le niveau logique haut est actif sur ECHO //
  int Duree = pulseIn(Broche_Echo_left, HIGH);
  // Calcul de la distance grace au temps mesure //
  return (Duree*0.034/2) ; // *** voir explications apres l'exemple de code *** //
}


void setup()
{
  servo.attach(10);
  pinMode(Broche_Trigger_right, OUTPUT); // Broche Trigger en sortie //
  pinMode(Broche_Echo_right, INPUT);
  pinMode(Broche_Trigger_left, OUTPUT); // Broche Trigger en sortie //
  pinMode(Broche_Echo_left, INPUT);
  // Broche Echo en entree //
  Serial.begin (9600);

  servo.write(0);
  angle = 0;

  pinMode(LASER, OUTPUT);
  digitalWrite(LASER, HIGH);
  delay(1000);
}


void loop() {

  Distance_right = get_distance_right(T,tau); 
  delay(100);
  Distance_left = get_distance_left(T,tau);
  gap = abs(Distance_left - Distance_right);

  if (gap >max_gap){
    if( (Distance_right > Distance_left) && angle <180){
      angle = move_right(angle);
    }
    if( (Distance_left > Distance_right) && angle >0){
      angle = move_left(angle);
    }
  }

  // Affichage dans le moniteur serie de la distance mesuree //
  Serial.print("Distance gauche :"+String(Distance_left));
  Serial.print("\tDistance droite :"+ String(Distance_right));
  Serial.print("\tGap :"+ String(gap));

  Serial.println("\n\n");
}