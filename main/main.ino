const int line[8]={2,3,4,5,6,7,8,9};
const int column[8]={10,11,12,13,A0,A1,A2,A3};
void setup() {
	for(int i=0;i<8;i++){
        pinMode(line[i],OUTPUT);
        pinMode(column[i],OUTPUT);
        digitalWrite(line[i],LOW);
        digitalWrite(column[i],HIGH);
    }
}

void loop() {
  
}


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