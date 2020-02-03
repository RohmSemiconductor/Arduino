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

#ifndef __KX13X_H__
#define __KX13X_H__

#ifdef __cplusplus
extern "C" {
#endif

/* I2C address */
#define KX13X_I2C_ADDRESS_1E (0x1E)
#define KX13X_I2C_ADDRESS_1F (0x1F)

/* supported sensors */
#define	KX13X_TYPE_KX132_1211 1
#define	KX13X_TYPE_KX134_1211 2

/* sensor feature, bit */
#define KX13X_FEA_NONE	0x00
#define KX13X_FEA_DRDY	(0x01 << 0)
#define KX13X_FEA_BUF	(0x01 << 2)
#define KX13X_FEA_WUF	(0x01 << 3)
#define KX13X_FEA_BTS	(0x01 << 4)
#define KX13X_FEA_FREEFALL	(0x01 << 5)
#define KX13X_FEA_TAP	(0x01 << 6)
#define KX13X_FEA_TILT	(0x01 << 7)

/* forward declare */
struct kx13x;
struct platform;

/* Function return codes */
#define KX13X_RC_OK (0)
#define KX13X_RC_ERR (-1)
#define KX13X_RC_INVALID_PARAM (-2)
#define KX13X_RC_NOT_SUPPORTED (-3)

/* KX13x disabled/enabled feature */
#define KX13X_DISABLED	0
#define KX13X_ENABLED	1

/* KX13X operating modes */
#define KX13X_OPER_MODE_STANDBY   0
#define KX13X_OPER_MODE_OPERATING 1
int kx13x_set_oper_mode(struct kx13x *dev, uint8_t mode);
int kx13x_get_oper_mode(struct kx13x *dev, uint8_t *mode);

/* KX13X performance mode */
#define KX13X_PERF_MODE_LOW_POWER 0
#define KX13X_PERF_MODE_HIGH_RES 1
int kx13x_set_perf_mode(struct kx13x *dev, uint8_t mode);

/* KX13X acceleration range, bits */
#define KX13X_GRANGE_2G		2
#define KX13X_GRANGE_4G		4
#define KX13X_GRANGE_8G		8
#define KX13X_GRANGE_16G	16
#define KX13X_GRANGE_32G	32
#define KX13X_GRANGE_64G	64
#define KX13X_GRANGE_AMOUNT	6
int kx13x_set_grange(struct kx13x *dev, uint8_t grange);

/* KX13X ODR */
#define KX13X_ODR_0P781HZ	(0x00 << 0)
#define KX13X_ODR_1P563HZ	(0x01 << 0)
#define KX13X_ODR_3P125HZ	(0x02 << 0)
#define KX13X_ODR_6P25HZ	(0x03 << 0)
#define KX13X_ODR_12P5HZ	(0x04 << 0)
#define KX13X_ODR_25HZ		(0x05 << 0)
#define KX13X_ODR_50HZ		(0x06 << 0)
#define KX13X_ODR_100HZ		(0x07 << 0)
#define KX13X_ODR_200HZ		(0x08 << 0)
#define KX13X_ODR_400HZ		(0x09 << 0)
#define KX13X_ODR_800HZ		(0x0A << 0)
#define KX13X_ODR_1600HZ	(0x0B << 0)
#define KX13X_ODR_3200HZ	(0x0C << 0)
#define KX13X_ODR_6400HZ	(0x0D << 0)
#define KX13X_ODR_12800HZ	(0x0E << 0)
#define KX13X_ODR_25600HZ	(0x0F << 0)
int kx13x_set_odr(struct kx13x *dev, uint8_t odr);

/* KX13x disable/enable DRDY */
int kx13x_set_drdy_enabled(struct kx13x *dev, uint8_t enable);

/* KX13X low pass filter */
#define KX13X_BYPASS_BYPASSED	0
#define KX13X_BYPASS_ODR_2		1
#define KX13X_BYPASS_ODR_9		2
#define KX13X_BYPASS_AMOUNT		3
int kx13x_set_low_pass_filter(struct kx13x *dev, uint8_t filter);

/* KX13X avg filter */
#define KX13X_AVG_NO_AVG	0
#define KX13X_AVG_2_SAMPLE	1
#define KX13X_AVG_4_SAMPLE	2
#define KX13X_AVG_8_SAMPLE	3
#define KX13X_AVG_16_SAMPLE	4
#define KX13X_AVG_32_SAMPLE	5
#define KX13X_AVG_64_SAMPLE	6
#define KX13X_AVG_AMOUNT	7
int kx13x_set_avg_filter_ctrl(struct kx13x *dev, uint8_t avc);

/* KX13X accel config structure */
struct kx13x_accel_cfg {
	uint8_t perf_mode;
	uint8_t grange;
	uint8_t odr;
	uint8_t drdy_enable;
	uint8_t filter;
	uint8_t avc; /* Note, affects also to other engines */
};

int kx13x_set_accel_cfg(struct kx13x *dev, struct kx13x_accel_cfg *cfg);

/* KX13X get accel xyz-data */
int kx13x_get_accel_data_raw(struct kx13x *dev, int16_t *xyz_raw);
int kx13x_get_accel_data(struct kx13x *dev, float *xyz);

/* KX13X Wake-up/back to sleep feature */

/* KX13X wu or bts odr */
#define KX13X_WU_0P781HZ	0x00
#define KX13X_WU_1P563HZ	0x01
#define KX13X_WU_3P125HZ	0x02
#define KX13X_WU_6P25HZ		0x03
#define KX13X_WU_12P5HZ		0x04
#define KX13X_WU_25HZ		0x05
#define KX13X_WU_50HZ		0x06
#define KX13X_WU_100HZ		0x07

/* KX13X wu or bts config struct */
struct kx13x_wu_cfg {
	uint8_t enable;		/* wakeup/back-to-sleep enabled */
	uint16_t threshold;	/* 3.9 mg/count, 11bit value */
	uint8_t counter;	/* WUFC/BTSC counter */
	uint8_t odr;		/* WU/BTS counter */
};

/* KX13X wu/bts modes */
#define KX13X_WU_MODES_C_RESET			(0x00 << 7)
#define KX13X_WU_MODES_C_DECREMENTED	(0x01 << 7)
#define KX13X_WU_MODES_TH_ABSOLUTE		(0x00 << 6)
#define KX13X_WU_MODES_TH_RELATIVE		(0x01 << 6)
#define KX13X_WU_MODES_PR_STANDARD		(0x00 << 3)
#define KX13X_WU_MODES_PR_REJECTED		(0x01 << 3)

/* KX13X wu/bts axes config */
#define KX13X_WU_AXES_AOI_OR	(0x00 << 6)
#define KX13X_WU_AXES_AOI_AND	(0x01 << 6)
#define KX13X_WU_AXES_XNWUE		(0x01 << 5)
#define KX13X_WU_AXES_XPWUE		(0x01 << 4)
#define KX13X_WU_AXES_YNWUE		(0x01 << 3)
#define KX13X_WU_AXES_YPWUE		(0x01 << 2)
#define KX13X_WU_AXES_ZNWUE		(0x01 << 1)
#define KX13X_WU_AXES_ZPWUE		(0x01 << 0)

/* KX13X wu/bts config */
struct kx13x_wu_bts_cfg {
	struct kx13x_wu_cfg *wu;	/* wake-up config or NULL */
	struct kx13x_wu_cfg *bts;	/* back-to-sleep config or NULL */
	uint8_t mode_bits;			/* common config */
	uint8_t axes_bits;			/* common config */
};

int kx13x_set_wu_bts_cfg(struct kx13x *dev, struct kx13x_wu_bts_cfg *cfg);

/* KX13X ADP config */

/* ADP filter1 */
#define KX13X_ADP_FILTER1_NONE			(0xff)
#define KX13X_ADP_FILTER1_LP_ODR_4		(0)
#define KX13X_ADP_FILTER1_LP_ODR_8		(1)
#define KX13X_ADP_FILTER1_LP_ODR_16		(2)
#define KX13X_ADP_FILTER1_LP_ODR_32		(3)
#define KX13X_ADP_FILTER1_LP_ODR_64		(4)
#define KX13X_ADP_FILTER1_LP_ODR_128	(5)
#define KX13X_ADP_FILTER1_LP_ODR_256	(6)
#define KX13X_ADP_FILTER1_LP_ODR_512	(7)
#define KX13X_ADP_FILTER1_LP_ODR_1024	(8)
#define KX13X_ADP_FILTER1_LP_ODR_2048	(9)
#define KX13X_ADP_FILTER1_LP_ODR_6p400	(10)
#define KX13X_ADP_FILTER1_LP_ODR_4p266	(11)
#define KX13X_ADP_FILTER1_LP_ODR_4p830	(12)

/* ADP filter2 */
#define KX13X_ADP_FILTER2_NONE			(0xff)
/* LP-filters */
#define KX13X_ADP_FILTER2_LP_ODR_4		(0)
#define KX13X_ADP_FILTER2_LP_ODR_8      (1)
#define KX13X_ADP_FILTER2_LP_ODR_16     (2)
#define KX13X_ADP_FILTER2_LP_ODR_32     (3)
#define KX13X_ADP_FILTER2_LP_ODR_64     (4)
#define KX13X_ADP_FILTER2_LP_ODR_128    (5)
#define KX13X_ADP_FILTER2_LP_ODR_256    (6)
#define KX13X_ADP_FILTER2_LP_ODR_512	(7)
#define KX13X_ADP_FILTER2_LP_ODR_1024   (8)
#define KX13X_ADP_FILTER2_LP_ODR_2048   (9)
#define KX13X_ADP_FILTER2_LP_ODR_8p533  (10)
/* HP-filters */
#define KX13X_ADP_FILTER2_HP_ODR_4      (11)
#define KX13X_ADP_FILTER2_HP_ODR_8      (12)
#define KX13X_ADP_FILTER2_HP_ODR_16     (13)
#define KX13X_ADP_FILTER2_HP_ODR_32		(14)
#define KX13X_ADP_FILTER2_HP_ODR_40		(15)
#define KX13X_ADP_FILTER2_HP_ODR_64		(16)
#define KX13X_ADP_FILTER2_HP_ODR_128	(17)
#define KX13X_ADP_FILTER2_HP_ODR_256	(18)
#define KX13X_ADP_FILTER2_HP_ODR_512	(19)
#define KX13X_ADP_FILTER2_HP_ODR_640	(20)
#define KX13X_ADP_FILTER2_HP_ODR_1024	(21)
#define KX13X_ADP_FILTER2_HP_ODR_2048	(22)
#define KX13X_ADP_FILTER2_HP_ODR_6p400	(23)
#define KX13X_ADP_FILTER2_HP_ODR_4p413	(24)
#define KX13X_ADP_FILTER2_HP_ODR_4p266	(25)
#define KX13X_ADP_FILTER2_HP_ODR_2p844	(26)
#define KX13X_ADP_FILTER2_HP_ODR_3p938	(27)
/* HP-filters start index */
#define KX13X_ADP_FILTER2_HP_FILTERS KX13X_ADP_FILTER2_HP_ODR_4

/* ADP RMS average */
#define KX13X_ADP_RMS_AVC_NONE			(0xff)
#define KX13X_ADP_RMS_AVC_2_SAMPLE_AVG	(0x00 << 4)
#define KX13X_ADP_RMS_AVC_4_SAMPLE_AVG	(0x01 << 4)
#define KX13X_ADP_RMS_AVC_8_SAMPLE_AVG	(0x02 << 4)
#define KX13X_ADP_RMS_AVC_16_SAMPLE_AVG	(0x03 << 4)
#define KX13X_ADP_RMS_AVC_32_SAMPLE_AVG	(0x04 << 4)
#define KX13X_ADP_RMS_AVC_64_SAMPLE_AVG	(0x05 << 4)
#define KX13X_ADP_RMS_AVC_128_SAMPLE_AVG	(0x06 << 4)
#define KX13X_ADP_RMS_AVC_256_SAMPLE_AVG	(0x07 << 4)

/* ADP engine configuration */
struct kx13x_adp_cfg {
	uint8_t filter1; /* KX13X_ADP_FILTER1_ */
	uint8_t filter2; /* KX13X_ADP_FILTER2_ */
	uint8_t adp_odr; /* KX132X_ODR_ */
    uint8_t rms_avg; /* KX13X_ADP_RMS_AVC_ */
	uint8_t adp_enabled; /* KX13X_DISABLED / KX13X_ENABLED */
};

int kx13x_set_adp_cfg(struct kx13x *dev, struct kx13x_adp_cfg *cfg);

int kx13x_get_adp_data_raw(struct kx13x *dev, int16_t *xyz_raw);
int kx13x_get_adp_data(struct kx13x *dev, float *xyz);

/* KX13X interrupt */

/* KX13X int pin selection */
#define KX13X_INT1_PIN 0
#define KX13X_INT2_PIN 1

/* KX13X interrupt routing bits */
#define KX13X_INT_ROUTE_NONE		0x00
#define KX13X_INT_ROUTE_TILT		(0x01 << 0)
#define KX13X_INT_ROUTE_WUF			(0x01 << 1)
#define KX13X_INT_ROUTE_TAP			(0x01 << 2)
#define KX13X_INT_ROUTE_BTS			(0x01 << 3)
#define KX13X_INT_ROUTE_DRDY		(0x01 << 4)
#define KX13X_INT_ROUTE_BUF_WM		(0x01 << 5)
#define KX13X_INT_ROUTE_BUF_FULL	(0x01 << 6)
#define KX13X_INT_ROUTE_FREEFALL	(0x01 << 7)
int kx13x_set_int_route(struct kx13x *dev, uint8_t pin, uint8_t route);

/* KX13X interrupt level */
#define KX13X_INT_LEVEL_LOW		0
#define KX13X_INT_LEVEL_HIGH	1
int kx13x_set_int_level(struct kx13x *dev, uint8_t pin, uint8_t level);

/* KX13X interrupt control */
#define KX13X_INT_CTRL_LATCH			0
#define KX13X_INT_CTRL_PULSE_50US_10US	1
#define KX13X_INT_CTRL_PULSE_1XODR		2
#define KX13X_INT_CTRL_PULSE_2XODR		3
#define KX13X_INT_CTRL_PULSE_REALTIME	4
#define KX13X_INT_CTRL_AMOUNT			5
int kx13x_set_int_ctrl(struct kx13x *dev, uint8_t pin, uint8_t int_ctrl);

/* KX13X interrupt pin enable/disable */
int kx13x_set_int_enabled(struct kx13x *dev, uint8_t pin, uint8_t enable);

/* KX13X interrupt pin config */
struct kx13x_interrupt_cfg {
	uint8_t enable;
	uint8_t routing;
	uint8_t level;
	uint8_t ctrl;
};

int kx13x_set_int_cfg(struct kx13x *dev, uint8_t pin, struct kx13x_interrupt_cfg *cfg);

/* Interrupt statuses */
#define KX13X_INT_STATUS_OCCURED	(0x01 << 4)
int kx13x_get_int_status(struct kx13x *dev, uint8_t *status);

/* INS2 status */
#define KX13X_INT_INS2_DRDY	(0x01 << 4)
/* INS3 status */
#define KX13X_INT_INS3_BTS	(0x01 << 6)
#define KX13X_INT_INS3_WUFS	(0x01 << 7)
int kx13x_get_int_ins123(struct kx13x *dev, uint8_t *ins123);

/* KX13X interrupt latch */
int kx13x_release_int(struct kx13x *dev);

/* KX13X soft reset */
int kx13x_reset(struct kx13x *dev);

/* Sensor configuration structure */
struct kx13x_cfg {
	uint8_t oper_mode;					/* mandatory */
	struct kx13x_accel_cfg *accel;		/* cfg or NULL */
	struct kx13x_wu_bts_cfg *wu_bts;	/* cfg or NULL */
	struct kx13x_adp_cfg *adp;			/* cfg or NULL */
	struct kx13x_interrupt_cfg *int1;	/* cfg or NULL */
	struct kx13x_interrupt_cfg *int2;	/* cfg or NULL */
};

/* Sensor driver data structure */
struct kx13x {
	struct platform *plat;	/* data provided by platform */
	uint16_t granges;		/* supported granges */
	uint16_t gsens;			/* accel raw data to si-format convert param */
	uint8_t wai_id;			/* wai_id read from sensor */
};

/**
 *
 */
int kx13x_init(struct kx13x *dev, struct platform *plat);

/**
 *  Returns pointer to sensor name or NULL in fail case
 */
char* kx13x_get_name(struct kx13x *dev);

/**
 * Sets sensor device configuration.
 *
 * @param  dev	  Pointer to the kx13x struct
 * @param  dev_cfg  Pointer to the kx13x configuration
 *
 * @return 0 on success, non-zero on failure.
 */
int kx13x_set_config(struct kx13x *dev, struct kx13x_cfg *dev_cfg);

/**
 * Dump sensor registers
 */
int kx13x_debug_dump_regs(struct kx13x *dev);

#ifdef __cplusplus
}
#endif

#endif /* __KX13X_H__ */
