
// Librerias
#include <Servo.h>

// Definicion de pines (servos)
Servo typhonElbow; // Codo
Servo griffinBase; // Base
Servo natashaClaw; // Garra
Servo nemesisArm; // Brazo

void setup() {
    // Pines de los servos
    typhonElbow.attach(6);
    griffinBase.attach(3);
    natashaClaw.attach(10);
    nemesisArm.attach(11);

    // Inicializacion de los servos
    typhonElbow.write(90);
    rotateGriffinBase("center");
    closeNatashaClaw();
    bendNemesisArm();
    delay(2000);
}

void loop() {
    stepOne();
    delay(5000);
    stepTwo();
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

void stretchTyphonElbow() {
    typhonElbow.write(180);
}

void bendTyphonElbow() {
    typhonElbow.write(90);
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
    delay(1000);
}

void rotateGriffinBase(String rotate) {
    if (rotate == "left") {
        griffinBase.write(0);
    } else if (rotate == "right") {
        griffinBase.write(180);
    } else if(rotate == "center") {
        griffinBase.write(85);
    }
}

void stepTwo() {
    delay(1000);
    rotateGriffinBase("right");
    delay(1000);
    stretchTyphonElbow();
    delay(1000);
    stretchNemesisArm();
    delay(1000);
    openNatashaClaw();
    delay(1000);
    bendNemesisArm();
    delay(1000);
    bendTyphonElbow();
    delay(1000);
    closeNatashaClaw();
    delay(1000);
    rotateGriffinBase("center");
    delay(1000);
}
