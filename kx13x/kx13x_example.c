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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "platform.h"
#include "kx13x.h"
#include "kx13x_example.h"

#define UNUSED_VAR(a) (void)a

/* Sensor main config */
struct kx13x_cfg main_cfg;

/* Sensor feature configs */
struct kx13x_accel_cfg accel;
struct kx13x_wu_bts_cfg wu_bts_cfg;
struct kx13x_wu_cfg wu_cfg;
struct kx13x_wu_cfg bts_cfg;
struct kx13x_adp_cfg adp_cfg;
struct kx13x_interrupt_cfg int1;
struct kx13x_interrupt_cfg int2;

/* KX13X_EXAMPLE_DRDY_POLL */
static struct kx13x_cfg *kx13x_ex_get_drdy_poll_cfg(struct kx13x *dev)
{
	/* Fill accel */
	accel.perf_mode = KX13X_PERF_MODE_HIGH_RES;
	if (dev->granges & KX13X_GRANGE_64G) {
		// kx134: 8,16,32,64
		accel.grange = KX13X_GRANGE_8G;
	} else {
		// kx132: 2,4,8,16
		accel.grange = KX13X_GRANGE_2G;
	}

	accel.odr = KX13X_ODR_3P125HZ;
	accel.drdy_enable = KX13X_ENABLED;
	accel.filter = KX13X_BYPASS_ODR_9;
	accel.avc = KX13X_AVG_4_SAMPLE;

	/* Add all configs to main config */
	main_cfg.oper_mode = KX13X_OPER_MODE_STANDBY;
	main_cfg.accel = &accel;
	main_cfg.wu_bts = NULL;
	main_cfg.adp = NULL;
	main_cfg.int1 = NULL;
	main_cfg.int2 = NULL;

	return &main_cfg;
}

/* KX13X_EXAMPLE_DRDY_INTERRUPT */
static struct kx13x_cfg *kx13x_ex_get_drdy_interrupt_cfg(struct kx13x *dev)
{
	/* Fill accel */
	accel.perf_mode = KX13X_PERF_MODE_HIGH_RES;
	if (dev->granges & KX13X_GRANGE_64G) {
		// kx134: 8,16,32,64
		accel.grange = KX13X_GRANGE_8G;
	} else {
		// kx132: 2,4,8,16
		accel.grange = KX13X_GRANGE_2G;
	}

	accel.odr = KX13X_ODR_3P125HZ;
	accel.drdy_enable = KX13X_ENABLED;
	accel.filter = KX13X_BYPASS_ODR_9;
	accel.avc = KX13X_AVG_4_SAMPLE;

	/* Fill interrupt pin1 config */
	int1.enable = KX13X_ENABLED;
	int1.routing = KX13X_INT_ROUTE_DRDY;
	int1.level = KX13X_INT_LEVEL_HIGH;
	int1.ctrl = KX13X_INT_CTRL_PULSE_50US_10US;
	
	/* Add all configs to main config */
	main_cfg.oper_mode = KX13X_OPER_MODE_STANDBY;
	main_cfg.accel = &accel;
	main_cfg.wu_bts = NULL;
	main_cfg.adp = NULL;
	main_cfg.int1 = &int1;
	main_cfg.int2 = NULL;

	return &main_cfg;
}

/* KX13X_EXAMPLE_WU_BTS_INTERRUPT */
static struct kx13x_cfg *kx13x_ex_get_wu_bts_interrupt_cfg(struct kx13x *dev)
{
	UNUSED_VAR(dev);

	/* Set wake-up and back to sleep cfg */
	wu_cfg.threshold = 20; 		/* 3.9mg*value */
	wu_cfg.counter = 2; 		/* 1/wu_odr*value */
	wu_cfg.odr = KX13X_WU_12P5HZ;
	wu_cfg.enable = KX13X_ENABLED;
	wu_bts_cfg.wu = &wu_cfg;

	bts_cfg.threshold = 20;		/* 3.9mg*value */
	bts_cfg.counter = 2; 		/* 1/bts_odr*value */
	bts_cfg.odr = KX13X_WU_12P5HZ;
	bts_cfg.enable = KX13X_ENABLED;
	wu_bts_cfg.bts = &bts_cfg;

	/* set wu/bts common config */
	wu_bts_cfg.mode_bits = KX13X_WU_MODES_PR_STANDARD|
							KX13X_WU_MODES_TH_RELATIVE|
							KX13X_WU_MODES_C_RESET;

	wu_bts_cfg.axes_bits = KX13X_WU_AXES_AOI_OR |
							KX13X_WU_AXES_XNWUE |
							KX13X_WU_AXES_XPWUE |
							KX13X_WU_AXES_YNWUE |
							KX13X_WU_AXES_YPWUE |
							KX13X_WU_AXES_ZNWUE |
							KX13X_WU_AXES_ZPWUE;

	/* Route wu/bts to int2 pin */
	int2.enable = KX13X_ENABLED;
	int2.routing = KX13X_INT_ROUTE_WUF | KX13X_INT_ROUTE_BTS;
	int2.level = KX13X_INT_LEVEL_HIGH;
	int2.ctrl = KX13X_INT_CTRL_LATCH;

	/* Add all configs to main config */
	main_cfg.oper_mode = KX13X_OPER_MODE_STANDBY;
	main_cfg.accel = NULL;
	main_cfg.wu_bts = &wu_bts_cfg;
	main_cfg.adp = NULL;
	main_cfg.int1 = NULL;
	main_cfg.int2 = &int2;

	return &main_cfg;
}

/* KX13X_EXAMPLE_ADP_DATA */
static struct kx13x_cfg *kx13x_ex_get_adp_data_cfg(struct kx13x *dev)
{
	UNUSED_VAR(dev);

	/* Fill accel */
	accel.perf_mode = KX13X_PERF_MODE_HIGH_RES;
	if (dev->granges & KX13X_GRANGE_64G) {
		// kx134: 8,16,32,64
		accel.grange = KX13X_GRANGE_8G;
	} else {
		// kx132: 2,4,8,16
		accel.grange = KX13X_GRANGE_2G;
	}

	accel.odr = KX13X_ODR_100HZ;
	accel.drdy_enable = KX13X_ENABLED;
	accel.filter = KX13X_BYPASS_ODR_2;
	accel.avc = KX13X_AVG_2_SAMPLE;

	/* Fill ADP engine config */
	adp_cfg.filter1 = KX13X_ADP_FILTER1_LP_ODR_4;
	adp_cfg.filter2 = KX13X_ADP_FILTER2_HP_ODR_8;
	adp_cfg.adp_odr = KX13X_ODR_100HZ;
	adp_cfg.rms_avg = KX13X_ADP_RMS_AVC_64_SAMPLE_AVG;
	adp_cfg.adp_enabled = KX13X_ENABLED;

	/* Add all configs to main config */
	main_cfg.oper_mode = KX13X_OPER_MODE_STANDBY;
	main_cfg.accel = &accel;
	main_cfg.wu_bts = NULL;
	main_cfg.adp = &adp_cfg;
	main_cfg.int1 = NULL;
	main_cfg.int2 = NULL;

  return &main_cfg;
}

/* writes new config to sensor, does not set sensor to oper mode*/
struct kx13x_cfg *kx13x_example_update_config(struct kx13x *dev, uint8_t example)
{
	struct kx13x_cfg *cfg;
	int rc;
	
	/* clear previous config */
	rc = kx13x_reset(dev);
	if (rc != KX13X_RC_OK) {
		return NULL;
	}
	
	/* Dump registers after sensor reset */
	rc = kx13x_debug_dump_regs(dev);
	if (rc != KX13X_RC_OK) {
		return NULL;
	}

	switch (example) {
		case KX13X_EXAMPLE_DRDY_POLL:
			if (dev->plat->debug_print) {
				dev->plat->debug_print(dev->plat,"KX13X_EXAMPLE_DRDY_POLL\n");
			}
			cfg = kx13x_ex_get_drdy_poll_cfg(dev);
			break;
		case KX13X_EXAMPLE_DRDY_INTERRUPT:
			if (dev->plat->debug_print) {
				dev->plat->debug_print(dev->plat,"KX13X_EXAMPLE_DRDY_INTERRUPT\n");
			}
			cfg = kx13x_ex_get_drdy_interrupt_cfg(dev);
			break;
		case KX13X_EXAMPLE_WU_BTS_INTERRUPT:
			if (dev->plat->debug_print) {
				dev->plat->debug_print(dev->plat,"KX13X_EXAMPLE_WU_BTS_INTERRUPT\n");
			}
			cfg = kx13x_ex_get_wu_bts_interrupt_cfg(dev);
			break;
		case KX13X_EXAMPLE_ADP_DATA:
			if (dev->plat->debug_print) {
				dev->plat->debug_print(dev->plat,"KX13X_EXAMPLE_ADP_DATA\n");
			}
			cfg = kx13x_ex_get_adp_data_cfg(dev);
			break;
		default:
			return NULL;
			break;
	}
	
	rc = kx13x_set_config(dev, cfg);
	if (rc != KX13X_RC_OK) {
		return NULL;
	}

	/* Dump registers after config is written to sensor */
	rc = kx13x_debug_dump_regs(dev);
	if (rc != KX13X_RC_OK) {
		return NULL;
	}

	return cfg;
}

static int kx13x_example_read_and_print_data(struct kx13x *dev)
{
	int rc;
	float xyz[3] = {0.0F};
	int xyz_mg[3] = {0};
	int adp_xyz_mg[3] = {0};
	char* sensor_name;

	sensor_name = kx13x_get_name(dev);
	if (sensor_name == NULL) {
		return KX13X_RC_ERR;
	}

	/* get accel data */ 
	rc = kx13x_get_accel_data(dev, xyz);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* g to mg */
	xyz_mg[0] =	xyz[0] * 1000;
	xyz_mg[1] =	xyz[1] * 1000;
	xyz_mg[2] =	xyz[2] * 1000;

	if (main_cfg.adp) {
		/* get adp data */
		rc = kx13x_get_adp_data(dev, xyz);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
		/* g to mg */
		adp_xyz_mg[0] =	xyz[0] * 1000;
		adp_xyz_mg[1] =	xyz[1] * 1000;
		adp_xyz_mg[2] =	xyz[2] * 1000;
	}

	/* print data */
	if (dev->plat->debug_print) {
		char buffer[120];
		if (main_cfg.adp) {
			char format[] = "%s %d , %d , %d , %d , %d , %d \n";
			(void)sprintf(buffer, format, "accel xyz [mg], adp xyz[mg] :", xyz_mg[0], xyz_mg[1], xyz_mg[2], adp_xyz_mg[0], adp_xyz_mg[1], adp_xyz_mg[2]);
			dev->plat->debug_print(dev->plat, buffer);
		} else {
			char format[] = "%s %d , %d , %d \n";
			(void)sprintf(buffer, format, "accel xyz [mg] :", xyz_mg[0], xyz_mg[1], xyz_mg[2]);
			dev->plat->debug_print(dev->plat, buffer);
		}
	}

	return KX13X_RC_OK;
}

static int kx13x_example_report_ins_status(struct kx13x *dev)
{
	int rc;
	uint8_t ins123[3];
	uint8_t release_int = 0;
	char* sensor_name;

	sensor_name = kx13x_get_name(dev);
	if (sensor_name == NULL) {
		return KX13X_RC_ERR;
	}

	rc = kx13x_get_int_ins123(dev, ins123);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

#define INS1 0
#define INS2 1
#define INS3 2
	if (ins123[INS2] & KX13X_INT_INS2_DRDY) {
		(void)kx13x_example_read_and_print_data(dev);
	}

	if (ins123[INS3]) {
		char buffer[120];

		//if (ins123[INS3] & KX13X_INT_INS3_WUFS)
		//if (ins123[INS3] & KX13X_INT_INS3_BTS)
		if (dev->plat->debug_print) {
			char format[] = "%s INS3 0x%x \n";
			(void)sprintf(buffer, format, sensor_name, ins123[INS3]);
			dev->plat->debug_print(dev->plat, buffer);
		}

		/* release wu/bts int */
		release_int = 1;
	}

	if (release_int) {
		(void)kx13x_release_int(dev);
	}
	
	return KX13X_RC_OK;
}

int kx13x_example_handle_interrupt(struct kx13x *dev)
{
	int rc;
	uint8_t int_status;

	rc = kx13x_get_int_status(dev, &int_status);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	if (!(int_status & KX13X_INT_STATUS_OCCURED)) {
		/* no interrupt */
		return KX13X_RC_OK;
	}

	rc = kx13x_example_report_ins_status(dev);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

int kx13x_example_poll_interrupt(struct kx13x *dev)
{
	int rc;
	rc = kx13x_example_report_ins_status(dev);
	return rc;
}
