const int DigI= 4;
const int AnaI = A0;
const int TRIG = 6;
const int ECHO = 7;
const int ledR = 8;
const int ledY = 10;
const int ledO = 9;
const int ledG = 11;
const int Buzz = 13;
const int relay = 1;
const int stclearance = 10;     //residual water level required for exerting sufficient pressure for the working of solenoid valve.Need to find out using ultrasonic sensor.
const double totalsurface = 56; // total surface area of the container used
const double opensurface = 36;  //suraface of the container exposed to rain

double dynclearance;
double waterlevel = 0;
double dist = 0;
int analog_val;
double residue;
int i = 0;
int m;
int n;
int o; 

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(DigI, INPUT);
  pinMode(AnaI, INPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledO, OUTPUT);
  pinMode(ledR, OUTPUT);
  
  Serial.begin(9600);  

}

void loop() {
   // first check whether it is raining
if(digitalRead(DigI) == LOW) 
  {
    
    Serial.println("It's raining"); 
    delayMicroseconds(10);
    digitalWrite(Buzz,HIGH);
    delay(2000);
    digitalWrite(Buzz,LOW);
    
    residue = waterlevel - (2*i/3600);     //let's assume 2cm height water drain in 1 hr ;1 hr = 3600 s
    if(residue<0){
     residue = 0;
     }
    dynclearance = distfunct();
    Serial.println(dynclearance);
     m = 0;
     n = 0;
     o = 0; 
    alertcheck();
  
 }

 else{
  for(i=0;digitalRead(DigI) == HIGH;i++);
  delay(1000);
  }

 

}
//************************************************************************************
//input values from ultrasonic sensor
  int distfunct(){
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
  
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
  
    long duration= pulseIn(ECHO, HIGH);
    double dist =   duration/2*0.0343;
    //Serial.println(dist);
    return dist;
    }

//********************************************************************************************
   //function to compare sensor values to give alert
   void alertcheck(){
    
    if(5>=distfunct()) {
      Serial.println("Start draining water");
      waterdrain();
      }
    
      waterlevel = distfunct() - dynclearance;
      //waterlevel = residue + (waterlevel*totalsurface/opensurface);// to find actual height from apparent height.
      Serial.println("**");
      Serial.println(waterlevel);
      Serial.println("**");
      
    if(6<waterlevel<8){
      Serial.println("yellow alert");
      Serial.println(waterlevel);
      digitalWrite(ledY,HIGH);
      delay(2000);
      digitalWrite(ledY,LOW);
      
      while(m<3){
      
      digitalWrite(Buzz,HIGH);
      delay(2000);
      digitalWrite(Buzz,LOW);
      m++;}
    }
    if(8<waterlevel<10){
      Serial.println("Orange alert");
      digitalWrite(ledO,HIGH);
      delay(2000);
      digitalWrite(ledO,LOW);
      
      while(n<3){
      digitalWrite(Buzz,HIGH);
      delay(2000);
      digitalWrite(Buzz,LOW);
      n++;}
    }
    if(10<waterlevel){
      Serial.println("red alert");
      digitalWrite(ledR,HIGH);
      delay(2000);
      digitalWrite(ledR,LOW);
      
      while(o<3){
      digitalWrite(Buzz,HIGH);
      delay(2000);
      digitalWrite(Buzz,LOW);
      o++;}
    }
  
    if(digitalRead(DigI) == LOW){
       alertcheck();
    }
    
  }
//******************************************************************************************  
   //function to drain water from the container
      void waterdrain(){
      while(distfunct()<stclearance) { 
      digitalWrite(relay,LOW);
      delayMicroseconds(200);
      digitalWrite(relay,HIGH);
      }
   }
