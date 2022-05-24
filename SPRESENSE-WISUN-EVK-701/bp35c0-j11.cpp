/********************************************************************************
  bp35c0-j11.cpp
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
*********************************************************************************/
#include <Arduino.h>
#include "bp35c0-j11.h"

unsigned const char uni_req[4] = {0xD0 , 0xEA , 0x83 , 0xFC};
unsigned const char uni_res[4] = {0xD0 , 0xF9 , 0xEE , 0x5D};

unsigned const char ini_data[4] = {0x03 , 0x00 , 0x05 , 0x00};       // エンドデバイス/Sleep 非対応/922.9MHz/20mW出力
unsigned const char pair_id[8] = {0x00 , 0x1D , 0x12 , 0x91 , 0x00 , 0x00 , 0x05 , 0xA7};   // 接続先MACアドレス
unsigned const char mac_adr[16] = {0xFE , 0x80 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x02 , 0x1D , 0x12 , 0x91 , 0x00 , 0x00 , 0x05 , 0xE7}; // 接続先IPv6アドレス
unsigned const char my_port[2] = { 0x01 , 0x23 };     // オープンするUDPポート
unsigned const char dist_port[2] = { 0x0E , 0x1A };   // 送信先UDPポート
unsigned const char password[16] = { '1' , '1' , '1' , '1' , '2', '2' , '2' , '2' , '3' , '3' , '3' , '3' , '4' , '4' , '4' , '4' };    // PANA認証時のパスワード
unsigned const char radiodata[4] = { 'T' , 'E' , 'S' , 'T' };         // 送信データ

CMD_FORMAT cmd_format;

BP35C0J11::BP35C0J11(void)
{
	
}

/********************************************************************************
*   Name     : j11_init
*   Function : initial setting bp35c0-j11
*   input    : -
*   return   : -
*********************************************************************************/
void BP35C0J11::j11_init(void) {

  // configure output D20/D21
  pinMode(PIN_ENABLE, OUTPUT);      
  pinMode(PIN_RESET, OUTPUT);
  digitalWrite(PIN_ENABLE, HIGH);


  delay(1000);

  // Serial port initial 
  Serial2.begin(115200);
  Serial.begin(115200);
  Serial.write("RESET");
  Serial.println("");

  digitalWrite(PIN_RESET, LOW);     // reset
  delay(500);
  digitalWrite(PIN_RESET, HIGH);

}

/********************************************************************************
*   Name     : wait_msg
*   Function : wait for response from bp35c0-j11
*   input    : -
*   return   : TRUE/FALSE
*********************************************************************************/
boolean BP35C0J11::wait_msg(void)
{
  unsigned long start_time;
  unsigned long current_time;
  unsigned char rcvdata[128] = {0} ;
  unsigned char cnt = 0 ;
  start_time = millis();
  while (Serial2.available() == 0)
  {
    current_time = millis();
    if ((current_time - start_time) > TIMEOUT) {
      Serial.println("receive timeout");
      return FALSE;
    }

  }
  while (Serial2.available() > 0 ) {
    delay(5);
    rcvdata[cnt] = Serial2.read();
#ifdef DEBUG
    Serial.print(rcvdata[cnt] , HEX);
#endif
    cnt++;
    if (cnt >= 128) {
      Serial.println("receive data over flow");
      return FALSE;
    }
  }
  if (rcvdata[0] == uni_res[0] && rcvdata[1] == uni_res[1] &&
      rcvdata[2] == uni_res[2] && rcvdata[3] == uni_res[3]) {     // RESPONSE/NORTIFICATION
    switch (rcvdata[4] << 8 | rcvdata[5]) {
      case (NORT_WAKE):

        break;
      case (RES_INI):
        if (rcvdata[12] == 0x01) {
          Serial.println("Init Success");
        } else {
          Serial.println("Init Error");
          return FALSE;
        }
        break;
      case (RES_PANA_SET):
        if (rcvdata[12] == 0x01) {
          Serial.println("PANA Password set Success");
        } else {
          Serial.println("PANA Password set Error");
          return FALSE;
        }
        break;
      case (RES_SCAN):

        break;
      case (NORT_SCAN):
        break;
      case (RES_HAN):
        if (rcvdata[12] == 0x01) {
          Serial.println("HAN Act Success");
        } else {
          Serial.println("HAN Act Error");
          return FALSE;
        }
        break;
      case (RES_PANA):
        if (rcvdata[12] == 0x01) {
          Serial.println("PANA Act Success");
        } else {
          Serial.println("PANA Act Error");
          return FALSE;
        }
        break;
      case (NORT_PANA):
        if (rcvdata[12] == 0x01) {
          Serial.println("PANA Connect Success");
        } else {
          Serial.println("PANA Connecgt Error");
          return FALSE;
        }
        break;
      case (RES_CON_SET):
        if (rcvdata[12] == 0x01) {
          Serial.println("Normal connect mode");
        } else {
          Serial.println("connect mode change error");
          return FALSE;
        }
        break;
      case (RES_PORTOPEN):
        if (rcvdata[12] == 0x01) {
          Serial.println("UDP port open Success");
        } else {
          Serial.println("UDP port open Error");
          return FALSE;
        }
        break;
      case (RES_UDPSEND):
        if (rcvdata[12] == 0x01) {
          Serial.println("UDP send Success");
        } else {
          Serial.println("UDP send Error");
          return FALSE;
        }
        break;
      case (0x2FFF):
        Serial.println("checksum error");
        return FALSE;
        break;
      default:
        Serial.println("uni code error");
        return FALSE;
        break;
    }

  } else {
    Serial.println("recv data error");
    return FALSE;
  }

  return TRUE;
}



/********************************************************************************
*   Name     : cmd_send
*   Function : REQUEST command to bp35c0-j11
*   input    : cmd  - REQUEST command 
*   return   : TRUE/FALSE
*********************************************************************************/
boolean BP35C0J11::cmd_send(unsigned short cmd) {
  unsigned short hdr_chksum = uni_req[0] + uni_req[1] + uni_req[2] + uni_req[3] ;
  unsigned short dat_chksum = 0 ;
  unsigned short msg_length = 0 ;
  unsigned short dat_length = 0 ;
  unsigned short send_dat_size = 0 ;
  unsigned char data[128] = {0};

  unsigned char send_data[128] = {0} ;
  boolean rc = FALSE;
  unsigned char cnt = 0 ;

  switch (cmd) {
    case (CMD_RESET):
      dat_length = 0;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_RESET + msg_length;
      dat_chksum = 0 ;
      msg_create(CMD_RESET , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, (msg_length + CMD_HDR_LEN));
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif

      break;
    case (CMD_INI):
      dat_length = (unsigned short)4;
      msg_length = (unsigned short )( 4 + dat_length);
      hdr_chksum += CMD_INI + msg_length ;
      for (cnt = 0 ; cnt < dat_length ; cnt++ ) {
        data[cnt] = ini_data[cnt] ;
      }
      for (cnt = 0 ; cnt < dat_length ; cnt++) {
        dat_chksum += data[cnt];
      }
      msg_create(CMD_INI , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, (msg_length + CMD_HDR_LEN));
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif
      break;
    case (CMD_PANA_SET):
      dat_length = (unsigned short)16 ;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_PANA_SET + msg_length;
      for (cnt = 0 ; cnt < dat_length ; cnt++ ) {
        data[cnt] = password[cnt] ;
      }
      for (cnt = 0 ; cnt < dat_length ; cnt++) {
        dat_chksum += data[cnt];
      }
      msg_create(CMD_PANA_SET , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, (msg_length + CMD_HDR_LEN));
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif

      break;
    case (CMD_SCAN):
      break;
    case (CMD_HAN):
      dat_length = (unsigned short)8 ;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_HAN + msg_length;
      for (cnt = 0 ; cnt < dat_length ; cnt++ ) {
        data[cnt] = pair_id[cnt] ;
      }
      for (cnt = 0 ; cnt < dat_length ; cnt++) {
        dat_chksum += data[cnt];
      }
      msg_create(CMD_HAN , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, (msg_length + CMD_HDR_LEN));
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif


      break;
    case (CMD_PANA):
      dat_length = 0;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_PANA + msg_length;
      dat_chksum = 0 ;
      msg_create(CMD_PANA , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, msg_length + CMD_HDR_LEN);
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif
      break;
    case (CMD_CON_SET):
      dat_length = 1;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_CON_SET + msg_length;
      data[0] = 0x02 ;
      dat_chksum = data[0] ;
      msg_create(CMD_CON_SET , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, msg_length + CMD_HDR_LEN);
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif

      break;
    case (CMD_PORTOPEN):
      dat_length = 2;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_PORTOPEN + msg_length;
      for (cnt = 0 ; cnt < dat_length ; cnt++ ) {
        data[cnt] = my_port[cnt] ;
      }
      for (cnt = 0 ; cnt < dat_length ; cnt++) {
        dat_chksum += data[cnt];
      }
      msg_create(CMD_PORTOPEN , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, msg_length + CMD_HDR_LEN);
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif
      break;
    case (CMD_UDPSEND):
      send_dat_size = 4 ;
      dat_length = 22 + send_dat_size ;
      msg_length = (unsigned short)(4 + dat_length);
      hdr_chksum += CMD_UDPSEND + msg_length;
      for (cnt = 0 ; cnt < 16 ; cnt++ ) {
        data[cnt] = mac_adr[cnt] ;
      }
      data[16] = my_port[0] ;
      data[17] = my_port[1] ;          // 送信元UDPポート　：0x0123
      data[18] = dist_port[0] ;
      data[19] = dist_port[1] ;        // 送信先UDPポート：0x0E1A
      data[20] = (unsigned char)(send_dat_size >> 8);
      data[21] = (unsigned char)(send_dat_size & 0xFF); // send data length
      for (cnt = 0 ; cnt < send_dat_size ; cnt++) {
        data[22 + cnt] = radiodata[cnt];              // data
      }
      for (cnt = 0 ; cnt < dat_length ; cnt++) {
        dat_chksum += data[cnt];
      }
      msg_create(CMD_UDPSEND , msg_length , hdr_chksum , dat_chksum, data , send_data );
      Serial2.write(send_data, msg_length + CMD_HDR_LEN);
#ifdef DEBUG
      debugmsg( msg_length + CMD_HDR_LEN , send_data);
#endif
      break;
    default:

      break;
  }
}

/********************************************************************************
*   Name     : msg_create
*   Function : create Request command format
*   input    : cmd - Request command
*              msg_length - message data length
*              hdr_chksum - header checksum
               dat_chksum - data checksum
               *pdada     - wireless data
               *psend_data- request command format data
*   return   : -
*********************************************************************************/
void static BP35C0J11::msg_create(unsigned short cmd , unsigned short msg_length , unsigned short hdr_chksum , unsigned short dat_chksum, unsigned char *pdata , unsigned char *psend_data )
{
  unsigned char cnt = 0 ;

  for (cnt = 0 ; cnt < 4 ; cnt++) {
    psend_data[cnt] = uni_req[cnt];
  }
  psend_data[4] = (unsigned char)((cmd & 0xFF00) >> 8);
  psend_data[5] = (unsigned char)(cmd & 0xFF);
  psend_data[6] = (unsigned char)((msg_length & 0xFF00) >> 8);
  psend_data[7] = (unsigned char)(msg_length & 0xFF);
  psend_data[8] = (unsigned char)((hdr_chksum & 0xFF00) >> 8);
  psend_data[9] = (unsigned char)(hdr_chksum & 0xFF);
  psend_data[10] = (unsigned char)((dat_chksum & 0xFF00) >> 8);
  psend_data[11] = (unsigned char)(dat_chksum & 0xFF);

  if (msg_length > 4) {
    for (cnt = 0 ; cnt < msg_length - 4 ; cnt++)
    {
      psend_data[12 + cnt] = pdata[cnt];
    }
  }
}



/********************************************************************************
*   Name     : debugmsg
*   Function : output serial console for debug
*   input    : datalength - output data lengh
               psend_data - output data pointer
*   return   : -
*********************************************************************************/
void BP35C0J11::debugmsg(unsigned short datalength , unsigned char* psend_data) {
  unsigned char cnt = 0 ;

  for ( cnt = 0 ; cnt < datalength ; cnt++) {
    Serial.print(psend_data[cnt] , HEX);
    Serial.print(" ");
  }
  Serial.println("");
}



