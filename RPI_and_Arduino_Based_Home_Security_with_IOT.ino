uint8_t id; //for finger enroll
int Buzzer = 10;
String content = "";
//char character;

//Button Switch Door Loob
int inPinDoorLoob = 2;   
int valDoorLoob = 0;  
int doorLoobStatus = 0;
int pushedDoorLoob = 0;
int doorLoob = 11;


//Button Switch Door Loob
int inPinDoorLabas = 3;   
int valDoorLabas = 0;  
int doorLabasStatus = 0;
int pushedDoorLabas = 0;
int doorLabas = 8;

//ilaw sa pinaka labas
int inPinLight3 = 4;  
int valLight3 = 0; 
int lightStatus3 = 0;
int pushed3 = 0;
int LightPinakaLabas = 7;

//ilaw sa labas
int inPinLight2 = 12;  
int valLight2 = 0; 
int lightStatus2 = 0;
int pushed2 = 0;
int LightsaLabas = 6;

//ilaw sa loob
int inPinLight = 13;  
int valLight = 0; 
int lightStatus = 0;
int pushed = 0;
int LightsaLoob = 5;

//vibration sensor
int vibrasion_sensor = 20;

//Smoke Sensor
int valve = 9;
int smokeA0 = A5;
int sensorThres = 300;
//
//#define BLYNK_PRINT Serial
//
#include <Adafruit_Fingerprint.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "xU0w1JkSk7zDBwJ14bljSOVT3aWYJafk";
char ssid[] = "THESISONLY";
char pass[] = "ipasokmoilabasmo";

#define EspSerial Serial
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);


//Serial 0,1 rx tx
//Serial1 18, 19 rx tx
//Serial2 16, 17 rx tx
//Serial3 14, 15 rx tx 



Adafruit_Fingerprint finger1 = Adafruit_Fingerprint(&Serial1);
//fplabas
Adafruit_Fingerprint finger2 = Adafruit_Fingerprint(&Serial3);
#define SIM900 Serial2
String textForSMS =  "\nMay Pumasok";  
  
String f1001 = "+639976479080";

int buzzerCount = 0;
int buzzerCount2 = 0;
void setup()  
{
  Serial.begin(9600);

  SIM900.begin(9600);
 // Serial.setDebugOutput(true);
 //Doors
 //esp8266

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  
  pinMode(doorLoob, OUTPUT);
  pinMode(doorLabas, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(doorLoob, HIGH);
  digitalWrite(doorLabas, HIGH);
  digitalWrite(Buzzer, HIGH);
   
  //Lights
  pinMode(inPinLight, INPUT_PULLUP); 
  pinMode(inPinLight2, INPUT_PULLUP); 
  pinMode(inPinLight3, INPUT_PULLUP); 
  //doors 
  pinMode(inPinDoorLoob, INPUT_PULLUP);
  pinMode(inPinDoorLabas, INPUT_PULLUP);

 
   
  pinMode(LightsaLoob, OUTPUT);
  pinMode(LightsaLabas, OUTPUT);
  pinMode(LightPinakaLabas, OUTPUT);
  
  digitalWrite(LightsaLoob,HIGH);
  digitalWrite(LightsaLabas,HIGH);
  digitalWrite(LightPinakaLabas,HIGH);

  //Smoke Sensor
  pinMode(smokeA0, INPUT);
  
  pinMode(valve, OUTPUT);
  
  digitalWrite(valve, HIGH);
  
  while (!Serial); 
  delay(100);
  //Serial.println("\n\nAdafruit finger detect test");
  // set the data rate for the sensor serial port
  finger1.begin(57600);
  finger2.begin(57600);
  
  //if (finger1.verifyPassword() and finger2.verifyPassword()) {
    if (finger2.verifyPassword()) {
    Serial.println("Found fingerprint sensors!");
  } else {
    Serial.println("Did not find any fingerprint sensors :(");
    while (1) { delay(1); }
  }

  finger1.getTemplateCount();
  finger2.getTemplateCount();
  
  Serial.print("Fingerprint Sensor1 contains "); Serial.print(finger1.templateCount); Serial.println(" templates");
  Serial.print("Fingerprint Sensor2 contains "); Serial.print(finger2.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");


//blynk send app


//enroll

}

void loop()                     // run over and over again
{
  //esp
  Blynk.run();

  //Fingerprint Sensor Loob
  getFingerprintDoorLoob();
  delay(50);           
  //Fingerprint Sensor Labas
  getFingerprintDoorLabas();
  delay(50);

//Door loob
 valDoorLoob = digitalRead(inPinDoorLoob);  // read input value
// Serial.print(valDoorLoob);

  if(valDoorLoob == HIGH && doorLoobStatus == LOW){

    pushedDoorLoob = 1-pushedDoorLoob;
     //Serial.print(pushed);
    delay(100);
  }    
  
  doorLoobStatus = valDoorLoob;
  //Serial.print(doorLoobStatus);
   
  if (pushedDoorLoob == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(doorLoob, HIGH);
  } else {
    digitalWrite(doorLoob, LOW);  
  }

//Door Switch Labas
valDoorLabas = digitalRead(inPinDoorLabas);  // read input value
// Serial.print(valDoorLoob);

  if(valDoorLabas == HIGH && doorLabasStatus == LOW){

    pushedDoorLabas = 1-pushedDoorLabas;
     //Serial.print(pushed);
    delay(100);
  }    
  
  doorLabasStatus = valDoorLabas;
  //Serial.print(doorLoobStatus);
   
  if (pushedDoorLabas == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(doorLabas, HIGH);
  } else {
    digitalWrite(doorLabas, LOW);  
  }


 //Light Switch loob
 valLight = digitalRead(inPinLight);  // read input value
 //Serial.print(valLight);

  if(valLight == HIGH && lightStatus == LOW){

    pushed = 1-pushed;
     //Serial.print(pushed);
    delay(100);
  }    
  
  lightStatus = valLight;
  //Serial.print(lightStatus);
   
  if (pushed == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(LightsaLoob, HIGH);
  } else {
    digitalWrite(LightsaLoob, LOW);  
  }

 //light switch labas
 valLight2 = digitalRead(inPinLight2);  // read input value
 // Serial.print(valLight2);

  if(valLight2 == HIGH && lightStatus2 == LOW){

    pushed2 = 1-pushed2;
     Serial.print(pushed2);
    delay(100);
  }    
  
  lightStatus2 = valLight2;
  //Serial.print(lightStatus2);
   
  if (pushed2 == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(LightsaLabas, HIGH);
    //delay(1000);
   //digitalWrite(in2, LOW);
  } else {
    digitalWrite(LightsaLabas, LOW);  
  }

//light sa pinaka labas
valLight3 = digitalRead(inPinLight3);  // read input value
// Serial.print(valLight2);

  if(valLight3 == HIGH && lightStatus3 == LOW){

    pushed3 = 1-pushed3;
    // Serial.print(pushed2);
    delay(100);
  }    
  
  lightStatus3 = valLight3;
  //Serial.print(lightStatus2);
   
  if (pushed3 == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(LightPinakaLabas, HIGH);
    //delay(1000);
   //digitalWrite(in2, LOW);
  } else {
    digitalWrite(LightPinakaLabas, LOW);  
  }


//Vibration Sensor
 long measurement = vibration();
  delay(50);
 // Serial.println(measurement);
  if (measurement > 15000){
    digitalWrite(Buzzer, LOW);
    delay(3000);
  }
  else{
    digitalWrite(Buzzer, HIGH); 
  }

  //Smoke Sensor
  int analogSensor = analogRead(smokeA0);

    Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  Serial.println(analogSensor);
  
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(Buzzer,LOW);
    digitalWrite(valve,LOW);
  }
  else
  {
    digitalWrite(Buzzer,HIGH);
    digitalWrite(valve,HIGH);
  }
//
//  if(buzzerCount == 3){
//    buzzerCount = 0;
//    sendsms("Door sa loob: May gustong pumasok", f1001);
//    Serial.println(textForSMS);
//    Serial.println("message sent.");
//  }
//  if(buzzerCount2 == 3){
//    buzzerCount2 = 0;
//    sendsms("Door sa labas: May gustong pumasok", f1001);
//    Serial.println(textForSMS);
//    Serial.println("message sent.");
//  }     





    
}


long vibration(){
  long measurement=pulseIn (vibrasion_sensor, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}


//GSM Sim 900a
void sendsms(String message, String number)
{
String mnumber = "AT + CMGS = \""+number+"\""; 
   SIM900.print("AT+CMGF=1\r");                   
  delay(1000);
  SIM900.println(mnumber);  // recipient's mobile number, in international format
 
  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
 // SIM900power();  
}

uint8_t getFingerprintDoorLoob() {
  uint8_t p = finger1.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
     // Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    //  Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  // OK success!

  p = finger1.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
     // Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
     // Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
     // Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger1.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    digitalWrite(doorLoob, LOW); 
    sendsms(textForSMS + " Noah", f1001);
    Serial.println(textForSMS);
    Serial.println("message sent.");  
    delay(3000);
    digitalWrite(doorLoob, HIGH);
    delay(1000);
   // Serial.print(finger1.fingerID); 
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
//    Serial.println("Did not find a match");
//    digitalWrite(Buzzer,LOW);
//    buzzerCount = buzzerCount + 1;
//    delay(1000);
//    digitalWrite(Buzzer,HIGH);
//    
    
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   

  return finger1.fingerID;
}


uint8_t getFingerprintDoorLabas() {
  uint8_t p = finger2.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
     // Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    //  Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger2.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
     // Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
     // Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
     // Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger2.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    
    digitalWrite(doorLabas, LOW); 
     
 // sendsms(textForSMS, f1001); // you can use a variable of the type String
  if (finger2.fingerID = 1){
  sendsms(textForSMS + " Noah", f1001);
  Serial.println(textForSMS);
  Serial.println("message sent.");   
  }
  else if(finger2.fingerID = 2){
  sendsms(textForSMS + " Cedie", f1001);
  Serial.println(textForSMS);
  Serial.println("message sent.");  
  }
  else if(finger2.fingerID = 3){
  sendsms(textForSMS + " Dang", f1001);
  Serial.println(textForSMS);
  Serial.println("message sent.");  
  }
  else if(finger2.fingerID = 4){
  sendsms(textForSMS + " Warren", f1001);
  Serial.println(textForSMS);
  Serial.println("message sent.");  
  }
  else{
  sendsms(textForSMS, f1001);
  Serial.println(textForSMS);
  Serial.println("message sent.");
  }
    delay(3000);
    digitalWrite(doorLabas, HIGH);
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
//    Serial.println("Did not find a match");
//    digitalWrite(Buzzer,LOW);
//    delay(1000);
//    digitalWrite(Buzzer,HIGH);
//     buzzerCount2 = buzzerCount2 + 1;
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  return finger2.fingerID;
}




void SerialInput() {
  if (Serial.available()) {  // Watch for Serial data
    content = Serial.read();  // Read Serial character
//    content.concat(character);  // Add character to holding String
    if (content == "add fs1"){  // If last character is new line...
//       Serial.println("Ready to enroll a fingerprint!");
        Blynk.virtualWrite(V0, "Ready to enroll a fingerprint!");
        Blynk.virtualWrite(V0, "Please type in the ID # (from 1 to 127) you want to save this finger as...");
//        Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
        id = readnumber();
        if (id == 0) {// ID #0 not allowed, try again!
           return;
        }
        Blynk.virtualWrite(V0, "Enrolling ID #");
//        Serial.print("Enrolling ID #");
        Blynk.virtualWrite(V0, id);
//        Serial.println(id);
  
  while (!  FingerprintEnroll1() );

     // Blynk.virtualWrite(V1, content);  // ...send string to terminal
      content = "";  // Clear holding String
    }
  }
}


uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t FingerprintEnroll1() {

  int p = -1;
  //Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  Blynk.virtualWrite(V0, "Waiting for valid finger to enroll as #");
  while (p != FINGERPRINT_OK) {
    p = finger1.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Blynk.virtualWrite(V0, "Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
     Blynk.virtualWrite(V0, "Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
    Blynk.virtualWrite(V0, "Imaging error");
      break;
    default:
    Blynk.virtualWrite(V0, "Unknown error");
      break;
    }
  }

  // OK success!

  p = finger1.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
//      Serial.println("Image converted");
       Blynk.virtualWrite(V0, "Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
//      Serial.println("Image too messy");
       Blynk.virtualWrite(V0, "Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
//      Serial.println("Communication error");
       Blynk.virtualWrite(V0, "Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
//      Serial.println("Could not find fingerprint features");
       Blynk.virtualWrite(V0, "Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
//      Serial.println("Could not find fingerprint features");
       Blynk.virtualWrite(V0, "Could not find fingerprint features");
      return p;
    default:
//      Serial.println("Unknown error");
       Blynk.virtualWrite(V0, "Unknown error");
      return p;
  }
  
//  Serial.println("Remove finger");
  Blynk.virtualWrite(V0, "Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger1.getImage();
  }
  Blynk.virtualWrite(V0, "ID " + id);
 // Serial.print("ID "); Serial.println(id);
  p = -1;
//  Serial.println("Place same finger again");
  Blynk.virtualWrite(V0, "Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger1.getImage();
    switch (p) {
    case FINGERPRINT_OK:
     Blynk.virtualWrite(V0, "Image taken");
//      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
     Blynk.virtualWrite(V0, "Communication error");
//      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
     Blynk.virtualWrite(V0, "Imaging error");
//      Serial.println("Imaging error");
      break;
    default:
     Blynk.virtualWrite(V0, "Unknown error");
//      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger1.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
    
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger1.createModel();
  if (p == FINGERPRINT_OK) {
//    Serial.println("Prints matched!");
    Blynk.virtualWrite(V0, "Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
//    Serial.println("Fingerprints did not match");
    Blynk.virtualWrite(V0, "Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger1.storeModel(id);
  if (p == FINGERPRINT_OK) {
     Blynk.virtualWrite(V0, "Stored!");
   Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}




uint8_t FingerprintEnroll2() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger2.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger2.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger2.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger2.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger2.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger2.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger2.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
