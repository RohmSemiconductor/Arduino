/*****************************************************************************
  KX126.cpp

 Copyright (c) 2018 ROHM Co.,Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
//#include <avr/pgmspace.h>
//#include <Arduino.h>
#include <Wire.h>
#include "Arduino.h"
#include "KX126.h"

#define RESET_DELAY 2

KX126::KX126(uint8_t slave_address)
{
  _device_address = slave_address;
  _g_sens = 16384;
}

KX126::~KX126()
{
  _device_address = 0;
  _g_sens = 0;
}

byte KX126::init(void)
{
  byte rc;
  unsigned char reg;
  unsigned char gsel;

  reg = KX126_CNTL2_SRST;
  rc = write(KX126_CNTL2, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write KX126 CNTL2 register");
    return (rc);
  }

  delay(RESET_DELAY);

  rc = read(KX126_WHO_AM_I, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't access KX126");
    return (rc);
  } 
  Serial.print("KX126_WHO_AMI Register Value = 0x");
  Serial.println(reg, HEX);
  
  if (reg != KX126_WAI_VAL) {
    Serial.println("Can't find KX126");
    return (-1);
  }
  
  reg = KX126_CNTL1_VAL;
  rc = write(KX126_CNTL1, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write KX126 CNTL1 register at first");
    return (rc);
  }
  
  reg = KX126_ODCNTL_VAL;
  rc = write(KX126_ODCNTL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write KX126 ODCNTL register");
    return (rc);
  }
  
  rc = read(KX126_CNTL1, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't read KX126 CNTL1 register");
    return (rc);
  }
  gsel = reg & KX126_CNTL1_GSELMASK;
  
  reg |= KX126_CNTL1_PC1;
  rc = write(KX126_CNTL1, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write KX126 CNTL1 register at second");
    return (rc);
  }
  
  switch(gsel) {
    case KX126_CNTL1_GSEL_2G :
      // (Equivalent counts) / (Range) = (32768 / 2)
      _g_sens = 16384;
    break;

    case KX126_CNTL1_GSEL_4G :
      // (Equivalent counts) / (Range) = (32768 / 4)
      _g_sens = 8192;
    break;

    case KX126_CNTL1_GSEL_8G :
      // (Equivalent counts) / (Range) = (32768 / 8)
      _g_sens = 4096;
    break;

    default:
    break;
  }
  return (rc);
}

byte KX126::get_rawval(unsigned char *data)
{
  byte rc;

  rc = read(KX126_XOUT_L, data, 6);
  if (rc != 0) {
    Serial.println("Can't get KX126 accel value");
  }

  return (rc);
}

byte KX126::get_val(float *data)
{
  byte rc;
  unsigned char val[6];
  signed short acc[3];

  rc = get_rawval(val);
  if (rc != 0) {
    return (rc);
  }

  acc[0] = ((signed short)val[1] << 8) | (val[0]);
  acc[1] = ((signed short)val[3] << 8) | (val[2]);
  acc[2] = ((signed short)val[5] << 8) | (val[4]);

  // Convert LSB to g
  data[0] = (float)acc[0] / _g_sens;
  data[1] = (float)acc[1] / _g_sens;
  data[2] = (float)acc[2] / _g_sens;

  return (rc);  
}

byte KX126::write(uint8_t memory_address, uint8_t *data, uint8_t len)
{
  byte rc;

  Wire.beginTransmission(_device_address);
  Wire.write(memory_address);
  Wire.write(data, len);
  rc = Wire.endTransmission();
  return (rc);
}

byte KX126::read(uint8_t memory_address, uint8_t *data, uint8_t len)
{
  byte rc;
  unsigned char cnt;

  Wire.beginTransmission(_device_address);
  Wire.write(memory_address);
  rc = Wire.endTransmission(false);
  if (rc != 0) {
    return (rc);
  }

  Wire.requestFrom(_device_address, len, true);
  cnt = 0;
  while(Wire.available()) {
    data[cnt] = Wire.read();
    cnt++;
  }

  return (0);
}
