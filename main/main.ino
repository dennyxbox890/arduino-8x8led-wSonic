//#include <Servo.h>
//Servo servo;
const int trig=10;
const int echo=11;
//const int serv=9;
//int motor_dtime=1;
long duration;
long distance;
int supersonic_func1();
void setup() {
	Serial.begin(9600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    //servo.attach(serv);
}

void loop() {
  
  
  
  
	/*for(int i=0;i<120;i++){
        servo.write(i);
        supersonic_func1();
        delay(motor_dtime);
    }
    for(int i=120;i>=0;i--){
        servo.write(i);
        supersonic_func1();
        delay(motor_dtime);
    }*/

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
    Serial.println(distance);
}