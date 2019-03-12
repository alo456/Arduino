int numBin[]={2,3,4,5};
int dispSel[]={6,7};
int boton = 8;

byte digitos[7][4] ={
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0}
};
void setup() {
  for(int i=0;i<4;i++) pinMode(numBin[i],OUTPUT);
  pinMode(dispSel[0],OUTPUT);
  pinMode(dispSel[1],OUTPUT);
  pinMode(boton,INPUT);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],LOW);
}

void loop() {
  static  int dice1;
  static int dice2;
 // if(digitalRead(boton)){
    dice1 = random(1,7);
    dice2 = random(1,7);
 // }

  delay(1000);
  
  updateDisplay(dice1,dice2);
}

void updateDisplay(int d1, int d2){
  digitalWrite(dispSel[0],HIGH);
  digitalWrite(dispSel[1],LOW);
  setSegments(d1);
  delay(500);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],HIGH);
  setSegments(d2);
  delay(500);
}

void setSegments (int n){
  for(int i=0;i<4;i++){
    digitalWrite(numBin[i], digitos[n][i]);
  }
}


