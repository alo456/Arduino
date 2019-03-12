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

 int idx =0,espera=0;
void setup() {
  for(int i=0;i<4;i++) pinMode(numBin[i],OUTPUT);
  pinMode(dispSel[0],OUTPUT);
  pinMode(dispSel[1],OUTPUT);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],LOW);
}

void loop() {
  int d1 = idx/10;
  int d2 = idx%10;
  updateDisplay(d1,d2);
  if(espera++ > 50) {
    idx++;
    espera =0;
  }

  if(idx ==100) idx =0;
  
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
