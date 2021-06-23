#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <math.h>
const int line[]={2,3,4,5,6,7,8,9};
const int column[]={10,11,12,13,A0,A1,A2,A3};
//using flash memory
const bool frame[8][40] PROGMEM={
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,0,1,0,0,1,1,0,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,0,1,1,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}
};
bool playground[8][8]={
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};
double pos=0.0;
int led_displayID=0;
int trig=A4;
int echo=A5;
void def_display();
//void bluetooth();
void sec_display();
long duration;
int distance;
int supersonic_func1();
void setup() {
    Serial.begin(9600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
	for(int i=0;i<8;i++){
        pinMode(line[i],OUTPUT);
        pinMode(column[i],OUTPUT);
        digitalWrite(line[i],LOW);
        digitalWrite(column[i],HIGH);
    }
    Serial.println("[_INIT_]");
}
void loop() {
    switch (led_displayID){
        case 0:
            def_display();
            break;
        case 1:
            //bluetooth();
            sec_display();
            break;
        default:
            break;
    }
}
void def_display(){
    for(int l=0;l<8;l++){
        for(int c=0;c<8;c++){
            int frame_buf=pgm_read_byte_near(&frame[c][l+(int)(floor(pos))]);
            Serial.print(frame_buf);
            Serial.print(" ");
            if(frame_buf==1){
                digitalWrite(line[l],HIGH);
                digitalWrite(column[c],LOW);
                delay(2);
                digitalWrite(line[l],LOW);
                digitalWrite(column[c],HIGH);
            }else if(frame_buf==0){
                delay(0);
            }
            pos+=0.02;
        }
        Serial.println("");
    }
    Serial.println("--------------------");
    if(pos>=39.0){
        pos=0.0;
        led_displayID=1;
    }
    /*if(bt.available()){
        led_displayID=1;
        Serial.println("[_DISPLAYID=1_]");
        pos=0.0;
    }*/
}
void sec_display(){
    for(int l=0;l<8;l++){
        for(int c=0;c<8;c++){
            int buffer=playground[c][l];
            switch (buffer){
                case 1:
                    digitalWrite(line[l],HIGH);
                    digitalWrite(column[c],LOW);
                    delay(1);
                    digitalWrite(line[l],LOW);
                    digitalWrite(column[c],HIGH);
                    break;
                case 0:
                    delay(1);
                    break;
                default:
                    break;
                }
        }
    }
    int display_bar=supersonic_func1();
    if(display_bar>100){
        display_bar=100;
    }
    display_bar=display_bar/12;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(j<7){
                playground[i][j]=playground[i+1][j];
            }
        }
        if((8-i)<=display_bar){
            playground[7][i]=1;
        }else if((8-i)>display_bar){
            playground[7][i]=0;
        }
    }
}
int supersonic_func1(){
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    /*
    v=340 m/s =0.034 µ/s
    t=s/v
    s=t*0.034/2
    */
    duration=pulseIn(echo,HIGH);
    distance=duration*0.034/2;
    Serial.println(distance);
    return(distance);
}
/*END*/
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
/*void bluetooth(){
    if(bt.available()){
        /*do something*/
    /*    
    }else if(!bt.available()){
        delay(2);
    }
}*/
