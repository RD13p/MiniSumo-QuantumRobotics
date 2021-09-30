//hola esto es una prueba x3sasads
//variables motores
const int motorIzqAdelante = 11;
const int motorIzqReversa = 10;

const int motorDerAdelante = 6;
const int motorDerReversa = 5;

void setup() {
  
Serial.begin(9600);
// Se declara el pin y se pone como entrada, ya que
// va a recibir datos  

pinMode(A1, INPUT); //Sensor izquierdo 
pinMode(A2, INPUT); //SENSOR DERECHO
pinMode(motorIzqAdelante, OUTPUT); //Motor1      //MOTOR IZQUIERDO
pinMode(motorIzqReversa, OUTPUT); //Fin Motor1   //MOTOR IZQUIERDO
pinMode(motorDerAdelante, OUTPUT); //Motor2       //MOTOR DERECHO
pinMode(motorDerReversa, OUTPUT); //Fin Motor2   //MOTOR DERECHO
avanzar();
}

void loop() {

float sensorIzq = analogRead(A1);
Serial.print("Sensor Izquierdo: ");
Serial.print(convertirCm(sensorIzq));

float sensorDer = analogRead(A2);
Serial.print("Sensor Derecho: ");
Serial.print(convertirCm(sensorDer));

delay(1000);
}

void avanzar() {
  Serial.println("Avanzar");
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 0);
  analogWrite(motorIzqAdelante, 255);
  analogWrite(motorIzqReversa, 0);
}

void buscarIzq() {
  Serial.println("Buscar");
  analogWrite(motorIzqAdelante, 0);
  analogWrite(motorIzqReversa, 255);
  analogWrite(motorDerAdelante, 255);
  analogWrite(motorDerReversa, 0);  
}
void buscarDer() {
  Serial.println("Buscar");
  analogWrite(motorIzqAdelante, 255);
  analogWrite(motorIzqReversa, 0);
  analogWrite(motorDerAdelante, 0);
  analogWrite(motorDerReversa, 255);  
}

void detener(){
  Serial.println("Detenido");
  analogWrite(motorIzqAdelante, 0);
  analogWrite(motorIzqReversa, 0);
  analogWrite(motorDerAdelante, 0);
  analogWrite(motorDerReversa, 0);
}

float convertirCm(float lecturaSensor){
  float vin = lecturaSensor * 0.0049;
  float r = (2.5 - vin) / 0.034;
  return r;
}
