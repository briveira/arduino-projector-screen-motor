
#include "IRLibAll.h"

//=============================
// posicion en el stepper para pantalla subida y bajada
// cambiar en función del nº de vueltas a dar al motor
// para tener la pantalla bajada

unsigned int posStepperPantallaSubida = 0;
unsigned int posStepperPantallaBajada = 10000;
 
//=============================
// gestion de recepcion IR

//receptor en IR 2

IRrecvPCI myReceiver(3);
 
//Create a decoder object 
IRdecode myDecoder;   

// ultimo valor recibido por IR
unsigned long ultimoIR = 0;

#define IR_ABAJO 0xfd10ef
#define IR_ARRIBA 0xfd50af
#define IR_REPETICION 0xffffffff

unsigned long loopReceptorIR() {

  unsigned long ret = 0;
  
  if (myReceiver.getResults()) {    
    myDecoder.decode();
    if (myDecoder.protocolNum == NEC) {
      switch(myDecoder.value) {
        case IR_ABAJO: // abajo
        case IR_ARRIBA: // arriba
          ultimoIR = myDecoder.value;
          ret = ultimoIR;          
          break;
        //case IR_REPETICION:  // repeticion del ultimo IR
        //  ret = ultimoIR;          
        //  break;        
      }     
    }
    myReceiver.enableIRIn(); //Restart the receiver    
  }
   
  return ret;
}

void setupIR() {
  myReceiver.enableIRIn(); // Start the receiver  
}

// ==============================
// gestion del led

#define LED_PIN 2

void encenderLed() {
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)  
}
void apagarLed() {
  digitalWrite(LED_PIN, LOW);   // turn the LED on (HIGH is the voltage level)  
}
void setupLed() {
  pinMode(LED_PIN, OUTPUT);
}

// ==============================
// control del stepper

// library from http://www.airspayce.com/mikem/arduino/AccelStepper/
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10     // IN3 on the ULN2003 driver 1
#define motorPin4  11     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

// inicializar stepper
void setupStepper() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(500);  
}

void loopStepper() {

  // mueve el stepper si es preciso
  
  stepper1.run();

  // si el stepper esta en movimiento, encendemos el LED
  
  if (stepper1.isRunning()) {
    encenderLed();
  } else {
    apagarLed();
  }
}

void pararStepper() {

  if (stepper1.isRunning()) {
    encenderLed();
    Serial.println("frenando stepper");
    stepper1.stop();
    stepper1.runToPosition();
    apagarLed();    
  }
}

// ==============================
// setup general

void setup() {
  Serial.begin(9600);

  setupIR();
  setupLed();  
  setupStepper();
}

// ==============================
// loop general


void loop() {
  
  unsigned long tecla = loopReceptorIR();

  if (tecla == IR_ARRIBA) {
    pararStepper();
    stepper1.moveTo(posStepperPantallaSubida);
    Serial.println("iniciando subida de pantalla");
  } else if (tecla == IR_ABAJO) {    
    pararStepper();
    stepper1.moveTo(posStepperPantallaBajada);
    Serial.println("iniciando bajada de pantalla");
  }
  loopStepper();

}

