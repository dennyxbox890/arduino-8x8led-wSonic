#include <Servo.h>
Servo servo;
const int trig=10;
const int echo=11;
int motor_dtime=1;
long duration;
int distance;
int supersonic_func1();
void setup() {
	Serial.begin(9600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    servo.attach(9);
}

void loop() {
	for(int i=0;i<360;i++){
        servo.write(i);
        delay(motor_dtime);
    }
    for(int i=360;i>=0;i--){
        servo.write(i);
        delay(motor_dtime);
    }

}
//https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
int supersonic_func1(){
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    /*
    v=340 m/s
    t=s/v
    s=t*0.034/2
    */
    duration=pulseIn(echo,HIGH);
    distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}