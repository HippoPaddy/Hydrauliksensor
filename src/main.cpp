#include <Arduino.h>

//    Formel;
//    Füllstand [%]    = -1.887*distance+113.208


int hydsensemmit = 6;
int hydsensekko = 7;

int ledpinlow = 2;
int ledpingood = 3;
int ledpinover = 4;
float timing;
float distance;



void setup() {
// Alle nötigen Pinmodes
    // mit Hilfe von Isabel und https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf

    pinMode(ledpingood, OUTPUT);
    pinMode(ledpinlow, OUTPUT);
    pinMode(ledpinover, INPUT);
    pinMode(hydsensemmit, OUTPUT);
    pinMode(hydsensekko, INPUT);

    Serial.begin(9600);

}

void loop() {
// Dieser Teil ist das Programm für den Sensor. Mit der Berechnung für die Distanzmessung
    //https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf


    Serial.print ("digitalread ");

    Serial.println(digitalRead(hydsensekko));

    digitalWrite(hydsensemmit, LOW);
    delay(2);

    digitalWrite(hydsensemmit, HIGH);
    delay(10);
    digitalWrite(hydsensemmit, LOW);

    timing = pulseIn(hydsensekko, HIGH);
    distance = (timing * 0.034) / 2;


// Das Programm gibt die Distanz in cm aus
    Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print("cm | ");

// Bis hier vom Link

    // Die Verzeigung wie Arduino vorgehen soll bei der gemessenen Distanz

float statehydsens = -1.887*distance+113.208 ; // Formel für den Füllstand in Abhängigkeit der Distanz
    //    Ist der Füllstand zwischen 20% und 100% leuchtet die grüne Lampe
    if (statehydsens <= 100 && statehydsens >= 20) {
        digitalWrite(ledpingood, HIGH);// Setzt den Digitalpin 2 auf HIGH = "Ein"
        digitalWrite(ledpinlow, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
        digitalWrite(ledpinover, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
    }
    //    Ist der Füllstand > 100% leuchtet die blaue Lampe
    else if (statehydsens > 100 ) {
        digitalWrite(ledpingood, LOW);// Setzt den Digitalpin 2 auf LOW = "AUS"
        digitalWrite(ledpinlow, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
        digitalWrite(ledpinover, HIGH);// Setzt den Digitalpin 3 auf HIGH = "EIN"
    }
    //    Ist der Füllstand unter 20% leuchtet die rote Lampe
else {
    digitalWrite(ledpingood, LOW);// Setzt den Digitalpin 2 auf LOW = "AUS"
    digitalWrite(ledpinlow, HIGH);// Setzt den Digitalpin 3 auf HIGH = "EIN"
    digitalWrite(ledpinover, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
}

    // Was das Programm ausgeben soll
    // auch mit hilfe des Programms im Link

Serial.print("Der Oelstand betraegt: "); // Anzeige vom errechneten Füllstand
Serial.println(statehydsens);
delay(3000); // Messinterval





}