#include "ble_advertising.h"
#include <BLEClient.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEAdvertisedDevice.h>


BLE_ADV ble;

void setup() {
	Serial.begin(115200);
	ble.begin("BeaconZ");  //sets the device name
}

void loop() {

//  Serial.print("successful");

	delay(1000);
}
