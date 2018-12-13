/*****************************************************************************
  KX126.h

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
#ifndef _KX126_H_
#define _KX126_H_

#define KX126_DEVICE_ADDRESS_1E   (0x1E)    // 7bit Address
#define KX126_DEVICE_ADDRESS_1F   (0x1F)    // 7bit Address
#define KX126_WAI_VAL             (0x38)

#define KX126_XOUT_L              (0x08)
#define KX126_WHO_AM_I            (0x11)
#define KX126_CNTL1               (0x1A)
#define KX126_CNTL2               (0x1B)
#define KX126_ODCNTL              (0x1F)

#define KX126_CNTL1_TPE           (1 << 0)
#define KX126_CNTL1_PDE           (1 << 1)
#define KX126_CNTL1_TDTE          (1 << 2)
#define KX126_CNTL1_GSELMASK      (0x18)
#define KX126_CNTL1_GSEL_2G       (0x00)
#define KX126_CNTL1_GSEL_4G       (0x08)
#define KX126_CNTL1_GSEL_8G       (0x10)
#define KX126_CNTL1_DRDYE         (1 << 5)
#define KX126_CNTL1_RES           (1 << 6)
#define KX126_CNTL1_PC1           (1 << 7)

#define KX126_CNTL2_SRST          (1 << 7)

#define KX126_ODCNTL_OSA_50HZ     (2)
#define KX126_ODCNTL_LPRO         (1 << 6)
#define KX126_IIR_BYPASS          (1 << 7)

#define KX126_CNTL1_VAL           (KX126_CNTL1_RES | KX126_CNTL1_GSEL_2G)
#define KX126_ODCNTL_VAL          (KX126_ODCNTL_OSA_50HZ)


class KX126
{
  public:
    KX126(uint8_t slave_address);
    ~KX126();
    byte init(void);
    byte get_rawval(unsigned char *data);
    byte get_val(float *data);
    byte write(uint8_t memory_address, uint8_t *data, uint8_t len);
    byte read(uint8_t memory_address, uint8_t *data, uint8_t len);
  private:
    uint8_t _device_address;
    unsigned short _g_sens;
};

#endif // _KX126_H_
