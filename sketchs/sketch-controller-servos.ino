
// Librerias
#include <Servo.h>

// Definicion de pines (servos)
Servo typhonElbow; // Codo
Servo griffinBase; // Base
Servo natashaClaw; // Garra
Servo nemesisArm; // Brazo

void setup() {
    // Inicializacion de los servos
    typhonElbow.attach(6);
    griffinBase.attach(9);
    natashaClaw.attach(10);
    nemesisArm.attach(11);

    // Inicializacion de los servos
    typhonElbow.write(90);
    griffinBase.write(90);
    closeNatashaClaw();
    bendNemesisArm();

    delay(2000);
}

void loop() {
    stepOne();
    delay(5000);
}


void openNatashaClaw() {
    natashaClaw.write(180);
}

void closeNatashaClaw() {
    natashaClaw.write(90);
}


void stretchNemesisArm() {
    nemesisArm.write(180);
}

void bendNemesisArm() {
    nemesisArm.write(90);
}

void stepOne() {
    delay(1000);
    openNatashaClaw();
    delay(1000);
    stretchNemesisArm();
    delay(1000);
    closeNatashaClaw();
    delay(1000);
    bendNemesisArm();
}