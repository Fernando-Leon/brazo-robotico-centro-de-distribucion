
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
    bendTyphonElbow();
    rotateGriffinBase("center");
    natashaClaw.write(90);
    bendNemesisArm();
    delay(2000);
}

void loop() {
    stepOneGetBox();
    delay(2000);
    stepTwoCheckBoxRIFD();
    delay(2000);
    stepThreePutBox();
    delay(2000);
    stepFourReturn();
    delay(2000);
}


void openNatashaClaw() {
    natashaClaw.write(170);
}

void closeNatashaClaw(int angle = 90) {
    natashaClaw.write(angle);
}


void stretchNemesisArm(int angle = 170) {
    nemesisArm.write(angle);
}

void bendNemesisArm() {
    nemesisArm.write(100);
}

void stretchTyphonElbow() {
    typhonElbow.write(180);
}

void bendTyphonElbow() {
    typhonElbow.write(100);
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

void stepOneGetBox() {
    delay(1000);
    openNatashaClaw();
    delay(1000);
    stretchNemesisArm(155);
    delay(1000);
    closeNatashaClaw(100);
    delay(1000);
    bendNemesisArm();
    delay(1000);
}

void stepTwoCheckBoxRIFD() {
    delay(1000);
    stretchTyphonElbow();
    delay(1000);
    stretchNemesisArm();
    delay(2000);
    bendNemesisArm();
    delay(1000);
}

void stepThreePutBox() {
    delay(1000);
    rotateGriffinBase("right");
    delay(1000);
    stretchNemesisArm();
    delay(1000);
    openNatashaClaw();
    delay(1000);
}

void stepFourReturn() {
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
