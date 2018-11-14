

#ifndef _SIMPLE_BLE_H_
#define _SIMPLE_BLE_H_


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bt.h"

#include "Arduino.h"

struct ble_gap_adv_params_s;

class BLE_ADV {
public:

	BLE_ADV(void);
	~BLE_ADV(void);

	/*
	* Start BLE Advertising
	* set local name to advertise
	* return true if success
	*/
	bool begin(String localName = String());

	/*
	*Advertises data on Manufacturer Data field
  *String with the message to be transmitted
	*return true on success
	*/
	bool advertise(String data);

	/*
	*Advertises data on Manufacturer Data field
	*byte array with the message to be transmitted
	*size of the byte array
	*return true if success
	*/
	 bool advertise(byte* data, int size);

	/*
	* Stop BLE Advertising
	*/
	void end(void);

private:
	void clearAdvertiseData();
	String local_name;

};

#endif
