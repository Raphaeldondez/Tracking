#define Broche_Echo 12 // Broche Echo du HC-SR04 sur D7 //
#define Broche_Trigger 13

#define LASER 8 // Broche Trigger du HC-SR04 sur D8 //
// Definition des variables
int MesureMaxi = 300; // Distance maxi a mesurer //
int MesureMini = 3; // Distance mini a mesurer //
long Duree;
long Distance;
void setup()
{
pinMode(Broche_Trigger, OUTPUT); // Broche Trigger en sortie //
pinMode(Broche_Echo, INPUT);
 // Broche Echo en entree //
Serial.begin (9600);

pinMode(LASER, OUTPUT);
 digitalWrite(LASER, HIGH);
}
void loop() {
// Debut de la mesure avec un signal de 10 μS applique sur TRIG //
digitalWrite(Broche_Trigger, LOW); // On efface l'etat logique de TRIG //
delayMicroseconds(2);
digitalWrite(Broche_Trigger, HIGH); // On met la broche TRIG a "1" pendant 10μS //
delayMicroseconds(10);
digitalWrite(Broche_Trigger, LOW); // On remet la broche TRIG a "0" //
// On mesure combien de temps le niveau logique haut est actif sur ECHO //
Duree = pulseIn(Broche_Echo, HIGH);
// Calcul de la distance grace au temps mesure //
Distance = Duree*0.034/2; // *** voir explications apres l'exemple de code *** //
// Verification si valeur mesuree dans la plage //
if (Distance >= MesureMaxi || Distance <= MesureMini) {
// Si la distance est hors plage, on affiche un message d'erreur //
Serial.println("Distance de mesure en dehors de la plage (3 cm à 3 m)");
}
else {
// Affichage dans le moniteur serie de la distance mesuree //
Serial.print("Distance mesuree :");
Serial.print(Distance);
Serial.println("cm");
}
delay(1000); // On ajoute 1 seconde de delais entre chaque mesure //
}