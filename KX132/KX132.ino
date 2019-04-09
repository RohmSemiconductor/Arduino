/*
The MIT License (MIT)
Copyright (c) 2019 Kionix Inc.

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

#include "KX132_drv.h"

/* Arduino functions passed to driver */
struct platform_functions arduino_funcs;

uint8_t arduino_debug_println(char *str)
{
    Serial.println(str);
	return RC_OK;
}

uint8_t arduino_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
	uint8_t rc;

	Wire.beginTransmission(sad);
	Wire.write(reg);
	Wire.write(data, size);
	rc = Wire.endTransmission(true);

	if(rc != 0) {
		return RC_FAIL;
	}

	return RC_OK;
}

uint8_t arduino_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, int size)
{
	uint8_t rc;
	uint8_t cnt;

	Wire.beginTransmission(sad);
	Wire.write(reg);
	rc = Wire.endTransmission(false);
	if (rc != 0) {
		Serial.print("Read failed!");
		return RC_FAIL;
	}

	Wire.requestFrom((int)sad, (int)size, (int)true);
	cnt = 0;
	while(Wire.available()) {
		data[cnt] = Wire.read();
		cnt++;
	}

	return RC_OK;
}

uint8_t arduino_delay_ms(uint16_t ms)
{
	delay(ms);
	return RC_OK;
}

void setup() {
	uint8_t rc;

	Serial.begin(115200);
	while (!Serial);

	Wire.begin();

	/* Pass arduino functions to driver */
	arduino_funcs.i2c_write = arduino_i2c_write;
	arduino_funcs.i2c_read = arduino_i2c_read;
	arduino_funcs.delay_ms = arduino_delay_ms;
	arduino_funcs.debug_println = arduino_debug_println;
	KX132_set_platform_functions(&arduino_funcs);

	/* Init driver */
	rc = KX132_init(KX132_DEVICE_ADDRESS_1F);
	if (rc != RC_OK) {
		Serial.println(F("KX132_init fail"));
		Serial.flush();
		return;
	}
	Serial.println(F("KX132_init ok"));

	/* Write sensor lowpower settings */
	rc = KX132_set_lowpower_config();
	if (rc != RC_OK) {
		Serial.println("KX132_set_lowpower_config fail");
		Serial.flush();
		return;
	}
	Serial.println(F("KX132_set_lowpower_config ok"));
	
	KX132_debug_dump_regs();
	Serial.println(" ");
	delay(1000);
}

void loop() {
	uint8_t rc;
	float xyz[3];

	/* TODO: add delay based on odr used in driver */
	delay(500);
	rc = KX132_get_xyz(xyz);

	if (rc == RC_OK) {
		Serial.write("KX132 (X) = ");
		Serial.print(xyz[0]);
		Serial.print(" [g]");
		Serial.write("(Y) = ");
		Serial.print(xyz[1]);
		Serial.print(" [g]");
		Serial.write("(Z) = ");
		Serial.print(xyz[2]);
		Serial.println(" [g]");
	}
}
