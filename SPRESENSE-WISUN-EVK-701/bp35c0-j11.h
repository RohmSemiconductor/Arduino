/*
  bp35c0-j11.h
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
#ifndef _BP35C0J11_H_
#define _BP35C0J11_H_

#define DEBUG


#define CMD_HDR_LEN  ((unsigned char)8)
#define UNI_CODE_LEN ((unsigned char)4)

#define CMD_RESET    (0x00D9)
#define CMD_INI      (0x005F)
#define CMD_HAN      (0x000A)
#define CMD_PANA     (0x003A)
#define CMD_PANA_SET (0x002C)
#define CMD_CON_SET  (0x0025)
#define CMD_UDPSEND  (0x0008)
#define CMD_SCAN     (0x0051)
#define CMD_PORTOPEN (0x0005)

#define NORT_WAKE    (0x6019)
#define RES_INI      (0x205F)
#define RES_HAN      (0x200A)
#define RES_PANA     (0x203A)
#define RES_PANA_SET (0x202C)
#define RES_CON_SET  (0x2025)
#define RES_UDPSEND  (0x2008)
#define RES_SCAN     (0x2051)
#define NORT_SCAN    (0x4051)
#define RES_PORTOPEN (0x2005)
#define NORT_PANA    (0x6028)

#define TIMEOUT      ((unsigned short)10000)

#define PIN_ENABLE  (PIN_D20)    // level shifter enable pin
#define PIN_RESET   (PIN_D21)    // wisun module reset pin

#define TRUE 1
#define FALSE 0

typedef struct {
  unsigned char uni_code[4];
  unsigned char cmd_code[2];
  unsigned char msg_len[2];
  unsigned char hdr_chksum[2];
  unsigned char dat_chksum[2];
  unsigned char data[128];
}CMD_FORMAT;

void j11_init(void);
boolean wait_msg(void);
boolean cmd_send(unsigned short cmd);
void static msg_create(unsigned short cmd , unsigned short msg_length ,unsigned short hdr_chksum , unsigned short dat_chksum, unsigned char *pdata , unsigned char *psend_data );
void static debugmsg(unsigned short datalength , unsigned char *psend_data);

#endif    //_BP35C0J11_H_

