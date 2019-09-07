#include <Servo.h>  
/* Einbindung der Servo-Bibliothek, damit das Programmieren der Servos leichter wird */

// Pinfestlegung der Sensoren, acc ist die Abkürzung für den Neigungssensor
int accZPin=0;      //Z-Achse
int accYPin=1;      //Y-Achse
int accXPin=2;      //X-Achse
int onePot=3;       //Greifer-Potentiometer
int twoPot=4;       //Neigungs-Potentiometer

/* Variablenerstellung für die unterschiedlichen Gelenke des Roboters – Namen nach Gelenk */
int greifer;
int greifer_alt = 0;    // was […]_alt bedeutet wird unten beschrieben
int dreher;
int dreher_alt = 0;
int neigung;
int neigung_alt = 0;

//Variablenfestlegung für die benötigte Pause einer Servobewegung
int pause_greifer;
int pause_dreher;
int pause_neigung;

//Namensfestlegung für die verschiedenen Servos
Servo first;     //Greifer
Servo second;    //Dreh
Servo third;     //Neigung

//Code, der einmal ausgeführt wird:
void setup() {
/* Baudrate einstellen – die Geschwindigkeit, womit der Arduino mit einem PC redet */
    Serial.begin(9600); 
//Den Servos jeweils ihren Pin zuweisen
  first.attach(10);
  second.attach(11);
  third.attach(9);
  }


//Code, der ständig wiederholt wird:
void loop() {
  /* zuerst wird zum leichteren Kalibrieren (einstellen) des Neigungssensor ihre Werte ausgelesen und an den PC geschickt */
  Serial.print(" X=");
  Serial.print(analogRead(accXPin));
  Serial.print(" Y=");
  Serial.print(analogRead(accYPin));
  Serial.print(" Z=");
  Serial.println(analogRead(accZPin));

//Hier wird jetzt in diesem Block der Greifer-Servo gesteuert.
  greifer = map(analogRead(onePot), 215, 300, 30, 190); /* Hier wird der Greifer-Potentiometer ausgelesen und in die Werte für den Servo umgerechnet – die Variable „Greifer“ nimmt diesen Wert an. In der Klammer werden zuerst die Werte vom Sensor von 215 – 300 in den Winkel für den Servo von 30°-190° umgerechnet. (Arduino, V.1.8.9)*/
  Serial.print(" Servo Greifer: "); //Winkel des Servos an den Computer senden
  Serial.print(greifer);            /* Immer zuerst was angezeigt wird (voriger Befehl), danach die Variabel */
  pause_greifer = abs(greifer - greifer_alt) * 3;   /* Die Verzögerung für die Drehung wird ständig neu angepasst, je nachdem, wie groß die Winkeldifferenz ist. Dafür wird die differenz der alten Winkeldifferenz und der neuen genommen und mit drei multipliziert. Die neue Variable für diesen Vorgang hat immer die Vorsilbe „pause“. */
  if (pause_greifer <= 600 && greifer > 0){  /* Wenn der Winkelunterschied kleiner als 200° ist (da vorher mit drei Multipliziert wurden ist, muss man jetzt durch drei teilen, um auf diese Zahl zu kommen) und der Servowinkel nicht negativ ist, soll der Servo bewegt werden – das mache ich, damit Fehlmessungen oder falsche Werte weniger im Betrieb auffallen – eine Sicherheitsabfrage. */
  first.write(greifer); //Greifer-Servo bewegt sich zu dem vorgegebenen Winkel
  delay(pause_dreher);  //Pause für die Bewegung 
  }
  greifer_alt = greifer;    /* den aktuellen Winkel als alten Winkel nehmen, damit in der nächsten Ausführung des Codes der Wert wieder neu berechnet werden kann. */

//Hier wird jetzt in diesem Block der Dreher-Servo gesteuert, funktioniert im Grunde so wie der Obige, Variablen und Zahlen wurden aktualisiert 
  dreher = map(analogRead(accZPin), 250, 450, 30, 330);// Umrechnung der Werte
  Serial.print(" Servo Dreher: ");      //Ausgabe des Servo-Winkels an den PC
  Serial.print(dreher);             
  pause_dreher = abs(dreher - dreher_alt) * 3;  //Pause berechnen
  if (pause_dreher <= 80 && dreher > 0){    //Sicherheitsabfrage 
  second.write(dreher);				//Dreh-Servo bewegen
  delay(pause_dreher);				//Dynamische Pause
  }
  dreher_alt = dreher;				//Werte aktualisieren

/* Dieser Block funktioniert genauso wie die beiden darüber – die Variablen und Zahlen sind nur für den Neigungssensor angepasst wurden */
  neigung = map(analogRead(accYPin), 270, 410, 30, 330);
  Serial.print(" Servo Neigung: ");
  Serial.print(neigung);
  pause_neigung = abs(neigung - neigung_alt) * 5;
  if (pause_neigung <= 80 && neigung > 0){
  third.write(neigung);
  delay(pause_neigung);
  }
  neigung_alt = neigung;
}
 
