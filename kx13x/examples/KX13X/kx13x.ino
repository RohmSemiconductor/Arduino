/*
The MIT License (MIT)
Copyright (c) 2020 ROHM Co.,Ltd.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Wire.h>
#include <Arduino.h>

#include "platform.h"
#include "kx13x.h"
#include "kx13x_example.h"

#define UNUSED_VAR(a) (void)a 

/* Set sensor example configuration, modify example config in kx13x_example.c */
uint8_t example_config = KX13X_EXAMPLE_ADP_DATA;
/* Set sensor I2C address */
uint8_t sensor_sad = KX13X_I2C_ADDRESS_1F;

/* Set Arduino int pins connected to sensor int1/2 */
#define ARDUINO_INT1_PIN 5
#define ARDUINO_INT2_PIN 6

/* Arduino loop poll delay */
#define ARDUINO_POLL_DELAY_MS 10

/* Sensor driver data and pointer to sensor config */
struct kx13x sensor_dev;
struct kx13x_cfg *sensor_cfg;
/* Arduino platform functions needed by driver */
struct platform arduino_plat;
/* Flag to indicate timer poll or interrupt */
uint8_t timer_poll;

/* Arduino platform functions */
int arduino_debug_print(struct platform *plat, char *str)
{
	UNUSED_VAR(plat);
	Serial.print(str);
	return PLAT_RC_OK;
}

int arduino_i2c_write(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	uint8_t rc;
	uint8_t sad = *(uint8_t*)plat->plat_data;

	Wire.beginTransmission(sad);
	Wire.write(reg);
	Wire.write(data, size);
	rc = Wire.endTransmission(true);

	if (rc != 0) {
		return PLAT_RC_FAIL;
	}

	return PLAT_RC_OK;
}

int arduino_i2c_read(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	uint8_t rc;
	uint8_t cnt;
	uint8_t sad = *(uint8_t*)plat->plat_data;

	Wire.beginTransmission(sad);
	Wire.write(reg);
	rc = Wire.endTransmission(false);
	if (rc != 0) {
		Serial.print("Read failed!\n");
		return PLAT_RC_FAIL;
	}

	Wire.requestFrom((int)sad, (int)size, (int)true);
	cnt = 0;
	while (Wire.available()) {
		data[cnt] = Wire.read();
		cnt++;
	}

	return PLAT_RC_OK;
}

int arduino_spi_write(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	UNUSED_VAR(plat);
	UNUSED_VAR(reg);
	UNUSED_VAR(data);
	UNUSED_VAR(size);
	// TODO: Add SPI write
	return PLAT_RC_FAIL;
}

int arduino_spi_read(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	UNUSED_VAR(plat);
	UNUSED_VAR(reg);
	UNUSED_VAR(data);
	UNUSED_VAR(size);
	// TODO: Add SPI read
	return PLAT_RC_FAIL;
}

int arduino_delay_ms(struct platform *plat, uint16_t ms)
{
	UNUSED_VAR(plat);
	delay(ms);
	return PLAT_RC_OK;
}

int init_sensor_dev(struct kx13x *dev)
{
	int rc;
	char *sensor_name;

	/* Pass pointer to sad as private plat data */
	arduino_plat.plat_data = (void*)&sensor_sad;
	/* Pass platform functions */
	arduino_plat.write = arduino_i2c_write;
	arduino_plat.read = arduino_i2c_read;
	//arduino_plat.write = arduino_spi_write;
	//arduino_plat.read = arduino_spi_read;
	arduino_plat.delay_ms = arduino_delay_ms;
	arduino_plat.debug_print = arduino_debug_print;

	rc = kx13x_init(dev, &arduino_plat);
	if (rc != KX13X_RC_OK) {
		Serial.print("kx13x_init fail\n");
		return rc;
	}

	sensor_name = kx13x_get_name(dev);
	if (sensor_name == NULL) {
		Serial.print("kx13x_get_name fail\n");
		return KX13X_RC_ERR;
	}

	Serial.print("init_sensor_dev ok, sensor type: ");
	Serial.println(sensor_name);

	return KX13X_RC_OK;
}

/* Flags to indicate if isr called */
uint8_t int1_isr_called = 0;
uint8_t int2_isr_called = 0;

void int1_isr(void)
{
	int1_isr_called = 1;
}

void int_pin2_isr(void)
{
	int2_isr_called = 1;
}

int config_host_int1_pin(uint8_t int1_pin, uint8_t mode, uint8_t trigger)
{
	pinMode(int1_pin, mode);
	attachInterrupt(digitalPinToInterrupt(int1_pin), int1_isr, trigger);
	return 0;
}

int config_host_int2_pin(uint8_t int2_pin, uint8_t mode, uint8_t trigger)
{
	pinMode(int2_pin, mode);
	attachInterrupt(digitalPinToInterrupt(int2_pin), int_pin2_isr, trigger);
	return 0;
}

/* Arduino setup */
void setup() {
	int rc;

	Serial.begin(115200);  
	while (!Serial);
	Wire.begin();

	timer_poll = 1;

	/* init sensor driver */
	rc = init_sensor_dev(&sensor_dev);
	if (rc != KX13X_RC_OK) {
		Serial.print("init_sensor_dev fail\n");
		return;
	}

	sensor_cfg = kx13x_example_update_config(&sensor_dev, example_config);
	
	/* config host int pins based on sensor config */
	if (sensor_cfg->int1) {
		timer_poll = 0;
		if (sensor_cfg->int1->level == KX13X_INT_LEVEL_HIGH) {
			config_host_int1_pin(ARDUINO_INT1_PIN, INPUT, RISING);
		} else {
			config_host_int1_pin(ARDUINO_INT1_PIN, INPUT, FALLING);
		}

	}

	if (sensor_cfg->int2) {
		timer_poll = 0;
		if (sensor_cfg->int2->level == KX13X_INT_LEVEL_HIGH) {
			config_host_int2_pin(ARDUINO_INT2_PIN, INPUT, RISING);
		} else {
			config_host_int2_pin(ARDUINO_INT2_PIN, INPUT, FALLING);
		}
		
	}

	/* set sensor to operating mode */
	rc = kx13x_set_oper_mode(&sensor_dev, KX13X_OPER_MODE_OPERATING);
	if (rc != KX13X_RC_OK) {
		Serial.println("fail to set operating mode");
		return;
	}

	delay(1000);
	Serial.println(" ");
}

void loop_interrupt()
{
	uint8_t int1_occured = 0;
	uint8_t int2_occured = 0;

	if (int1_isr_called) {
		int1_occured = 1;
		int1_isr_called = 0;
	}
	
	if (int2_isr_called) {
		int2_occured = 1;
		int2_isr_called = 0;
	}

	if (int1_occured || int2_occured) {
		(void)kx13x_example_handle_interrupt(&sensor_dev);
	}
}

void loop_timer()
{
  
	(void)kx13x_example_poll_interrupt(&sensor_dev);  
}

/* Arduino loop */
void loop() {

	delay(ARDUINO_POLL_DELAY_MS);
  
	if (timer_poll) {
		loop_timer();    
	} else {    
		loop_interrupt();
	}
}
