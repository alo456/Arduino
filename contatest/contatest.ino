int ledOut[] = {0,1,2,3};
int crecDecSw = 10;
int swStatus;
int holdSw;
int currentCount;
void setup() {
 for(int i=0;i<4;i++){
    pinMode(ledOut[i],OUTPUT);
  }
  pinMode(crecDecSw,INPUT);

}

void loop() {
  switchStatus();
  if(swStatus == LOW) {
    currentCount=1;
    cuentaCreciente();
  }
  else{
    currentCount = 15; 
    cuentaDec();  
  }
  apagaTodo();
 delay(1000); 

}

void cuentaCreciente(){
  for(; currentCount<=15; currentCount++){
        
    for(int j=0;j<4;j++){
      if((currentCount >> j) & 1)
          digitalWrite(ledOut[j],HIGH);
      else 
          digitalWrite(ledOut[j],LOW);
    }
   
    switchStatus();
    if(swStatus == HIGH){
        return ;
      }  
      
    delay(1000);
  }
  return ;
}

void cuentaDec(){
  for(;currentCount>=1 ; currentCount--){
     
      for(int j=0;j<4;j++){
      if((currentCount >> j) & 1)
          digitalWrite(ledOut[j],HIGH);
      else 
          digitalWrite(ledOut[j],LOW);
      }
    switchStatus();
    if(swStatus == LOW){
        return ;
      } 
      
    delay(1000);
  }
  return ;
}

void switchStatus(){
  swStatus = digitalRead(crecDecSw);
}


void apagaTodo(){
 for(int j=0;j<4;j++){
      digitalWrite(ledOut[j],LOW);
    }
}



