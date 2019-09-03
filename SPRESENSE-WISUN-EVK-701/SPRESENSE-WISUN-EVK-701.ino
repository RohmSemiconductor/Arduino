/*
  SPRESENSE-WISUN-EVK-701
 Copyright (c) 2019 ROHM Co.,Ltd.

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
*/
#include "bp35c0-j11.h"


unsigned char state = 0 ;

void setup() {
  boolean rc = FALSE ;
  j11_init();
  rc = wait_msg();
  if(rc == TRUE){
    state = 1 ;           //  hardware reset end 
  }else{
    state = 0 ;
  }
  

}

void loop() {

  unsigned char msg_length = 0 ;
  boolean rc = 0 ;

#ifdef DEBUG  
  Serial.print("State = ");
  Serial.println(state, DEC);
#endif

  delay(500);
  switch (state) {
    case(0):   // need hardware reset 
      rc = cmd_send(CMD_RESET);
      rc = wait_msg();
      if(rc == TRUE){
        state = 1 ;
      }
    break;
    case(1):  //  init state 
      rc = cmd_send(CMD_INI);
      rc = wait_msg();
      if(rc == TRUE){
        state = 2;
      }
      break;
    case(2): // HAN PANA setting
      rc = cmd_send(CMD_PANA_SET);
      rc = wait_msg();
      if(rc == TRUE){
        state = 4;
      }
      break;
    case(3): // active scan
      rc = cmd_send(CMD_SCAN);
      rc = wait_msg();
      if(rc == TRUE){
        rc = wait_msg();
        if(rc == TRUE){
          state = 4;
        }
      }
      break;
    case(4): //  HAN act
      rc = cmd_send(CMD_HAN);
      rc = wait_msg();
      if(rc == TRUE){
        state = 5;
      }
      break;
    case(5): // HAN PANA act
      rc = cmd_send(CMD_PANA);
      rc = wait_msg();
      if(rc == TRUE){
        rc = wait_msg();
        if(rc == TRUE){
            state = 7;
        }
      }
      break;
    case(6): // rcv mode change
      rc = cmd_send(CMD_CON_SET);
      rc = wait_msg();
      if(rc == TRUE){
        state = 7;
      }
      break;
    case(7): // my_port open
      rc = cmd_send(CMD_PORTOPEN);
      rc = wait_msg();
      if(rc == TRUE){
        state = 8;
      }
      break;
    case(8): // UDP send
      rc = cmd_send(CMD_UDPSEND);
      rc = wait_msg();
      if(rc == TRUE){
        delay(5000);
      }
      break;
    default:  // error 
        state = 0 ;
      break;

  }




}

