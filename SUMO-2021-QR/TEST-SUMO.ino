//Variables motores
const int motorIzqAdelante = 6;
const int motorIzqReversa = 5;

const int motorDerAdelante =11;
const int motorDerReversa = 10;

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
buscarDer();
}

void avanzar() {
  Serial.println("Avanzar");
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 0);
  analogWrite(motorIzqAdelante, 230);
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
  analogWrite(motorIzqAdelante, 120); 
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
