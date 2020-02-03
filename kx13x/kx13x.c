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
#include "kx132_1211_registers.h"
#include "kx134_1211_registers.h"

#define UNUSED_VAR(a) (void)a

/* Macro to enable debug prints */
#define KX13X_DEBUG

#ifdef KX13X_DEBUG
#define KX13X_TRACE_STR(dev,str) kx13x_debug_print_str(dev,str)
#define KX13X_TRACE_STR_1(dev,str,aa) kx13x_debug_print_str_1(dev,str,aa)
#define KX13X_TRACE_STR_2(dev,str,aa,bb) kx13x_debug_print_str_2(dev,str,aa,bb)
#else
#define KX13X_TRACE_STR(dev,str)
#define KX13X_TRACE_STR_1(dev,str,aa)
#define KX13X_TRACE_STR_2(dev,str,aa,bb)
#endif

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

/* Supported sensors info */
struct kx13x_sensor_info
{
	uint8_t 	type;
	char		name[11];
	uint8_t		wai_id;
	uint16_t	granges;	
};

static struct kx13x_sensor_info kx13x_supported_sensors[] = 
{	
	{
		.type = KX13X_TYPE_KX132_1211,
		.name = "KX132-1211",
		.wai_id = KX132_1211_WHO_AM_I_WAI_ID,
		.granges = (KX13X_GRANGE_2G|KX13X_GRANGE_4G|KX13X_GRANGE_8G|KX13X_GRANGE_16G)		
	},
	{
		.type = KX13X_TYPE_KX134_1211,
		.name = "KX134-1211",
		.wai_id = KX134_1211_WHO_AM_I_WAI_ID,
		.granges = (KX13X_GRANGE_8G|KX13X_GRANGE_16G|KX13X_GRANGE_32G|KX13X_GRANGE_64G)		
	},
};

static struct kx13x_sensor_info* kx13x_sensors_info_is_supported(uint8_t wai_id)
{
	struct kx13x_sensor_info *sensor = NULL;
	uint16_t i;

	for (i = 0; i < ARRAY_SIZE(kx13x_supported_sensors); i++) {
		if (kx13x_supported_sensors[i].wai_id == wai_id) {
			sensor = (struct kx13x_sensor_info *)&kx13x_supported_sensors[i];
			break;
		}
	}

	return sensor;
}

/* Platform debug print */
int kx13x_platform_debug_print(struct platform *plat, char *str)
{
	if (plat->debug_print)
		 plat->debug_print(plat, str);

	return KX13X_RC_OK;
}

/* Platform delay function */
int kx13x_platform_delay_ms(struct platform *plat, uint16_t ms)
{
	return plat->delay_ms(plat, ms);
}

/* Platform sensor bus register read/write */
int kx13x_platform_read(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	return plat->read(plat, reg, data, size);
}

int kx13x_platform_write(struct platform *plat, uint8_t reg, uint8_t *data, uint8_t size)
{
	return plat->write(plat, reg, data, size);
}

/* Sensor driver register read/write */
int kx13x_read_reg(struct kx13x *dev, uint8_t reg, uint8_t *data, uint8_t size)
{
	return kx13x_platform_read(dev->plat, reg, data, size);
}

int kx13x_write_reg(struct kx13x *dev, uint8_t reg, uint8_t *data, uint8_t size)
{
	return kx13x_platform_write(dev->plat, reg, data, size);
}

int kx13x_read_reg_byte(struct kx13x *dev, uint8_t reg, uint8_t *data)
{
	return kx13x_read_reg(dev, reg, data, 1);
}

int kx13x_write_reg_byte(struct kx13x *dev, uint8_t reg, uint8_t data)
{
	return kx13x_write_reg(dev, reg, &data, 1);
}
	
int kx13x_set_reg_bit_pattern(struct kx13x *dev, uint8_t reg, uint8_t bit_pattern, uint8_t mask)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_read_reg_byte(dev, reg, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	reg_val &= ~mask;
	reg_val |= (bit_pattern & mask);

	rc = kx13x_write_reg_byte(dev, reg, reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

int kx13x_set_reg_bit(struct kx13x *dev, uint8_t reg, uint8_t bits)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_read_reg_byte(dev, reg, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	reg_val |= bits;

	return kx13x_write_reg_byte(dev, reg, reg_val);
}

int kx13x_reset_reg_bit(struct kx13x *dev, uint8_t reg, uint8_t bits)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_read_reg_byte(dev, reg, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	reg_val &= ~bits;

	return kx13x_write_reg_byte(dev, reg, reg_val);
}

/* kx13x.h define to reg mapping and get/set functions*/
struct kx13x_define_reg_bits {
	uint8_t _define;
	uint8_t _reg_bits;
};

struct kx13x_define_reg_map {
	uint8_t reg;
	uint8_t mask;
	uint8_t amount;
	struct kx13x_define_reg_bits values[];
};

int kx13x_map_to_reg_bits(struct kx13x_define_reg_map *map, uint8_t _define, uint8_t *_reg_bits)
{
	int rc = KX13X_RC_INVALID_PARAM;
	uint16_t i;

	for (i = 0; i < map->amount; i++) {
		if (map->values[i]._define == _define) {
			*_reg_bits = map->values[i]._reg_bits;
			rc = KX13X_RC_OK;
			break;
		}
	}

	return rc;
}

int kx13x_map_to_define_val(struct kx13x_define_reg_map *map, uint8_t _reg_bits, uint8_t *_define)
{
	int rc = KX13X_RC_INVALID_PARAM;
	uint16_t i;

	uint8_t reg_bits = map->mask & _reg_bits;

	for (i = 0; i < map->amount; i++) {
		if (map->values[i]._reg_bits == reg_bits) {
			*_define = map->values[i]._define;
			rc = KX13X_RC_OK;
			break;
		}
	}

	return rc;
}

int kx13x_set_map_reg_bits(struct kx13x *dev, struct kx13x_define_reg_map *map, uint8_t _define)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_map_to_reg_bits(map, _define, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_reg_bit_pattern(dev, map->reg, reg_val, map->mask);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	return KX13X_RC_OK;
}

/* Debug */
#ifdef KX13X_DEBUG
static void kx13x_debug_print_str(struct kx13x *dev, char *str)
{
	kx13x_platform_debug_print(dev->plat, str);
}

static void kx13x_debug_print_str_1(struct kx13x *dev, char *str, int val1)
{
	char buffer[100];
	(void)sprintf(buffer, str, val1);
	kx13x_platform_debug_print(dev->plat, buffer);
}

static void kx13x_debug_print_str_2(struct kx13x *dev, char *str, int val1, int val2)
{
	char buffer[100];
	(void)sprintf(buffer, str, val1, val2);
	kx13x_platform_debug_print(dev->plat, buffer);
}
#endif

int kx13x_debug_dump_regs(struct kx13x *dev)
{
#ifdef KX13X_DEBUG
	int rc;
	uint8_t dump_regs[] = {
		KX132_1211_STATUS_REG,
		KX132_1211_CNTL1,
		KX132_1211_CNTL2,
		KX132_1211_CNTL3,
		KX132_1211_CNTL4,
		KX132_1211_CNTL5,
		KX132_1211_ODCNTL,
		KX132_1211_INC1,
		KX132_1211_INC2,
		KX132_1211_INC3,
		KX132_1211_INC4,
		KX132_1211_INC5,
		KX132_1211_INC6,
		KX132_1211_LP_CNTL1
	};
	uint8_t reg_val;
	uint8_t i;

	KX13X_TRACE_STR(dev, "kx13x_debug_dump_regs:\n");

	for (i=0; i < ARRAY_SIZE(dump_regs); i++) {
		rc = kx13x_read_reg_byte(dev, dump_regs[i], &reg_val);
		if (rc != KX13X_RC_OK) {
			return rc;
		}

		KX13X_TRACE_STR_2(dev, "reg 0x%x val 0x%x\n",dump_regs[i],reg_val);
	}
#else
	UNUSED_VAR(dev);
#endif
	return KX13X_RC_OK;
}

/* Operation mode  */
int kx13x_set_oper_mode(struct kx13x *dev, uint8_t oper)
{
	int rc;

	switch(oper) {
	case KX13X_OPER_MODE_OPERATING:
		rc = kx13x_set_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_PC1);
		break;
	case KX13X_OPER_MODE_STANDBY:
		rc = kx13x_reset_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_PC1);
		break;
	default:
		rc = KX13X_RC_INVALID_PARAM;
		break;
	}

	return rc;	
}

int kx13x_get_oper_mode(struct kx13x *dev, uint8_t *oper)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_read_reg_byte(dev, KX132_1211_CNTL1, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	if (reg_val & KX132_1211_CNTL1_PC1) {
		*oper = KX13X_OPER_MODE_OPERATING;
	} else {
		*oper = KX13X_OPER_MODE_STANDBY;
	}

	return KX13X_RC_OK;
}

/* Perf mode */
int kx13x_set_perf_mode(struct kx13x *dev, uint8_t perf)
{
	int rc;

	switch(perf) {
	case KX13X_PERF_MODE_LOW_POWER:
		rc = kx13x_reset_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_RES);
		break;
	case KX13X_PERF_MODE_HIGH_RES:
		rc = kx13x_set_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_RES);
		break;
	default:
		rc = KX13X_RC_INVALID_PARAM;
		break;
	}

	return rc;	
}

/* grange */
static struct kx13x_define_reg_map grange16_map = 
{
	.reg = KX132_1211_CNTL1,
	.mask = KX132_1211_CNTL1_GSEL_MASK,
	.amount = 4,
	.values = {
		{
			._define = KX13X_GRANGE_2G,
			._reg_bits = KX132_1211_CNTL1_GSEL_2G,
		},
		{
			._define = KX13X_GRANGE_4G,
			._reg_bits = KX132_1211_CNTL1_GSEL_4G,
		},
		{
			._define = KX13X_GRANGE_8G,
			._reg_bits = KX132_1211_CNTL1_GSEL_8G,
		},
		{
			._define = KX13X_GRANGE_16G,
			._reg_bits = KX132_1211_CNTL1_GSEL_16G,
		},
	}
};

static struct kx13x_define_reg_map grange64_map = 
{
	.reg = KX134_1211_CNTL1,
	.mask = KX134_1211_CNTL1_GSEL_MASK,
	.amount = 4,
	.values = {
		{
			._define = KX13X_GRANGE_8G,
			._reg_bits = KX134_1211_CNTL1_GSEL_8G,
		},
		{
			._define = KX13X_GRANGE_16G,
			._reg_bits = KX134_1211_CNTL1_GSEL_16G,
		},
		{
			._define = KX13X_GRANGE_32G,
			._reg_bits = KX134_1211_CNTL1_GSEL_32G,
		},
		{
			._define = KX13X_GRANGE_64G,
			._reg_bits = KX134_1211_CNTL1_GSEL_64G,
		},
	}
};

/* calculate 1g LSB counts, 16bit counts div by selected -/+ range */
#define KX13X_GRANGE_TO_GSENS(enum_g) (0x10000 / (enum_g*2))

int kx13x_set_grange(struct kx13x *dev, uint8_t grange)
{
	int rc;
	struct kx13x_define_reg_map *map;
	
	if (!(dev->granges & grange)) {
		return KX13X_RC_NOT_SUPPORTED;
	}

	if (dev->granges & KX13X_GRANGE_64G) {
		/* Note, check 64G first */
		map = &grange64_map;
	} else {
		map = &grange16_map;
	}

	rc = kx13x_set_map_reg_bits(dev, map, grange);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	dev->gsens = KX13X_GRANGE_TO_GSENS(grange);

	return KX13X_RC_OK;
}

int kx13x_set_odr(struct kx13x *dev, uint8_t odr)
{
	int rc;
	rc = kx13x_set_reg_bit_pattern(dev, KX132_1211_ODCNTL, odr, KX132_1211_ODCNTL_OSA_MASK);
	return rc;
}

/* Enable DRDY */
int kx13x_set_drdy_enabled(struct kx13x *dev, uint8_t enable)
{
	int rc;

	switch(enable) {
	case KX13X_ENABLED:
		rc = kx13x_set_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_DRDYE);
		break;
	case KX13X_DISABLED:
		rc = kx13x_reset_reg_bit(dev, KX132_1211_CNTL1, KX132_1211_CNTL1_DRDYE);
		break;
	default:
		rc = KX13X_RC_INVALID_PARAM;
		break;
	}

	return rc;	
}

/*  Lowpass / bybass */
static struct kx13x_define_reg_map bypass_map = 
{
	.reg = KX132_1211_ODCNTL,
	.mask = (KX132_1211_ODCNTL_IIR_BYPASS_MASK | KX132_1211_ODCNTL_LPRO_MASK),
	.amount = KX13X_BYPASS_AMOUNT,
	.values = {
		{
			._define = KX13X_BYPASS_BYPASSED,
			._reg_bits = KX132_1211_ODCNTL_IIR_BYPASS_BYPASSED,
		},
		{
			._define = KX13X_BYPASS_ODR_2,
			._reg_bits = KX132_1211_ODCNTL_IIR_BYPASS_NOT_BYPASSED | KX132_1211_ODCNTL_LPRO_ODR_2,
		},
		{
			._define = KX13X_BYPASS_ODR_9,
			._reg_bits = KX132_1211_ODCNTL_IIR_BYPASS_NOT_BYPASSED | KX132_1211_ODCNTL_LPRO_ODR_9,
		},
	}
};

int kx13x_set_low_pass_filter(struct kx13x *dev, uint8_t filter)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_map_to_reg_bits(&bypass_map, filter, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_reg_bit_pattern(dev, bypass_map.reg, reg_val, bypass_map.mask);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

/* Average filter  */
static struct kx13x_define_reg_map avg_map = 
{
	.reg = KX132_1211_LP_CNTL1,
	.mask = KX132_1211_LP_CNTL1_AVC_MASK,
	.amount = KX13X_AVG_AMOUNT,
	.values = {
		{
			._define = KX13X_AVG_NO_AVG,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_NO_AVG,
		},
		{
			._define = KX13X_AVG_2_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_2_SAMPLE_AVG,
		},
		{
			._define = KX13X_AVG_4_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_4_SAMPLE_AVG,
		},
		{
			._define = KX13X_AVG_8_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_8_SAMPLE_AVG,
		},
		{
			._define = KX13X_AVG_32_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_32_SAMPLE_AVG,
		},
		{
			._define = KX13X_AVG_16_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_16_SAMPLE_AVG,
		},
		{
			._define = KX13X_AVG_64_SAMPLE,
			._reg_bits = KX132_1211_LP_CNTL1_AVC_64_SAMPLE_AVG,
		},
		
	}
};

int kx13x_set_avg_filter_ctrl(struct kx13x *dev, uint8_t avc)
{
	int rc;
	uint8_t reg_val;

	rc = kx13x_map_to_reg_bits(&avg_map, avc, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_reg_bit_pattern(dev, avg_map.reg, reg_val, avg_map.mask);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

/* Get accel data */
int kx13x_get_accel_data_raw(struct kx13x *dev, int16_t *xyz_raw)
{
	int rc;
	uint8_t xyz[6];

	rc = kx13x_read_reg(dev, KX132_1211_XOUT_L, (uint8_t*)xyz, 6);
	if (rc != KX13X_RC_OK)
	{
		return rc;
	}

	xyz_raw[0] = ((int16_t)xyz[0]) | (((int16_t)xyz[1]) << 8);
	xyz_raw[1] = ((int16_t)xyz[2]) | (((int16_t)xyz[3]) << 8);
	xyz_raw[2] = ((int16_t)xyz[4]) | (((int16_t)xyz[5]) << 8);

	return KX13X_RC_OK;	
}

int kx13x_get_accel_data(struct kx13x *dev, float *xyz)
{
	int16_t raw_xyz[3];
	int rc;

	rc = kx13x_get_accel_data_raw(dev, &raw_xyz[0]);
	if (rc != KX13X_RC_OK)
	{
		return rc;
	}

	xyz[0] = (float)raw_xyz[0] / dev->gsens;
	xyz[1] = (float)raw_xyz[1] / dev->gsens;
	xyz[2] = (float)raw_xyz[2] / dev->gsens;

	return KX13X_RC_OK;
}

int kx13x_set_accel_cfg(struct kx13x *dev, struct kx13x_accel_cfg *cfg)
{
	int rc;
	
	rc = kx13x_set_perf_mode(dev, cfg->perf_mode);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_grange(dev, cfg->grange);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_odr(dev, cfg->odr);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_drdy_enabled(dev, cfg->drdy_enable);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_low_pass_filter(dev, cfg->filter);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_avg_filter_ctrl(dev, cfg->avc);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	return KX13X_RC_OK;
}

/* Wake-up/back to sleep */
int kx13x_set_wu_bts_cfg(struct kx13x *dev, struct kx13x_wu_bts_cfg *cfg)
{
	int rc;
	uint8_t cntl4 = 0;
	uint8_t bts_wuf_th_hibits = 0;
	uint8_t reg_val;

	/* Wake-up settings */
	if (cfg->wu) {

		if (cfg->wu->enable) {
			cntl4 |= KX132_1211_CNTL4_WUFE_ENABLED;
		}

		/* wu threshold lo-8bits */
		reg_val = cfg->wu->threshold & 0xff;
		rc = kx13x_write_reg_byte(dev, KX132_1211_WUFTH, reg_val);
		if (rc != KX13X_RC_OK) {
			return rc;
		}

		/* wu threshold hi-3bits to BTSWUFTH lo-nibble  */
		bts_wuf_th_hibits = ((cfg->wu->threshold >> 8) & 0x07);

		/* wu counter */
		rc = kx13x_write_reg_byte(dev, KX132_1211_WUFC, cfg->wu->counter);
		if (rc != KX13X_RC_OK) {
			return rc;
		}

		/* wu odr */
		rc = kx13x_set_reg_bit_pattern(dev, KX132_1211_CNTL3, cfg->wu->odr, KX132_1211_CNTL3_OWUF_MASK);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}

	/* Back to sleep settings */
	if (cfg->bts) {

		if (cfg->bts->enable) {
			cntl4 |= KX132_1211_CNTL4_BTSE_ENABLED;
		}

		/* bts threshold lo-8bits */
		reg_val = cfg->bts->threshold & 0xff;
		rc = kx13x_write_reg_byte(dev, KX132_1211_BTSTH, reg_val);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
		/* bts threshold hi-3bits to BTSWUFTH hi-nibble  */
		bts_wuf_th_hibits |= ((cfg->bts->threshold >> 8) & 0x07) << 4;
		
		/* bts counter */
		rc = kx13x_write_reg_byte(dev, KX132_1211_BTSC, cfg->bts->counter);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
		
		/* bts odr */
		cntl4 |= cfg->bts->odr;
	}

	/* set bts_wuf_th_hibits */
	rc = kx13x_write_reg_byte(dev, KX132_1211_BTSWUFTH, bts_wuf_th_hibits);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* direction mask and occurrence */
	rc = kx13x_write_reg_byte(dev, KX132_1211_INC2, cfg->axes_bits);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* set wu/bts mode bits and write CNTL4 */
	cntl4 |= cfg->mode_bits;

	rc = kx13x_write_reg_byte(dev, KX132_1211_CNTL4, cntl4);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* manual force */
	rc = kx13x_set_reg_bit(dev, KX132_1211_CNTL5, KX132_1211_CNTL5_MAN_WAKE);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}
/* Advanced data path (ADP) */
struct f1_filter {
	uint8_t f1_1a;  /* <6:0> */
	uint32_t f1_ba; /* <22:0> */
	uint32_t f1_ca; /* <22:0> */
	uint8_t f1_ish; /* <4:0> */
	uint8_t f1_osh; /* <0> bit */
};

struct f1_filter pre_def_f1_filters[] =
{
	{22, 0, 1439258, 1, 1},
	{72, 3954428, 2796203, 2, 0},
	{117, 6099540, 4815580, 4, 0},
	{10, 7230041, 6354764, 5, 0},
	{20, 7807115, 7301172, 7, 0},
	{25, 8097550, 7826024, 9, 0},
	{27, 8243038, 8102435, 11, 0},
	{29, 8315818, 8244280, 13, 0},
	{29, 8352212, 8316131, 15, 0},
	{30, 8370410, 8352291, 17, 0},
	{15,2934914,2176803,1,0},
	{52, 4213708, 2986360, 2, 0},
	{18, 4674381, 3358701, 2, 0},
};

int kx13x_set_adp_filter1(struct kx13x *dev, uint8_t filter1)
{
	int rc;
	struct f1_filter *f1;

    if (filter1 == KX13X_ADP_FILTER1_NONE) {
		/* disable filter1 */
		rc = kx13x_set_reg_bit(dev, KX132_1211_ADP_CNTL2, KX132_1211_ADP_CNTL2_ADP_FLT1_BYP);
		return rc;
	}
	
	/* enable filter1 */
	rc = kx13x_reset_reg_bit(dev, KX132_1211_ADP_CNTL2, KX132_1211_ADP_CNTL2_ADP_FLT1_BYP);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* get filter parameters */
	f1 = &pre_def_f1_filters[filter1];

	/* set filter1 parameters */
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL3, f1->f1_1a);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL4, f1->f1_ba & 0xff);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL5, (f1->f1_ba >> 8) & 0xff);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL6, (f1->f1_ba >> 16) & 0x7f);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL7, f1->f1_ca & 0xff);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL8, (f1->f1_ca >> 8) & 0xff);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL9, (f1->f1_ca >> 16) & 0x7f);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL10, f1->f1_ish);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_set_reg_bit_pattern(dev, KX134_1211_ADP_CNTL11, f1->f1_osh << 7, KX134_1211_ADP_CNTL11_ADP_F1_OSH);
	
	return rc;
}

struct f2_filter {
	uint8_t f2_1a;  /* <6:0> */
	uint16_t f2_ba; /* <14:0> */
	uint8_t f2_ish; /* <4:0> */
	uint8_t f2_osh; /* <4:0> */
};

struct f2_filter pre_def_f2_filters[] =
{
	{0, 0, 1, 1},
	{22, 13573, 1, 0},
	{42, 21895, 2, 0},
	{56, 26892, 3, 0},
	{64, 29699, 4, 0},
	{68, 31198, 5, 0},
	{71, 31973, 6, 0},
	{72, 32368, 7, 0},
	{72, 32568, 8, 0},
	{73, 32668, 9, 0},
	{33, 22481, 2, 0},
	{0, 0, 1, 1},
	{53, 13573, 2, 2},
	{86, 21895, 3, 3},
	{105, 26892, 4, 4},
	{109, 27987, 4, 4},
	{116, 29699, 5, 5},
	{122, 31198, 6, 6},
	{125, 31973, 7, 7},
	{126, 32368, 8, 8},
	{127, 32448, 8, 8},
	{127, 32568, 9, 9},
	{0, 32668, 9, 10},
	{77, 19640, 3, 3},
	{59, 15006, 2, 2},
	{57, 14523, 2, 2},
	{30, 7779, 2, 2},
	{52, 13336, 2, 2}
};

int kx13x_set_adp_filter2(struct kx13x *dev, uint8_t filter2)
{
	int rc;
	struct f2_filter *f2;

    if (filter2 == KX13X_ADP_FILTER2_NONE) {
		/* disable filter2 */
		rc = kx13x_set_reg_bit(dev, KX132_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_FLT2_BYP);
		return rc;
	}
	
	/* enable filter2 */
	rc = kx13x_reset_reg_bit(dev, KX132_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_FLT2_BYP);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* set filter2 to LP/HP */
    if (filter2 < KX13X_ADP_FILTER2_HP_FILTERS) {
           rc = kx13x_reset_reg_bit(dev, KX134_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_F2_HP);
	} else {
           rc = kx13x_set_reg_bit(dev, KX134_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_F2_HP);
	}
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* get filter2 parameters */
	f2 = &pre_def_f2_filters[filter2];

	/* set filter2 parameters */
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL12, f2->f2_ba & 255);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL13, (f2->f2_ba >> 8) & 255);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL18, f2->f2_ish);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	rc = kx13x_write_reg_byte(dev, KX134_1211_ADP_CNTL19, f2->f2_osh);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_reg_bit_pattern(dev, KX134_1211_ADP_CNTL11, f2->f2_1a, KX134_1211_ADP_CNTL11_ADP_F2_1A_MASK);

	return rc;
}

int kx13x_set_adp_odr(struct kx13x *dev, uint8_t adp_odr)
{
	int rc;
	rc = kx13x_set_reg_bit_pattern(dev, KX132_1211_ADP_CNTL1, adp_odr, KX132_1211_ADP_CNTL1_OADP_MASK);
	return rc;
}

int kx13x_set_adp_rms_avg(struct kx13x *dev, uint8_t rms_avg)
{
	int rc;

	if (rms_avg == KX13X_ADP_RMS_AVC_NONE) {
		/* Route ADP data before RMS block to XADP, YADP, ZADP */
		rc = kx13x_reset_reg_bit(dev, KX134_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_RMS_OSEL);
	} else {
		/* Route ADP data after RMS block to XADP, YADP, ZADP */
		rc = kx13x_set_reg_bit(dev, KX134_1211_ADP_CNTL2, KX134_1211_ADP_CNTL2_ADP_RMS_OSEL);
		if (rc != KX13X_RC_OK) {
			return rc;
		}

		rc = kx13x_set_reg_bit_pattern(dev, KX134_1211_ADP_CNTL1, rms_avg,
										KX134_1211_ADP_CNTL1_RMS_AVC_MASK);
	}

	return rc;
}

int kx13x_set_adp_enabled(struct kx13x *dev, uint8_t enable)
{
	int rc;

	if (enable == KX13X_ENABLED) {
		rc = kx13x_set_reg_bit(dev, KX134_1211_CNTL5, KX132_1211_CNTL5_ADPE_ENABLED);
	} else {
		rc = kx13x_reset_reg_bit(dev, KX134_1211_CNTL5, KX132_1211_CNTL5_ADPE_ENABLED);
	}

	return rc;
}

int kx13x_set_adp_cfg(struct kx13x *dev, struct kx13x_adp_cfg *cfg)
{
	int rc;

	rc = kx13x_set_adp_filter1(dev, cfg->filter1);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_adp_filter2(dev, cfg->filter2);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_adp_odr(dev, cfg->adp_odr);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_adp_rms_avg(dev, cfg->rms_avg);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* enabled/disabled ADP engine */
	rc = kx13x_set_adp_enabled(dev, cfg->adp_enabled);

	return rc;
}

int kx13x_get_adp_data_raw(struct kx13x *dev, int16_t *xyz_raw)
{
	int rc;
	uint8_t xyz[6];

	rc = kx13x_read_reg(dev, KX132_1211_XADP_L, (uint8_t*)xyz, 6);
	if (rc != KX13X_RC_OK)
	{
		return rc;
	}

	xyz_raw[0] = ((int16_t)xyz[0]) | (((int16_t)xyz[1]) << 8);
	xyz_raw[1] = ((int16_t)xyz[2]) | (((int16_t)xyz[3]) << 8);
	xyz_raw[2] = ((int16_t)xyz[4]) | (((int16_t)xyz[5]) << 8);

	return KX13X_RC_OK;	
}

int kx13x_get_adp_data(struct kx13x *dev, float *xyz)
{
	int16_t raw_xyz[3];
	int rc;

	rc = kx13x_get_adp_data_raw(dev, &raw_xyz[0]);
	if (rc != KX13X_RC_OK)
	{
		return rc;
	}

	xyz[0] = (float)raw_xyz[0] / dev->gsens;
	xyz[1] = (float)raw_xyz[1] / dev->gsens;
	xyz[2] = (float)raw_xyz[2] / dev->gsens;

	return KX13X_RC_OK;
}

/* Interrupt pin regs */
struct kx13x_int_regs {
	uint8_t ctrl;
	uint8_t route;
};

static struct kx13x_int_regs int_reg[] = 
{
	/* PIN1 */
	{
		.ctrl = KX132_1211_INC1,
		.route = KX132_1211_INC4,
	},
	/* PIN2 */
	{
		.ctrl = KX132_1211_INC5,
		.route = KX132_1211_INC6,
	},
};

int kx13x_set_int_route(struct kx13x *dev, uint8_t pin, uint8_t route)
{
	int rc;
	uint8_t reg_val;
	
	if (pin < KX13X_INT1_PIN || pin > KX13X_INT2_PIN) {
		return KX13X_RC_INVALID_PARAM;
	}

	reg_val = route;

	/* Update all bits in register */
	rc = kx13x_write_reg_byte(dev, int_reg[pin].route, reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

int kx13x_set_int_level(struct kx13x *dev, uint8_t pin, uint8_t level)
{
	int rc;

	if (pin < KX13X_INT1_PIN || pin > KX13X_INT2_PIN) {
		return KX13X_RC_INVALID_PARAM;
	}

	switch(level) {
	case KX13X_INT_LEVEL_HIGH:
		rc = kx13x_set_reg_bit(dev, int_reg[pin].ctrl, KX132_1211_INC1_IEA1);
		break;
	case KX13X_INT_LEVEL_LOW:
		rc = kx13x_reset_reg_bit(dev, int_reg[pin].ctrl, KX132_1211_INC1_IEA1);
		break;
	default:
		rc = KX13X_RC_INVALID_PARAM;
		break;
	}

	return rc;
}

static struct kx13x_define_reg_map int_ctrl_map =
{
	.reg = 0x00, /* not used, reg is get using int_reg */
	.mask = KX132_1211_INC1_PW1_MASK | KX132_1211_INC1_IEL1,
	.amount = KX13X_INT_CTRL_AMOUNT,
	.values = {
		{
			._define = KX13X_INT_CTRL_LATCH,
			._reg_bits = 0x00,
		},
		{
			._define = KX13X_INT_CTRL_PULSE_50US_10US,
			._reg_bits = KX132_1211_INC1_IEL1,
		},
		{
			._define = KX13X_INT_CTRL_PULSE_1XODR,
			._reg_bits = KX132_1211_INC5_PW2_1XODR | KX132_1211_INC1_IEL1,
		},
		{
			._define = KX13X_INT_CTRL_PULSE_2XODR,
			._reg_bits = KX132_1211_INC5_PW2_2XODR | KX132_1211_INC1_IEL1,
		},
		{
			._define = KX13X_INT_CTRL_PULSE_REALTIME,
			._reg_bits = KX132_1211_INC5_PW2_4XODR | KX132_1211_INC1_IEL1,
		},
	}
};

int kx13x_set_int_ctrl(struct kx13x *dev, uint8_t pin, uint8_t ctrl)
{
	int rc;
	uint8_t reg_bits;

	if (pin < KX13X_INT1_PIN || pin > KX13X_INT2_PIN) {
		return KX13X_RC_INVALID_PARAM;
	}

	rc = kx13x_map_to_reg_bits(&int_ctrl_map, ctrl, &reg_bits);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_reg_bit_pattern(dev, int_reg[pin].ctrl, reg_bits, int_ctrl_map.mask);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

int kx13x_set_int_enabled(struct kx13x *dev, uint8_t pin, uint8_t enable)
{
	int rc;

	if (pin < KX13X_INT1_PIN || pin > KX13X_INT2_PIN) {
		return KX13X_RC_INVALID_PARAM;
	}

	switch(enable) {
	case KX13X_ENABLED:
		rc = kx13x_set_reg_bit(dev, int_reg[pin].ctrl, KX132_1211_INC1_IEN1);
		break;
	case KX13X_DISABLED:
		rc = kx13x_reset_reg_bit(dev, int_reg[pin].ctrl, KX132_1211_INC1_IEN1);
		break;
	default:
		rc = KX13X_RC_INVALID_PARAM;
		break;
	}

	return rc;	
}

int kx13x_set_int_cfg(struct kx13x *dev, uint8_t pin, struct kx13x_interrupt_cfg *cfg)
{
	int rc;

	if (pin < KX13X_INT1_PIN || pin > KX13X_INT2_PIN) {
		return KX13X_RC_INVALID_PARAM;
	}

	rc = kx13x_set_int_route(dev, pin, cfg->routing);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	rc = kx13x_set_int_level(dev, pin, cfg->level);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_int_ctrl(dev, pin, cfg->ctrl);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	rc = kx13x_set_int_enabled(dev, pin, cfg->enable);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}

int kx13x_get_int_status(struct kx13x *dev, uint8_t *status)
{
	int rc;
	rc = kx13x_read_reg_byte(dev, KX132_1211_STATUS_REG, status);
	return rc;
}

int kx13x_get_int_ins123(struct kx13x *dev, uint8_t *ins123)
{
	int rc;
	rc = kx13x_read_reg(dev, KX132_1211_INS1, ins123, 3);
	return rc;
}

/* */
int kx13x_release_int(struct kx13x *dev)
{
	int rc;
	uint8_t dummy;

	rc = kx13x_read_reg_byte(dev, KX132_1211_INT_REL, &dummy);

	return rc;
}

/* */
int kx13x_reset(struct kx13x *dev)
{
	int rc;

	rc = kx13x_set_reg_bit(dev, KX132_1211_CNTL2, KX132_1211_CNTL2_SRST);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	(void)kx13x_platform_delay_ms(dev->plat, 10);

	return KX13X_RC_OK;
}

/* */
int kx13x_verify_who_am_i_id(struct kx13x *dev, uint8_t* wai_id)
{
	struct kx13x_sensor_info *sensor;
	int rc;
	uint8_t reg_val;
	
	rc = kx13x_read_reg_byte(dev, KX132_1211_WHO_AM_I, &reg_val);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	
	/* check if sensor is supported */	
	sensor = kx13x_sensors_info_is_supported(reg_val);
	if (sensor) {
		KX13X_TRACE_STR_1(dev, "kx13x sensor supported type %d\n", sensor->type);
		*wai_id = sensor->wai_id;
	} else {
		rc = KX13X_RC_NOT_SUPPORTED;
	}

	return rc;
}

/* */
int kx13x_init(struct kx13x *dev, struct platform *plat)
{
	int rc;
	uint8_t wai_id = 0;

	/* platform data */
	dev->plat = plat;

	KX13X_TRACE_STR(dev, "kx13x_init\n");

	rc = kx13x_verify_who_am_i_id(dev, &wai_id);
	if (rc != KX13X_RC_OK) {
		return rc;
	}
	dev->wai_id = wai_id;

	KX13X_TRACE_STR_1(dev, "kx13x wai_id %d\n", dev->wai_id);

	rc = kx13x_reset(dev);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	/* set default values */
	{
		struct kx13x_sensor_info *sensor = NULL;
		/* get sensor info */	
		sensor = kx13x_sensors_info_is_supported(dev->wai_id);
		if (sensor == NULL) {
			return KX13X_RC_ERR;
		}
		dev->granges = sensor->granges;

		if (dev->granges & KX13X_GRANGE_64G) {
			dev->gsens = KX13X_GRANGE_TO_GSENS(KX13X_GRANGE_16G);
		} else {
			dev->gsens = KX13X_GRANGE_TO_GSENS(KX13X_GRANGE_2G);
		}
	}
		
	KX13X_TRACE_STR(dev, "kx13x_init exit\n");
	
	return KX13X_RC_OK;	
}

char* kx13x_get_name(struct kx13x *dev)
{
	struct kx13x_sensor_info *sensor = NULL;

	/* get sensor info */	
	sensor = kx13x_sensors_info_is_supported(dev->wai_id);
	if (sensor) {
		return sensor->name;
	}

	return NULL;
}

int kx13x_set_config(struct kx13x *dev, struct kx13x_cfg *cfg)
{
	int rc;

	if (cfg->accel) {
		rc = kx13x_set_accel_cfg(dev, cfg->accel);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}

	if (cfg->wu_bts) {
		rc = kx13x_set_wu_bts_cfg(dev, cfg->wu_bts);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}
	
	if (cfg->adp) {
		rc = kx13x_set_adp_cfg(dev, cfg->adp);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}

	if (cfg->int1) {
		rc = kx13x_set_int_cfg(dev, KX13X_INT1_PIN, cfg->int1);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}
	
	if (cfg->int2) {
		rc = kx13x_set_int_cfg(dev, KX13X_INT2_PIN, cfg->int2);
		if (rc != KX13X_RC_OK) {
			return rc;
		}
	}

	rc = kx13x_set_oper_mode(dev, cfg->oper_mode);
	if (rc != KX13X_RC_OK) {
		return rc;
	}

	return KX13X_RC_OK;
}
