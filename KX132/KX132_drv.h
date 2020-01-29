/*
The MIT License (MIT)
Copyright (c) 2020 ROHM Co.,Ltd.

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

#ifndef _KX132_DRV_H_
#define _KX132_DRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#define KX132_DEVICE_ADDRESS_1E   (0x1E)    // 7bit Address
#define KX132_DEVICE_ADDRESS_1F   (0x1F)    // 7bit Address

/* function return codes */
#define RC_OK 0
#define RC_FAIL 1

/* Platform functions used by KX132 driver */
struct platform_functions
{
    uint8_t (*i2c_write)(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);
    uint8_t (*i2c_read)(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size);
    uint8_t (*delay_ms)(uint16_t ms);
	uint8_t (*debug_println)(char *str);
};

/* Set platform functions to driver */
uint8_t KX132_set_platform_functions(struct platform_functions *functions);

/* KX132 driver functions */
uint8_t KX132_init(uint8_t sad);
uint8_t KX132_set_lowpower_config();
uint8_t KX132_get_raw_xyz(uint8_t *data);
uint8_t KX132_get_xyz(float *data);
uint8_t KX132_debug_dump_regs();

#ifdef __cplusplus
}
#endif

#endif // _KX132_DRV_H_
