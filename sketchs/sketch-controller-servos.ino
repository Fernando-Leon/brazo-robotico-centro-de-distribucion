
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
    natashaClaw.write(90);
    nemesisArm.write(90);

    delay(2000);
}

void loop() {

    natashaClaw.write(180);

    delay(2000);

    natashaClaw.write(90);

    delay(2000);

}