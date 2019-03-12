#include <Servo.h>
Servo servoH;
int s0 = 0, s1 = 1, s2 = 2, s3 = 3, s4 = 4, s5 =5;
int numBin[]={0,1,2,3};
int dispSel[]={4,5};
int echo = 6, trig = 7;
int laserPin = 8;
int pinaltavoz = 10;
int boton = 11;

byte digitos[10][4] ={
  {0,0,0,0},
  {1,0,0,0},
  {0,1,0,0},
  {1,1,0,0},
  {0,0,1,0},
  {1,0,1,0},
  {0,1,1,0},
  {1,1,1,0},
  {0,0,0,1},
  {1,0,0,1}
  };
int dg1=0,dg2=0,total,idx =0;
long duracion, distancia,lastDist;
int period = 500;
int lim = 120,contador =0;
int x = 86;
int minX = 10;
int maxX = 170;
int frecuencia=700;   
bool breach = false;

void setup() {
  //Serial.begin(9600);
  servoH.attach(9);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(boton,INPUT);
  for(int i=0;i<4;i++) pinMode(numBin[i],OUTPUT);
  pinMode(dispSel[0],OUTPUT);
  pinMode(dispSel[1],OUTPUT);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],LOW);
  digitalWrite(laserPin,HIGH);
  sensorProx();
}

void loop() {
  if(contador++>30){
    sensorProx();
    total = (int) distancia;
    contador = 0;
  }
  
  detectaMovimiento();
  if(total >= 17 || total <=0){
    //dg1 = dg2 =0;   
  }
  else {
    dg1 = total/10;
    dg2 = total %10;
  }
   if(total<=9 && total>=5){ 
          breach = true;
          tone(pinaltavoz,frecuencia);
     }  
    if(breach){
      if(digitalRead(boton)==HIGH){
        dg1 = dg2 =0;
        breach = false;
        noTone(pinaltavoz);  
      }
    }
  updateDisplay(dg1,dg2);
}

void updateDisplay(int d1, int d2){
  digitalWrite(dispSel[0],HIGH);
  digitalWrite(dispSel[1],LOW);
  setSegments(d1);
  delay(5);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],HIGH);
  setSegments(d2);
  delay(5);
}


void setSegments (int n){
  for(int i=0;i<4;i++){
    digitalWrite(numBin[i], digitos[n][i]);
  }
}

void sensorProx(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  duracion = pulseIn(echo,HIGH);
  distancia = (duracion/2)/29;
}

void detectaMovimiento(){

  int r0 = analogRead(s0);
  int r1 = analogRead(s1);
  int r2 = analogRead(s2);
  int r3 = analogRead(s3);
  int r4 = analogRead(s4);
  int r5 = analogRead(s5);

  if(r0< lim){
    moveLaser(0);
    /*Serial.println(r0);
    Serial.print("valor 0\n");*/
  }
  if(r1<lim){
    moveLaser(1);
    /*Serial.println(r1);
    Serial.print("Valor de r1\n");*/
  }
  if(r2<lim){
    moveLaser(2);
    /*Serial.println(r2);
    Serial.print("Valor de r2\n");*/
  }
  if(r3<lim){
    moveLaser(3);
    //Serial.println(r3);
    //Serial.print("Valor de r3\n");
  }
  if(r4<lim){
    moveLaser(4);
    //Serial.println(r4);
    //Serial.print("Valor de r4\n");
  }
  if(r5<lim){
    moveLaser(5);
    //Serial.println(r5);
    //Serial.print("Valor de r5\n");
  }
  //delay(period);
}

void moveLaser(int linea){
  x = 86+(linea*4);
  if(total>=14) x+=11-linea;
  else if(total >= 9) x+=5-linea;
 
  servoH.write(x);
}

