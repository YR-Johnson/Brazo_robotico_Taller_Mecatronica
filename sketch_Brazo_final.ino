//Incluye la biblioteca Servo para controlar los motores servo.
#include <Servo.h>

//Declara objetos Servo para cada una de las articulaciones del brazo robótico.
Servo servoBase;
Servo servoHombro;
Servo servoCodo;
Servo servoPinza;

//Define los pines de conexión para un LED (pinTestigo) y para cada servo.
const int pinTestigo = 3;
const int pinBase = 11;
const int pinHombro = 9;
const int pinCodo = 10;
const int pinPinza = 6;

//Define los pines de conexión para los controles analógicos de movimiento (direcciones X, Y, Z y G del joystick).
const int pinXdir = 0;
const int pinYdir = 1;
const int pinZdir = 2;
const int pinGdir = 3;

//Define valores mínimos y máximos de los valores analógicos y un retraso entre movimientos de los servos en milisegundos.
const int valorAnalogicoMin = 100;
const int valorAnalogicoMax = 923;
const int retardoMovimiento = 10;

//Define los límites de ángulo para cada servo, lo que ayuda a evitar movimientos que podrían dañar el brazo robótico.
const int anguloMinBase = 0;
const int anguloMaxBase = 170;
const int anguloMinHombro = 125;
const int anguloMaxHombro = 250;
const int anguloMinCodo = 35;
const int anguloMaxCodo = 80;
const int anguloMinPinza = 130;
const int anguloMaxPinza = 155;  // CAMBIO REALIZADO AQUÍ: Cambiado de 180 a 155 para limitar el ángulo a 25 grados

//Configura el modo y estado inicial del LED en pinTestigo para indicar que el sistema está encendido.
//Luego, inicializa los servos asignándoles sus pines de control.
void setup() {
  pinMode(pinTestigo, OUTPUT);
  digitalWrite(pinTestigo, HIGH);
  servoBase.attach(pinBase);
  servoHombro.attach(pinHombro);
  servoCodo.attach(pinCodo);
  servoPinza.attach(pinPinza);
}
//Lee los valores analógicos del joystick en cada dirección para obtener la posición en X, Y, Z y la dirección de la pinza.
void loop() {
  int dirX = analogRead(pinXdir);
  int dirY = analogRead(pinYdir);
  int dirZ = analogRead(pinZdir);
  int dirG = analogRead(pinGdir);

  // Determinar la dirección de movimiento para cada servo, llamando a la función obtenerDireccion que analiza los valores leídos.
  int direccionBase = obtenerDireccion(dirX);
  int direccionHombro = obtenerDireccion(dirY);
  int direccionCodo = obtenerDireccion(dirZ);
  int direccionPinza = obtenerDireccion(dirG);

  //Mueve los servos a sus nuevos ángulos según las direcciones y los límites especificados para cada articulación del brazo robótico.
  moverServoConDireccion(servoBase, direccionBase, anguloMinBase, anguloMaxBase);
  moverServoConDireccion(servoHombro, direccionHombro, anguloMinHombro, anguloMaxHombro);
  moverServoConDireccion(servoCodo, direccionCodo, anguloMinCodo, anguloMaxCodo);
  moverServoConDireccion(servoPinza, direccionPinza, anguloMinPinza, anguloMaxPinza);

  //Espera un tiempo corto para permitir un movimiento más controlado.
  delay(retardoMovimiento);  // Cambiado de delay(movementDelay) a delay(retardoMovimiento)
}

//Define la función obtenerDireccion, que interpreta los valores analógicos del joystick y devuelve la dirección del movimiento:
//-1 para retroceso, 1 para avance y 0 para sin movimiento.
// Función para determinar la dirección de movimiento
int obtenerDireccion(int valorAnalogico) {
  if (valorAnalogico <= valorAnalogicoMin) {
    return -1;  // Retroceso
  } else if (valorAnalogico >= valorAnalogicoMax) {
    return 1;  // Avance
  } else {
    return 0;  // Sin movimiento
  }
}

//Define la función moverServoConDireccion, que mueve el servo un paso en la dirección indicada,
//limitando el ángulo dentro del rango permitido (anguloMin y anguloMax).
// Función para mover el servo según la dirección establecida y los límites de ángulo
void moverServoConDireccion(Servo &servo, int direccion, int anguloMin, int anguloMax) {
  int anguloActual = servo.read();                                              // Obtener el ángulo actual del servo
  int nuevoAngulo = constrain(anguloActual + direccion, anguloMin, anguloMax);  // Calcular el nuevo ángulo
  servo.write(nuevoAngulo);                                                     // Mover el servo al nuevo ángulo
}