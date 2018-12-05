/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <PubSubClient.h>

int scanTime = 10; //In seconds

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
     
      
//      if (advertisedDevice.count==1){
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    
        if(advertisedDevice.haveRSSI()&&advertisedDevice.count==1){
         
         Serial.printf("Rssi: %d \n", (int)advertisedDevice.getRSSI());
        }
        else Serial.printf("\n");
    }
     
};

void setup() {
  Serial.begin(115200);
  Serial.println("Start scanning...");
  BLEDevice::init("");
  
}

void loop() {
  
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  
  delay(1000);
}
