int echo = 6;
int trig = 7;
long duracion, distancia;

int numBin[]={0,1,2,3};
int dispSel[]={4,5};
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
void setup() {
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(13,OUTPUT);

  for(int i=0;i<4;i++) pinMode(numBin[i],OUTPUT);
  pinMode(dispSel[0],OUTPUT);
  pinMode(dispSel[1],OUTPUT);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],LOW);
  
}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  duracion = pulseIn(echo,HIGH);
  distancia = (duracion/2)/29;
  total = (int) distancia;
  if(distancia >= 25 || distancia <=0){
    Serial.println("----");
    dg1 = dg2 =0;
  }
  
  else{
    dg1 = total/10;
    dg2 = total %10;
    updateDisplay(dg1,dg2);
    int total = (int)distancia;
    Serial.print(total);
    Serial.println("cm");
    digitalWrite(13,0);
  }

  if(distancia <=10 && distancia >=1){
   
    //digitalWrite(13,1);
    Serial.println("Alarma.........!");
  }
  delay(400);
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

  //delay(5);
}


void setSegments (int n){
  for(int i=0;i<4;i++){
    digitalWrite(numBin[i], digitos[n][i]);
  }
}
