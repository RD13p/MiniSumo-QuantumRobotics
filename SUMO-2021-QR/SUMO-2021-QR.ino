//Variables motores
const int motorIzqAdelante = 11;
const int motorIzqReversa = 10;

const int motorDerAdelante = 6;
const int motorDerReversa = 5;

//Distancia detección
int dist  = 30;

//Variables sensores
#define sensorIzqPin A1
#define sensorDerPin A2

void setup() {
  
Serial.begin(9600);

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

if (sensorIzq < dist && sensorDer < dist) avanzar();
if (sensorIzq >= dist && sensorDer < dist) buscarIzq();
if (sensorIzq < dist && sensorDer >= dist) buscarDer();
if (sensorIzq > dist && sensorDer > dist) detener(100);

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
  analogWrite(motorIzqReversa, 0);
  analogWrite(motorDerAdelante, 100);
  analogWrite(motorDerReversa, 0);  
}

//Girar a la derecha
void buscarDer() {
  Serial.println("Buscar");
  analogWrite(motorIzqAdelante, 100); 
  analogWrite(motorIzqReversa, 0);
  analogWrite(motorDerAdelante, 0);
  analogWrite(motorDerReversa, 0);  
}

void detener(float microseconds){
  Serial.println("Detenido");
  analogWrite(motorIzqAdelante, 255);
  analogWrite(motorIzqReversa, 255);
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 255);
  delay(microseconds);
}

//Convertir a Centimetros las lecturas del sensor
float convertirCm(float lecturaSensor){
  float vin = lecturaSensor * 0.0049;
  float r = (2.5 - vin) / 0.034;
  return r;
}
