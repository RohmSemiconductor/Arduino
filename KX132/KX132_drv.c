/*
The MIT License (MIT)
Copyright (c) 2019 Kionix Inc.

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
#include <stdio.h> 
#include <stddef.h>
#include <stdint.h>
#include "KX132_drv.h"
#include "kx132_registers.h"

/* Driver data struct */
struct KX132_drv {
	uint8_t sad;
	uint16_t g_sens;
};

struct KX132_drv drv_data;

/* Platform functions passed to driver */
struct platform_functions *platform_funcs;

/* Set plafrom functions */
uint8_t KX132_set_platform_functions(struct platform_functions *functions)
{
	if (functions == NULL ||
	    functions->i2c_read == NULL ||
		functions->i2c_write == NULL) {
		return RC_FAIL;
	}

	platform_funcs = functions;

	return RC_OK;
}

/* Wrapper to platform functions */
uint8_t KX132_plat_func_i2c_read(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_read is mandatory */

	if (platform_funcs && platform_funcs->i2c_read) {
		rc = platform_funcs->i2c_read(sad, reg, data, size);
	}

    return rc;
}

uint8_t KX132_plat_func_i2c_write(uint8_t sad, uint8_t reg, uint8_t *data, uint8_t size)
{
    uint8_t rc = RC_FAIL; /* i2c_write is mandatory */

	if (platform_funcs && platform_funcs->i2c_write) {
		rc = platform_funcs->i2c_write(sad, reg, data, size);
	}

    return rc;
}

uint8_t KX132_plat_func_delay_ms(uint16_t ms)
{
    uint8_t rc = RC_OK; /* delay_ms is optional */

	if (platform_funcs && platform_funcs->delay_ms) {
		rc = platform_funcs->delay_ms(ms);
	}

    return rc;
}

uint8_t KX132_plat_func_debug_print_line(char *str)
{
    uint8_t rc = RC_OK; /* debug_println is optional */

	if (platform_funcs && platform_funcs->debug_println && str != NULL) {
		rc = platform_funcs->debug_println(str);
	}

    return rc;
}

/* KX132 reg read/write and reg bits handling */
uint8_t KX132_reg_read(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KX132_plat_func_i2c_read(drv_data.sad, reg, data, size);
}

uint8_t KX132_reg_write(uint8_t reg, uint8_t *data, uint8_t size)
{
    return KX132_plat_func_i2c_write(drv_data.sad, reg, data, size);
}

uint8_t KX132_reg_set_bit_pattern(uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
	uint8_t rc;
	uint8_t reg_val;

	rc = KX132_reg_read(reg, &reg_val, sizeof(reg_val));
	if (rc != RC_OK) {
		return rc;
	}

	reg_val &= ~mask;
	reg_val |= bit_pattern;

    rc = KX132_reg_write(reg, &reg_val, sizeof(reg_val));
	if (rc != RC_OK) {
		return rc;
	}

	return RC_OK;
}

uint8_t KX132_reg_set_bit(uint8_t reg, uint8_t bits)
{
	return KX132_reg_set_bit_pattern(reg, bits, 0x00);
}

uint8_t KX132_reg_reset_bit(uint8_t reg, uint8_t bits)
{
	return KX132_reg_set_bit_pattern(reg, 0x00, bits);
}

/* Debug prints */
uint8_t KX132_debug_print_line(char *str)
{
    return KX132_plat_func_debug_print_line(str);
}

void KX132_debug_print_reg_and_val(uint8_t reg, uint8_t val)
{
	char buffer[40];
	int n;
	n=sprintf(buffer, "reg 0x%x val 0x%x",reg,val);
	KX132_debug_print_line(buffer);
}

void KX132_debug_dump_reg(uint8_t reg)
{
	uint8_t rc;
	uint8_t reg_val;

	rc = KX132_reg_read(reg, &reg_val, sizeof(reg_val));
	if (rc != RC_OK) {
		return;
	}

	KX132_debug_print_reg_and_val(reg, reg_val);
}

/* KX132 delay */
void KX132_delay_ms(uint16_t ms)
{
	KX132_plat_func_delay_ms(ms);
}

/* KX132 drv_data code  */
uint8_t KX132_set_CNTL1_PC1_on()
{
	uint8_t rc;
    rc = KX132_reg_set_bit(KX132_CNTL1, KX132_CNTL1_PC1);
	return rc;
}

uint8_t KX132_set_CNTL1_PC1_off()
{
	uint8_t rc;
    rc = KX132_reg_reset_bit(KX132_CNTL1, KX132_CNTL1_PC1);
	return rc;
}

uint8_t KX132_set_odr(uint8_t ord)
{
	uint8_t rc;
	rc = KX132_reg_set_bit_pattern(KX132_ODCNTL, ord, KX132_ODCNTL_OSA_MASK);
	return rc;
}

uint8_t KX132_set_grange(uint8_t grange)
{
	uint8_t rc;

	rc = KX132_reg_set_bit_pattern(KX132_CNTL1, grange, KX132_CNTL1_GSEL_MASK);	

    if (rc == RC_OK) {
		grange &= KX132_CNTL1_GSEL_MASK;
		switch(grange) {
			case KX132_CNTL1_GSEL_2G  : drv_data.g_sens = 16384; break;
			case KX132_CNTL1_GSEL_4G  : drv_data.g_sens = 8192;  break;
			case KX132_CNTL1_GSEL_8G  : drv_data.g_sens = 4096;  break;
			case KX132_CNTL1_GSEL_16G : drv_data.g_sens = 2048;  break;
			default: break;
		}
	}

	return rc;
}

uint8_t KX132_force_sleep_mode()
{
	uint8_t rc;
	uint8_t cntl5;
	uint8_t status;

	/* force sleep mode */
	rc = KX132_reg_set_bit(KX132_CNTL5, KX132_CNTL5_MAN_SLEEP);
	if (rc != RC_OK) {
		return rc;
	}

    /* wait until sleep setup bit released */
	do{
		rc = KX132_reg_read(KX132_CNTL5, &cntl5, sizeof(cntl5));
		if (rc != RC_OK) {
			return rc;
		}

	} while (cntl5 & KX132_CNTL5_MAN_SLEEP);

	/* wait until sleep mode valid */
	do{
		rc = KX132_reg_read(KX132_STATUS_REG, &status, sizeof(status));
		if (rc != RC_OK) {
			return rc;
		}

	} while (status & KX132_STATUS_REG_WAKE);

	return RC_OK;
}

uint8_t KX132_sensor_soft_reset()
{
	uint8_t rc;

	rc = KX132_reg_set_bit(KX132_CNTL2, KX132_CNTL2_SRST);
	if (rc != RC_OK) {
		return rc;
	}

	KX132_delay_ms(500);

	return RC_OK;
}

uint8_t KX132_set_lowpower_config()
{
	uint8_t rc;
	uint8_t grange = KX132_CNTL1_GSEL_2G;
	uint8_t odr = KX132_ODCNTL_OSA_6P25;
	uint8_t average = KX132_LP_CNTL1_AVC_NO_AVG;

	/* Sensor must be in standby mode before configs are changed */
	rc = KX132_set_CNTL1_PC1_off();
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_set_CNTL1_PC1_off fail");
		return (rc);
	}

	/* set sensor odr */
	rc = KX132_set_odr(odr);
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_set_odr fail");
		return (rc);
	}

	/* set sensor grange */
	rc = KX132_set_grange(grange);
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_set_grange fail");
		return (rc);
	}

	/* enable low current mode */
	KX132_reg_reset_bit(KX132_CNTL1, KX132_CNTL1_RES);
	/* define averaging value */
    KX132_reg_set_bit_pattern(KX132_LP_CNTL1, average, KX132_LP_CNTL1_AVC_MASK);
 
    /* force sleep mode */
	KX132_force_sleep_mode();
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_force_sleep_mode fail");
		return (rc);
	}

	/* digital power shut-off enabled */
	/* Note: This setting (LPSTPSEL = 1) cannot be used in Low Power if any of the */
	/* following digital engines is enabled: Advanced Data Path, , Tap/Double-Tap, */
	/* Freefall, Tilt, or Pedometer. This setting can be used with Wake-up and     */
	/* Back-to-Sleep engines. This setting has no effect in High-performance mode. */
	KX132_reg_set_bit(KX132_LP_CNTL2, KX132_LP_CNTL2_LPSTPSEL);

    /* enable low power mode */
	rc = KX132_set_CNTL1_PC1_on();
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_set_CNTL1_PC1_on fail");
		return (rc);
	}

	return RC_OK;
}

uint8_t KX132_init(uint8_t sad)
{
	uint8_t rc;
	uint8_t reg;

	/* platform_funcs needs to be set, or overwrite local read/write/print functions */
	if (platform_funcs == NULL) {
		return RC_FAIL;
	}

	drv_data.sad = sad;
	drv_data.g_sens = 16384;

	rc = KX132_reg_read(KX132_WHO_AM_I, &reg, sizeof(reg));
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_reg_read WHO_AM_I fail");
		return (rc);
	}

	/* verify that we got correct wai value */
	if (reg != KX132_WHO_AM_I_WAI_ID) {
		KX132_debug_print_line("Incorrect WAI");
		return RC_FAIL;
	}

	/* do sensor soft reset */
	rc = KX132_sensor_soft_reset();
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_sensor_soft_reset fail");
		return (rc);
	}

	return RC_OK;
}

uint8_t KX132_get_raw_xyz(uint8_t *xyz)
{
	uint8_t rc;

	rc = KX132_reg_read(KX132_XOUT_L, xyz, 6);
	if (rc != RC_OK) {
		KX132_debug_print_line("KX132_get_rawval fail");
		return rc;
	}

	return RC_OK;
}

uint8_t KX132_get_xyz(float *xyz)
{
	uint8_t rc;
	uint8_t raw_xyz[6] = {0};
	int16_t acc[3];

	rc = KX132_get_raw_xyz(raw_xyz);
	if (rc != RC_OK) {
		return (rc);
	}

	acc[0] = ((signed short)raw_xyz[1] << 8) | (raw_xyz[0]);
	acc[1] = ((signed short)raw_xyz[3] << 8) | (raw_xyz[2]);
	acc[2] = ((signed short)raw_xyz[5] << 8) | (raw_xyz[4]);

	/* Convert LSB to g */
	xyz[0] = (float)acc[0] / drv_data.g_sens;
	xyz[1] = (float)acc[1] / drv_data.g_sens;
	xyz[2] = (float)acc[2] / drv_data.g_sens;

	return RC_OK;  
}

uint8_t KX132_debug_dump_regs()
{
	uint8_t dump_regs[] = {
		KX132_STATUS_REG,
		KX132_CNTL1,
		KX132_CNTL5,
		KX132_ODCNTL,
		KX132_LP_CNTL1,
		KX132_LP_CNTL2
	};

	uint8_t i = 0;
	uint8_t n = sizeof(dump_regs)/sizeof(dump_regs[0]);

	KX132_debug_print_line("KX132_debug_dump_regs :");

	for(i=0; i < n ; i++) {
		KX132_debug_dump_reg(dump_regs[i]);
	}

	return RC_OK;  
}

