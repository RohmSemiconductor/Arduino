/*****************************************************************************
  BM1422AGMV.ino

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
#include <BM1422AGMV.h>

BM1422 bm1422(BM1422_DEVICE_ADDRESS_0F);

void setup() {
  byte rc;
  Serial.begin(115200);
  Serial.println("Rohm BM1422AGMV Magnet Sensor sample");
  Wire.begin();
  rc = bm1422.init();
}

void loop() {
  byte rc;
  float mag[3];
  rc = bm1422.get_val(mag);

  if (rc == 0) {
    Serial.println("BM1422 XDATA=");
    Serial.print(mag[0], 3);
    Serial.println("[uT]");
    Serial.println("BM1422 YDATA=");
    Serial.print(mag[1], 3);
    Serial.println("[uT]");
    Serial.println("BM1422 ZDATA=");
    Serial.print(mag[2], 3);
    Serial.println("[uT]");
    Serial.println();    
  }

  delay(500);
}
