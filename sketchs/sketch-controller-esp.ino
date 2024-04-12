#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>

Servo typhonElbow; // Codo
Servo griffinBase; // Base
Servo natashaClaw; // Garra
Servo nemesisArm; // Brazo

#define RST_PIN         22          
#define SS_PIN          5          

static const int servoNemesis = 13;
static const int servoTyphon = 12;
static const int servoNatasha = 14;
static const int servoGriffind = 27;

const char* ssid = "Layon";
const char* password = "123456789";
const char* direccion_servidor = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

String readCard() {
  String lastName = "";
  
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte block;
  byte len;
  MFRC522::StatusCode status;


  if (!mfrc522.PICC_IsNewCardPresent()) {
    return lastName;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return lastName;
  }

  byte buffer[18];
  block = 1;
  len = 18;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    return lastName;
  }

  status = mfrc522.MIFARE_Read(block, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    return lastName;
  }

  for (uint8_t i = 0; i < 16; i++) {
    lastName += (char)buffer[i];
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  lastName.trim();
  return lastName;
}


void setup() {
  Serial.begin(9600);  

    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
      Serial.println("Conectando...");
  }
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  nemesisArm.setPeriodHertz(50);    
	nemesisArm.attach(servoNemesis, 500, 2400); 
  typhonElbow.setPeriodHertz(50);    
	typhonElbow.attach(servoTyphon, 500, 2400); 
  natashaClaw.setPeriodHertz(50);    
	natashaClaw.attach(servoNatasha, 500, 2400); 
  griffinBase.setPeriodHertz(50);    
	griffinBase.attach(servoGriffind, 500, 2400); 
  bendTyphonElbow();
  rotateGriffinBase("center");
  natashaClaw.write(90);
  bendNemesisArm();        
  delay(2000);                            
  SPI.begin();                                                  
  mfrc522.PCD_Init();                                              
  Serial.println(F("Read personal data on a MIFARE PICC:"));    
}

// Funciones del servomotor

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

void loop() {
  String cardName = readCard();

  if (cardName.length() > 0) {
    
    Serial.println(cardName);
    if(cardName == "PuntoA") {
      delay(1000);
      initProceso("left", cardName);
      delay(2000);
    }else {
      delay(1000);
      initProceso("right", cardName);
      delay(2000);
    }
    Serial.println(cardName);
  }
  
  delay(1000); //change value if you want to read cards faster
}

// Funcion para iniciar proceso

void initProceso(String rotate, String dot) {
  delay(1500);
  openNatashaClaw();
  delay(1500);
  stretchNemesisArm(155);
  delay(1500);
  closeNatashaClaw(100);
  delay(1500);
  bendNemesisArm();
  delay(1500);
  stretchTyphonElbow();
  delay(1500);
  rotateGriffinBase(rotate);
  delay(1500);
  stretchNemesisArm(155);
  delay(1500);
  openNatashaClaw();
  delay(1500);
  bendNemesisArm();
  delay(1500);
  closeNatashaClaw();
  delay(1500);
  bendTyphonElbow();
  delay(1500);
  rotateGriffinBase("center");
  delay(1500);

  HTTPClient http;
  http.begin("http://192.168.125.182:5000/api/registros"); // Cambia esto a la dirección donde se ejecute tu API Flask
  http.addHeader("Content-Type", "application/json");

  String requestBody = "{\"ubicacion\":\"" + dot + "\"}"; // Solo la ubicación
  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
      Serial.print("HTTP POST request successful, response code: ");
      Serial.println(httpResponseCode);
  } else {
      Serial.print("Error en la solicitud HTTP, response code: ");
      Serial.println(httpResponseCode);
  }

  http.end();
}


