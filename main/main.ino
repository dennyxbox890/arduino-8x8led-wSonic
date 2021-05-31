#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include <Wire.h>
const int line[]={2,3,4,5,6,7,8,9};
const int column[]={10,11,12,13,A0,A1,A2,A3};
//frame using flash memory
const bool frame[8][40] PROGMEM={
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}
};
double pos=0.0;
int led_displayID=0;
SoftwareSerial bts(A4,A5);
void def_display();
void bluetooh();
void setup() {
    Serial.begin(9600);
    Serial.println("TEST MESSAGE");
    //HC-05 default speed
    bts.begin(38400);
	for(int i=0;i<8;i++){
        pinMode(line[i],OUTPUT);
        pinMode(column[i],OUTPUT);
        digitalWrite(line[i],LOW);
        digitalWrite(column[i],HIGH);
    }
}
void loop() {
    switch (led_displayID){
        case 0:
            def_display();
            break;
        default:
            break;
    }
    
    
}
void def_display(){
    for(int l=0;l<8;l++){
        for(int c=0;c<8;c++){
            static int frame_buf=pgm_read_byte_near(&frame[c][l+(int)(floor(pos))]);
            if(frame_buf==1){
                digitalWrite(line[l],HIGH);
                digitalWrite(column[c],LOW);
                delay(2);
                digitalWrite(line[l],LOW);
                digitalWrite(column[c],HIGH);
            }else if(frame_buf==0){
                delay(2);
            }
            pos+=0.02;
        }
    }
    if(pos>=39.0){
        pos=0.0;
    }
}
void bluetooth(){

}
/*int supersonic_func1(){
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
    /*duration=pulseIn(echo,HIGH);
    distance= duration*0.034/2;
    Serial.println(distance);
}*/
/*const int frame[8][40]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}*/