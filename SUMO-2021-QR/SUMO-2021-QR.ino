//Variables motores
const int motorIzqAdelante = 11;
const int motorIzqReversa = 10;

const int motorDerAdelante = 6;
const int motorDerReversa = 5;

//Distancia detección
int dist  = 15;
int maxdist = 65;
int mindist = 8;
//Bandera 
// 0 = en frente - sin valor
// 1 = izquierda
// 2 = derecha
int bandera = 0;

//Variables sensores
#define sensorIzqPin A1
#define sensorDerPin A2

void setup() {
  
Serial.begin(9600);
delay(5000);

// Pines de sensores 
pinMode(sensorIzqPin, INPUT); //Sensor izquierdo 
pinMode(sensorDerPin, INPUT); //SENSOR DERECHO

//Pines de motores
pinMode(motorIzqAdelante, OUTPUT); //Motor1      //MOTOR IZQUIERDO
pinMode(motorIzqReversa, OUTPUT); //Fin Motor1   //MOTOR IZQUIERDO
pinMode(motorDerAdelante, OUTPUT); //Motor2       //MOTOR DERECHO
pinMode(motorDerReversa, OUTPUT); //Fin Motor2   //MOTOR DERECHO
}

void loop() {
//Si sabemos que el otro sumo se fue por la izquierda, seguimos girando a la izquierda hasta encontrarlo
//if (bandera == 1) buscarIzq();

//Si sabemos que el otro sumo se fue por la derecha, seguimos girando a la derecha hasta encontrarlo
//if (bandera == 2) buscarDer();

//Lectura del sensor izquierdo
float sensorIzq = analogRead(sensorIzqPin);
Serial.print("Sensor Izquierdo: ");
sensorIzq = convertirCm(sensorIzq);
Serial.println(sensorIzq);

//Lectura del sensor derecho 
float sensorDer = analogRead(sensorDerPin);
Serial.print("Sensor Derecho: ");
sensorDer = convertirCm(sensorDer);
Serial.println(sensorDer);

//Si esta cerca
if (sensorIzq < dist && sensorDer < dist){
avanzar();
bandera = 0;
  if ((sensorIzq < mindist || sensorDer < mindist) || (sensorIzq > maxdist || sensorDer > maxdist)) {
    while (true) {
    Serial.print("Entre en el loop");
    avanzar();
    sensorIzq = analogRead(sensorIzqPin);
    sensorIzq = convertirCm(sensorIzq);
    sensorDer = analogRead(sensorDerPin);
    sensorDer = convertirCm(sensorDer);
    //Detectar distancia valida
    if ((sensorIzq > mindist && sensorIzq < dist) || (sensorDer > mindist && sensorDer < dist)){
      break;
    }
}
}
}

if ((sensorIzq >= dist && sensorDer < dist) || bandera == 1){ 
bandera = 1;
Serial.print("Bandera = 1");
buscarIzq();
}

if ((sensorIzq < dist && sensorDer >= dist) || bandera == 2){
bandera = 2;
Serial.print("Bandera = 2");
buscarDer();
}

//Condicion inicial
if (sensorIzq >= dist && sensorDer >= dist){
  if (bandera == 0){
    buscarDer();
  }
  else if (bandera == 1){
    buscarIzq();
  }
  else if (bandera == 2){
    buscarDer();
  }
}
}

void avanzar() {
  Serial.println("Avanzar");
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 0);
  analogWrite(motorIzqAdelante, 255);
  analogWrite(motorIzqReversa, 0);
}

//Girar a la izquierda
void buscarIzq() {
  Serial.println("Buscar");
  analogWrite(motorIzqAdelante, 0);
  analogWrite(motorIzqReversa, 75);
  analogWrite(motorDerAdelante, 75);
  analogWrite(motorDerReversa, 0); 
  delay(5);   
}

//Girar a la derecha
void buscarDer() {
  Serial.println("Buscar");
  analogWrite(motorIzqAdelante, 0); 
  analogWrite(motorIzqReversa, 0);
  analogWrite(motorDerAdelante, 0);
  analogWrite(motorDerReversa, 75);
  delay(5);  
}

void detener(){
  Serial.println("Detenido");
  analogWrite(motorIzqAdelante, 255);
  analogWrite(motorIzqReversa, 255);
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 255);
}

//Convertir a Centimetros las lecturas del sensor
float convertirCm(float lecturaSensor){
  float vin = lecturaSensor * 0.0049;
  float r = (2.5 - vin) / 0.034;
  return r;
}
