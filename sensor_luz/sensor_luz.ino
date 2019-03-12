int ledPin = 13;
int sensorPin = 0;
int s1 = 1, s2 = 2, s3 = 3, s4 = 4, s5 =5;
double alpha = 0.75;
int period = 5000;
double change = 0.0;
int lim = 1000;
void setup(){
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
}
void loop()
{
static double oldValue = 0;
static double oldChange = 0;
int rawValue = analogRead(sensorPin);
int r1 = analogRead(s1);
int r2 = analogRead(s2);
int r3 = analogRead(s3);
int r4 = analogRead(s4);
int r5 = analogRead(s5);

if(rawValue < lim){
  Serial.println(rawValue);
  Serial.print("valor 0\n");
}
//else
if(r1<lim){
  Serial.println(r1);
  Serial.print("Valor de r1\n");
}
//else
if(r2<lim){
  Serial.println(r2);
  Serial.print("Valor de r2\n");
}
//else
if(r3<lim){
  Serial.println(r3);
  Serial.print("Valor de r3\n");
}
//else
if(r4<lim){
  Serial.println(r4);
  Serial.print("Valor de r4\n");
}
//else 
if(r5<lim){
  Serial.println(r5);
  Serial.print("Valor de r5\n");
}
/*double value = alpha * oldValue
+ (1 - alpha) * rawValue;
change = value - oldValue;
digitalWrite(ledPin, (change <
0.0 && oldChange > 0.0));
oldValue = value;
oldChange = change;*/
delay(period);
}
