/*****************************************************************************
  BH1749NUC.ino

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
#include "BH1749NUC.h"

BH1749NUC bh1749nuc(BH1749NUC_DEVICE_ADDRESS_39);

void setup() {
  byte rc;

  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  rc = bh1749nuc.init();
  if (rc != 0) {
    Serial.println("BH1749NUC initialization failed");
    Serial.flush();
  }
}

void loop() {
  byte rc;
  unsigned short color[5];

  rc = bh1749nuc.get_val(color);
  if (rc == 0) {
    Serial.write("BH1749NUC (RED)    = ");
    Serial.println(color[0]);
    Serial.write("BH1749NUC (GREEN)  = ");
    Serial.println(color[1]);
    Serial.write("BH1749NUC (BLUE)   = ");
    Serial.println(color[2]);
    Serial.write("BH1749NUC (IR)     = ");
    Serial.println(color[3]);
    Serial.write("BH1749NUC (GREEN2) = ");
    Serial.println(color[4]);
    Serial.println();
  }

  delay(WAIT_TMT2_MAX);

}
