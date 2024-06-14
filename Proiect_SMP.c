#include <Servo.h>
Servo servo_x;
Servo servo_y;
int led = 13;// the pin that the LED is atteched to
int sensor = 2;// the pin that the sensor is atteched to
int state = LOW;// by default, no motion detected
int val = 0;// variable to store the sensor status (value)
int echoPin = 12;
int trigPin = 11;
int motor_DC = 53;//shooting
long duration, cm, in_fata_vechi, in_fata_vechi_nou;
void setup() {
Serial.begin(9600);// initialize serial
pinMode(led, OUTPUT);// initalize LED as an output
pinMode(sensor, INPUT);// initialize sensor as an input
//primul servo
servo_x.attach(7);
servo_x.write(45);
//al doilea servo
servo_y.attach(6);
servo_y.write(90);
//vedere in fata
Serial.println("Am inceput");
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
//Convert the time into a distance
cm = (duration) / 29.1;// Divide by 29.1 or multiply by 0.0343
pinMode(motor_DC, OUTPUT);//shooting
}
void loop(){
val = digitalRead(sensor); // read sensor value
if (val == HIGH) {// check if the sensor is HIGH
digitalWrite(led, HIGH);// turn LED ON
delay(100);// delay 100 milliseconds
if (state == LOW) {
Serial.println("Se misca :()");
state = HIGH;// update variable state to HIGH
}
//Daca simte prezenta unui dusman porneste primul servo
for(int angle_x_axes = 45; angle_x_axes < 90; angle_x_axes++)
{
servo_x.write(angle_x_axes);
delay(15);
Serial.println(angle_x_axes);
//vedere in fata
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
//Read the signal from the sensor a HIGH pulse whose
//duration is the time (in microseconds) from the sending
//of the ping to the reception of its echo off of an object.
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
Serial.println("cm");
//Convert the time into a distance
cm = (duration) / 29.1;// Divide by 29.1 or multiply by 0.0343
// daca simte ca cineva este prezent la mai putin de 50 cm, va trage
if(cm < 50)
{
Serial.println("hat");
//shooting
digitalWrite(motor_DC, HIGH);
//Simtimnd ca este in dreptul unui dusman, servo-ul 2 a inceput
//sa se miste in sus si in jos
for(int angle_y_axes = 45; angle_y_axes < 90; angle_y_axes++)
{
servo_y.write(angle_y_axes);
delay(15);
}
for(int angle_y_axes = 90; angle_y_axes > 45 ; angle_y_axes--)
{
servo_y.write(angle_y_axes);
delay(15);
}
digitalWrite(motor_DC,LOW);
angle_x_axes--;//ca sa nu se miste in lateralcat timp trage
}
delay(15);
}
}
}