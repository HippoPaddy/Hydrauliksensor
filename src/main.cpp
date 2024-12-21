#include <Arduino.h>

//    Formeln;
//    Füllstand [100%] = l*b*(h-7cm)
//    Füllstand [20%]  = (l*b*(h-7cm))/5
//    Füllstand [%]    =


//    Füllstand 100% ist bei hydsenshigh 7cm entfernt
//    Füllstand 20% ist bei hydsenslow

int hydsensemmit = 6;
int hydsensekko = 7;
// int hydsenslow = 5;
int ledpinlow = 2;
int ledpingood = 3;
int ledpinover = 4;
float timing;
float distance;



void setup() {
// write your initialization code here

    pinMode(ledpingood, OUTPUT);
    pinMode(ledpinlow, OUTPUT);
    pinMode(ledpinover, INPUT);
    pinMode(hydsensemmit, OUTPUT);
    pinMode(hydsensekko, INPUT);
    // pinMode(hydsenslow, INPUT);
    Serial.begin(9600);

}

void loop() {
// write your code here
    Serial.print ("digitalread ");

    Serial.println(digitalRead(hydsensekko));

    digitalWrite(hydsensemmit, LOW);
    delay(2);

    digitalWrite(hydsensemmit, HIGH);
    delay(10);
    digitalWrite(hydsensemmit, LOW);

    timing = pulseIn(hydsensekko, HIGH);
    distance = (timing * 0.034) / 2;



    Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print("cm | ");


float statehydsens = -1.887*distance+113.208 ;
    // int hydsenslow = digitalRead(hydsenslow);
    if (statehydsens <= 100 && statehydsens >= 20) {
        digitalWrite(ledpingood, HIGH);// Setzt den Digitalpin 2 auf HIGH = "Ein"
        digitalWrite(ledpinlow, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
        digitalWrite(ledpinover, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
    }
    else if (statehydsens > 100 ) {
        digitalWrite(ledpingood, LOW);// Setzt den Digitalpin 2 auf LOW = "AUS"
        digitalWrite(ledpinlow, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
        digitalWrite(ledpinover, HIGH);// Setzt den Digitalpin 3 auf HIGH = "EIN"
    }
else {
    digitalWrite(ledpingood, LOW);// Setzt den Digitalpin 2 auf LOW = "AUS"
    digitalWrite(ledpinlow, HIGH);// Setzt den Digitalpin 3 auf HIGH = "EIN"
    digitalWrite(ledpinover, LOW);// Setzt den Digitalpin 3 auf LOW = "AUS"
}

Serial.print("Der Oelstand betraegt: ");
Serial.println(statehydsens);
delay(500);





}