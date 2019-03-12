#include <Keypad.h>
int position = 0;
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows] = {6,7,8,9};
byte colPins[cols] = {10,11,12};
int venti = 13;
const int tempPin = A0;
int temperatura,value;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

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
int limite, digit1,digit2,cont=0,idx=0,dt1,dt2,prov =0;
char key;
bool seteado;
void setup() {
  //Serial.begin(4800);
  for(int i=0;i<4;i++) pinMode(numBin[i],OUTPUT);
  pinMode(dispSel[0],OUTPUT);
  pinMode(dispSel[1],OUTPUT);
  digitalWrite(dispSel[0],LOW);
  digitalWrite(dispSel[1],LOW);
  pinMode(venti,OUTPUT);
  digitalWrite(venti,LOW);
   limite=0;
  digit1=0, digit2=0;
  seteado = false;
  updateTemp();
}
void loop() {

 // updateTemp();
  if(prov++ < 150) 
  updateDisplay(digit1,digit2);
  else{
    updateDisplay(dt1,dt2);
    if(prov>300) prov = 0;
  }
  
  key = keypad.getKey();
  if(key>='0' && key <='9' && !seteado){
    cont++;
    if(cont==1) digit1= key-48;
    else
    if(cont==2) digit2 = key-48;
    else{
      cont =1;
      digit1 = key-48;
    }
  }
  if(key == '#' || seteado){
    idx++;
    seteado = true;
    if(idx ==1) limite = digit1*10 + digit2;
    updateTemp();
    if(temperatura > limite){
      digitalWrite(venti,HIGH);
    } 
    else if(temperatura < limite - 2) digitalWrite(venti,LOW);
  }
  if(key == '*'){
    updateTemp();
    digitalWrite(venti,LOW);
    seteado = false;
    idx =0;
    digit1 = digit2 = 0;
    limite = prov = 0;
  }
  
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

void updateTemp(){
  value = analogRead(tempPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10; 
  temperatura = (int) celsius;
  dt1 = temperatura/10;
  dt2 = temperatura%10;
}

