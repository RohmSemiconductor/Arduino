/*****************************************************************************
  Sensors-Add-on-Demo.ino
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
#include <Wire.h>
#include <KX122.h>
#include <KX126.h>
#include <BM1422AGMV.h>
#include <BM1383AGLV.h>

KX122 kx122(KX122_DEVICE_ADDRESS_1F);
KX126 kx126(KX126_DEVICE_ADDRESS_1F);
BM1422AGMV bm1422agmv(BM1422AGMV_DEVICE_ADDRESS_0F);
BM1383AGLV bm1383aglv;
bool KX122_found = false;
bool KX126_found = false;

void setup() {
  byte rc;


  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  rc = kx122.init();
  if (rc != 0) {
    Serial.flush();
  }else{
    KX122_found = true;
  }

  rc = kx126.init();
  if (rc != 0) {
    Serial.flush();
  }else{
    KX126_found = true;
  }

  if(!KX122_found && !KX126_found){
    Serial.println(F("KX122/KX126 initialization failed"));
  }
  
  rc = bm1422agmv.init();
  if (rc != 0) {
    Serial.println(F("BM1422AGMV initialization failed"));
    Serial.flush();
  }

  rc = bm1383aglv.init();
  if (rc != 0) {
    Serial.println("BM1383AGLV initialization failed");
    Serial.flush();
  }

}

void loop() {
  byte rc;
  float acc[3], mag[3], press = 0, temp = 0;

  if(KX122_found){
    rc = kx122.get_val(acc);
    if (rc == 0) {
      Serial.write("KX122 (X) = ");
      Serial.print(acc[0]);
      Serial.println(" [g]");
      Serial.write("KX122 (Y) = ");
      Serial.print(acc[1]);
      Serial.println(" [g]");
      Serial.write("KX122 (Z) = ");
      Serial.print(acc[2]);
      Serial.println(" [g]");
    }
  }

  if(KX126_found){
    rc = kx126.get_val(acc);
    if (rc == 0) {
      Serial.write("KX126 (X) = ");
      Serial.print(acc[0]);
      Serial.println(" [g]");
      Serial.write("KX126 (Y) = ");
      Serial.print(acc[1]);
      Serial.println(" [g]");
      Serial.write("KX126 (Z) = ");
      Serial.print(acc[2]);
      Serial.println(" [g]");
    }
  }

  rc = bm1422agmv.get_val(mag);

  if (rc == 0) {
    Serial.print("BM1422AGMV XDATA=");
    Serial.print(mag[0], 3);
    Serial.println("[uT]");
    Serial.print("BM1422AGMV YDATA=");
    Serial.print(mag[1], 3);
    Serial.println("[uT]");
    Serial.print("BM1422AGMV ZDATA=");
    Serial.print(mag[2], 3);
    Serial.println("[uT]");
  }
  
  rc = bm1383aglv.get_val(&press, &temp);
  if (rc == 0) {
    Serial.print("BM1383AGLV (PRESS) = ");
    Serial.print(press);
    Serial.println(" [hPa]");
    Serial.print("BM1383AGLV (TEMP) =  ");
    Serial.print(temp);
    Serial.println(" [degrees Celsius]");    
    Serial.println();
  }

  delay(500);

}
