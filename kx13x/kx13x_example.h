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

#ifndef __KX13X_EXAMPLE_H__
#define __KX13X_EXAMPLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* forward declare */
struct kx13x;
struct platform;

#define KX13X_EXAMPLE_DRDY_POLL 1
#define KX13X_EXAMPLE_DRDY_INTERRUPT 2
#define KX13X_EXAMPLE_WU_BTS_INTERRUPT 3
#define KX13X_EXAMPLE_ADP_DATA 4

/* writes example config to sensor, sensor is not set to operation mode */
struct kx13x_cfg *kx13x_example_update_config(struct kx13x *dev, uint8_t example);

int kx13x_example_handle_interrupt(struct kx13x *dev);

int kx13x_example_poll_interrupt(struct kx13x *dev);

#ifdef __cplusplus
}
#endif

#endif /* __KX13X_EXAMPLE_H__ */

