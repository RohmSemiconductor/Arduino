/*****************************************************************************
  MK71251.cpp

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

#include "arduino.h"
#include "MK71251.h"


MK71251::MK71251(void)
{
  
}

byte MK71251::init(void)
{	

    // configure Output for GPIO3 (High: HCI mode, Low: AT command mode) 
    pinMode(PIN_D21, OUTPUT);
    digitalWrite(PIN_D21, LOW);
  
	Serial2.begin(57600);
  
  printf("MK71251-02: waiting for CTS:LOW...\n");
   
	while(1){
		int cts = digitalRead(PIN_D27);
    if(!cts) break;
	}

  printf("MK71251-02: CTS:LOW read succesfully\n");
 
	Serial2.write("ATD\r\n");

  printf("MK71251-02: waiting for connection...\n");
	
	while(1){
		int ret = waitConnect();
    if(ret) break;
	}
	
	printf("MK71251-02: connected succesfully\n");
	
	return(0);
}

byte MK71251::write(unsigned char *data)
{
  int rc;
	rc = Serial2.write(*data);
	if(rc != 0){
    return(0);
   }
  else{
    return(-1);
  }
}

byte MK71251::read(unsigned char *data)
{
  char c;
  if((c = Serial2.read()) && c != 255){
    *data = c;
    return(0);
  }
  else{
	  return(-1);
  }
}

int MK71251::waitConnect(void)
{
  char c = 0;
  char ret[128];
  int n;

  for(n = 0; n < 128 && c != '\n';)
  {
    c = Serial2.read();
    if (c != 0 && c != 255){
      ret[n] = c;
      n++;
    }
  }
  ret[n-2] = '\0';
  int cmp = strcmp(ret, "CONNECT");
  return cmp == 0 ? 1 : 0;
}

