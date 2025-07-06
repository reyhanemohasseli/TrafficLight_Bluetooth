#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string>


#define Red_LED 27
#define Green_LED 23
#define Yellow_LED 22 
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-abcd-1234-abcd-123456789abc"

int command = 0;

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    Serial.println("onWrite called!");
    std::string value = pCharacteristic->getValue();
    Serial.print("Value length: ");
    Serial.println(value.length());
    if (value.length() > 0) {
      char message = value[0];           // Get the first byte of the string (which is a character)

      
      command = message;                 // Convert the received byte into an integer

      Serial.print("Received command: ");
      Serial.println(command);
      if(command == 1){digitalWrite(Green_LED , HIGH);
      digitalWrite(Red_LED , LOW);
      digitalWrite(Yellow_LED , LOW);
      }
      else if(command == 2){digitalWrite(Green_LED , LOW);
      digitalWrite(Red_LED , HIGH);
      digitalWrite(Yellow_LED , LOW);
      }
  }
}
};


void setup(){
  Serial.begin(115200);
  pinMode(Red_LED , OUTPUT);
  pinMode(Green_LED , OUTPUT);
  pinMode(Yellow_LED , OUTPUT);

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
CHARACTERISTIC_UUID,
 BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
 pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your iphone!");
}


void loop() {
  delay(5000);
  Serial.println("Still running...");
  if(command == 0){                    //control the light without bluetooth
    
    digitalWrite(Red_LED , HIGH);
    digitalWrite(Green_LED , LOW);
    digitalWrite(Yellow_LED , LOW);
    delay(6000);
    digitalWrite(Red_LED , LOW);
    digitalWrite(Green_LED , HIGH);
    digitalWrite(Yellow_LED , LOW);
    delay(6000);
  }
}

