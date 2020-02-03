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

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PLAT_RC_OK (0)
#define PLAT_RC_FAIL (-1)

struct platform
{
	void *plat_data; /* platform private data, used to identify sensor */

	/* Sensor bus write function */
    int (*write)(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size);
	
	/* Sensor bus read function */
    int (*read)(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size);
	/* Delay function */
    int (*delay_ms)(struct platform *plat, uint16_t ms);
	/* Debug print/trace function */
	int (*debug_print)(struct platform *plat, char *str);
};

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H__ */
