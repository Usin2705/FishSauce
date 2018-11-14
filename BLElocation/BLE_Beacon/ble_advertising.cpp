de#include "ble_advertising.h"
#include "esp32-hal-log.h"

#include "bt.h"
#include "bta/bta_api.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"


#define MAX_MANUFACTURER_DATA_SIZE 20
#define MAX_SERVICE_DATA_SIZE 11

esp_ble_adv_data_t adv_data; // data that will be advertised
byte dataBuffer[50];
byte dataBuffer2[50];


// Standard parameters
static esp_ble_adv_data_t _adv_config = {
	.set_scan_rsp = false,
	.include_name = true,
	.include_txpower = true,
	.min_interval = 512,
	.max_interval = 1024,
	.appearance = 0,
	.manufacturer_len = 0,
	.p_manufacturer_data = NULL,
	.service_data_len = 0,
	.p_service_data = NULL,
	.service_uuid_len = 0,
	.p_service_uuid = NULL,
	.flag = (ESP_BLE_ADV_FLAG_NON_LIMIT_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT)
};



// 
static esp_ble_adv_params_t _adv_params = {
	.adv_int_min = 512,
	.adv_int_max = 1024,
	.adv_type = ADV_TYPE_NONCONN_IND,         // Excelent description of this parameter here: https://www.esp32.com/viewtopic.php?t=2267
	.own_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.peer_addr = { 0x00, },
	.peer_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.channel_map = ADV_CHNL_ALL,
	.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static void _on_gap(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
	if (event == ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT) {
		esp_ble_gap_start_advertising(&_adv_params);
	}
}

static bool _init_gap(const char * name, esp_ble_adv_data_t* adv_data) {
	if (!btStarted() && !btStart()) {
		log_e("btStart failed");
		return false;
	}
	esp_bluedroid_status_t bt_state = esp_bluedroid_get_status();
	if (bt_state == ESP_BLUEDROID_STATUS_UNINITIALIZED) {
		if (esp_bluedroid_init()) {
			log_e("esp_bluedroid_init failed");
			return false;
		}
	}
	if (bt_state != ESP_BLUEDROID_STATUS_ENABLED) {
		if (esp_bluedroid_enable()) {
			log_e("esp_bluedroid_enable failed");
			return false;
		}
	}
	if (esp_ble_gap_set_device_name(name)) {
		log_e("gap_set_device_name failed");
		return false;
	}
	if (esp_ble_gap_config_adv_data(adv_data)) {
		log_e("gap_config_adv_data failed");
		return false;
	}
	if (esp_ble_gap_register_callback(_on_gap)) {
		log_e("gap_register_callback failed");
		return false;
	}
	return true;
}

static bool _stop_gap()
{
	if (btStarted()) {
		esp_bluedroid_disable();
		esp_bluedroid_deinit();
		btStop();
	}
	return true;
}

BLE_ADV::BLE_ADV()
{
	local_name = "esp32";
	adv_data = {
		.set_scan_rsp = false,
		.include_name = true,
		.include_txpower = true,
		.min_interval = 512,
		.max_interval = 1024,
		.appearance = 0,
		.manufacturer_len = 0,
		.p_manufacturer_data = NULL,  //manufacturer data is what we will use to broadcast our info
		.service_data_len = 0,
		.p_service_data = NULL,
	};
}

BLE_ADV::~BLE_ADV(void)
{
	clearAdvertiseData();
	_stop_gap();
}

bool BLE_ADV::begin(String localName)
{
	if (localName.length()) {
		local_name = localName;
	}
	return _init_gap(local_name.c_str(), &_adv_config);
}

void BLE_ADV::end()
{
	_stop_gap();
}

bool BLE_ADV::advertise(String data) {
	data.getBytes(dataBuffer, data.length() + 1);
	return advertise(dataBuffer, data.length());
}

bool BLE_ADV::advertise(byte* data, int size) {
	clearAdvertiseData();
	return _init_gap(local_name.c_str(), &adv_data);
}


void BLE_ADV::clearAdvertiseData() {
	if (adv_data.p_manufacturer_data != NULL) {
		free(adv_data.p_manufacturer_data);
		adv_data.p_manufacturer_data = NULL;
		adv_data.manufacturer_len = 0;
	}
	if (adv_data.p_service_data != NULL) {
		free(adv_data.p_service_data);
		adv_data.p_service_data = NULL;
		adv_data.service_data_len = 0;
	}
}
