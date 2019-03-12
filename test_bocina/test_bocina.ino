int pinaltavoz = 10;
int frecuencia=220;    // frecuencia correspondiente a la nota La
int contador;          // variable para el contador
float m=1.059;         // constante para multiplicar frecuencias

void setup()
{
}

void loop()
{
    //for(contador=0,frecuencia=220;contador<12;contador++){
        //frecuencia=frecuencia*m;     // actualiza la frecuencia
        frecuencia = 500;
        tone(pinaltavoz,frecuencia); // emite el tono
        delay(500);                 // lo mantiene 1.5 segundos
        noTone(pinaltavoz);          // para el tono
        delay(500);                  // espera medio segundo
    //}
}
