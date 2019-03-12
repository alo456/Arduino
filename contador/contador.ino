int ledOut[] = {0,1,2,3};
int dipSwitch[] = {4,5,6,7};
int loadFlag = 11;
int crecDecSw = 10;
int holding = 9;
int reset = 8;
int swStatus;
int holdSw;
int loadedValue=-1;

void setup()
{
  //Serial.begin(9600);
  for(int i=0;i<4;i++){
    pinMode(ledOut[i],OUTPUT);
  }
  for(int i=0;i<4;i++){
    pinMode(dipSwitch[i],INPUT);
    //digitalWrite(dipSwitch[i], HIGH);
  }
  pinMode(loadFlag,INPUT);
  pinMode(reset,INPUT);
  pinMode(crecDecSw,INPUT);
  pinMode(holding,INPUT);
}

void loop()
{
  int start = 1,end = 15;
  switchStatus();
  holdStatus();
  if(holdSw == HIGH) stay();
  if(swStatus == LOW) cuentaCreciente(start);
  else cuentaDec(end);  

  apagaTodo();
 delay(1000); 
  
}


void cuentaCreciente(int inicio){
  for(int i=inicio;i<=15;i++){
      if(resetCont()) i = 1;
     setLoadedValue(i);
    i = loadedValue;
    for(int j=0;j<4;j++){
      if((i >> j) & 1)
          digitalWrite(ledOut[j],HIGH);
        else 
          digitalWrite(ledOut[j],LOW);
    }
    holdStatus();
    if(holdSw == HIGH) stay();
      
    switchStatus();
      if(swStatus == HIGH){
        cuentaDec(i);
        return ;
      }  
      
    delay(1000);
  }
  return ;
}

void cuentaDec(int inicio){
  for(int i=inicio;i>=1;i--){
       if(resetCont()) i = 15;
      
  
     setLoadedValue(i);
      i = loadedValue;
      for(int j=0;j<4;j++){
      if((i >> j) & 1)
          digitalWrite(ledOut[j],HIGH);
        else 
          digitalWrite(ledOut[j],LOW);
      }
      
    holdStatus();
      
  if(holdSw == HIGH) stay();
      
    switchStatus();
      if(swStatus == LOW){
        cuentaCreciente(i);
        return ;
      } 
      
    delay(1000);
  }
  return ;
}

void switchStatus(){
  swStatus = digitalRead(crecDecSw);
}

void holdStatus(){
  holdSw = digitalRead(holding);
}

void stay(){
  for(int i = 0; ; i++){
    holdStatus();
    if(holdSw == LOW) break;
  }
  return ;
}

bool resetCont(){
  if(digitalRead(reset) == HIGH){
    apagaTodo();
    return true;
  } 
  else return false;
}

void setLoadedValue(int current){
  loadedValue = current;
  while(digitalRead(loadFlag)==HIGH){
 
  int sum=0;

  if(digitalRead(7) == HIGH) sum +=8;
  if(digitalRead(6) == HIGH) sum +=4;
  if(digitalRead(5) == HIGH) sum +=2;
  if(digitalRead(4) == HIGH) sum +=1;

  for(int j=0;j<4;j++){
       if(digitalRead(dipSwitch[j])==HIGH) digitalWrite(ledOut[j],HIGH);
       else digitalWrite(ledOut[j],LOW);
  }
  loadedValue = sum;
}
  
}
void apagaTodo(){
 for(int j=0;j<4;j++){
      digitalWrite(ledOut[j],LOW);
    }
}

