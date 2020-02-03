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

#ifndef __KX132_1211_REGISTERS_H__
#define __KX132_1211_REGISTERS_H__
/* registers */
#define KX132_1211_MAN_ID 0x00
#define KX132_1211_PART_ID 0x01
// ADP accelerometer output x.
#define KX132_1211_XADP_L 0x02
// msb
#define KX132_1211_XADP_H 0x03
// ADP accelerometer output y
#define KX132_1211_YADP_L 0x04
// msb
#define KX132_1211_YADP_H 0x05
// ADP accelerometer output z
#define KX132_1211_ZADP_L 0x06
// msb
#define KX132_1211_ZADP_H 0x07
// Accelerometer output register x
#define KX132_1211_XOUT_L 0x08
// msb
#define KX132_1211_XOUT_H 0x09
// Accelerometeroutput register y
#define KX132_1211_YOUT_L 0x0A
// msb
#define KX132_1211_YOUT_H 0x0B
// Accelerometer output register z
#define KX132_1211_ZOUT_L 0x0C
// msb
#define KX132_1211_ZOUT_H 0x0D
// The Command Test Response (COTR) register is used to verify proper integrated circuit functionality.
#define KX132_1211_COTR 0x12
// This register can be used for supplier recognition
#define KX132_1211_WHO_AM_I 0x13
// Current Tilt Position Register.
#define KX132_1211_TSCP 0x14
// Previous Tilt Position Register.
#define KX132_1211_TSPP 0x15
// This register contains the tap/double tap axis specific interrupts. Data is updated at the ODR settings determined by OTDT<2:0> in CNTL3.
#define KX132_1211_INS1 0x16
// This register tells which function caused an interrupt.
#define KX132_1211_INS2 0x17
// This register reports the axis and direction of detected motion that triggered the wakeup interrupt.
#define KX132_1211_INS3 0x18
// This register reports the status of the interrupt.
#define KX132_1211_STATUS_REG 0x19
#define KX132_1211_INT_REL 0x1A
// Control register 1. Read/write control register that controls the main feature set.
#define KX132_1211_CNTL1 0x1B
// Control register 2. Read/write control register that primarily controls tilt position state enabling.
#define KX132_1211_CNTL2 0x1C
// Control register 3. Read/write control register that provides control of the Output Data Rate (ODR) for Tilt, Tap, and Wake-up engines.
#define KX132_1211_CNTL3 0x1D
// Control register 4. Read/write control register that provides more feature set control.
#define KX132_1211_CNTL4 0x1E
// Control register 5. Read/write control register that provides more feature set control. Note that to properly change the value of this register, the PC1 bit in CNTL1 must first be set to "0".
#define KX132_1211_CNTL5 0x1F
// Control register 6. Read/write control register that provides more feature set control.
#define KX132_1211_CNTL6 0x20
// Output data control register that configures the acceleration outputs.
#define KX132_1211_ODCNTL 0x21
// Interrupt control 1. This register controls the settings for the physical interrupt pin INT1
#define KX132_1211_INC1 0x22
// Interrupt control 2. This register controls which axis and direction of detected motion can cause an interrupt.
#define KX132_1211_INC2 0x23
// Interrupt control 3. This register controls which axis and direction of tap/double tap can cause an interrupt.
#define KX132_1211_INC3 0x24
// Interrupt control 4. This register controls routing of an interrupt reporting to physical interrupt pin INT1
#define KX132_1211_INC4 0x25
// Interrupt control 5. This register controls the settings for the physical interrupt pin INT2.
#define KX132_1211_INC5 0x26
// Interrupt control 6. This register controls routing of interrupt reporting to physical interrupt pin INT2
#define KX132_1211_INC6 0x27
#define KX132_1211_TILT_TIMER 0x29
// Tap/Double Tap report control.
#define KX132_1211_TDTRC 0x2A
#define KX132_1211_TDTC 0x2B
#define KX132_1211_TTH 0x2C
#define KX132_1211_TTL 0x2D
// This register contains counter information for the detection of any tap event
#define KX132_1211_FTD 0x2E
#define KX132_1211_STD 0x2F
#define KX132_1211_TLT 0x30
#define KX132_1211_TWS 0x31
#define KX132_1211_FFTH 0x32
#define KX132_1211_FFC 0x33
// Freefall interrupt control.
#define KX132_1211_FFCNTL 0x34
#define KX132_1211_TILT_ANGLE_LL 0x37
#define KX132_1211_TILT_ANGLE_HL 0x38
#define KX132_1211_HYST_SET 0x39
// Low Power Control
#define KX132_1211_LP_CNTL1 0x3A
// Low Power Control 2: The advanced low power control setting reduces the power consumption
#define KX132_1211_LP_CNTL2 0x3B
// Wake-up engine thresholds.
#define KX132_1211_WUFTH 0x49
// Wake-up/Back-to-sleep engine thresholds.
#define KX132_1211_BTSWUFTH 0x4A
// Back-to-sleep engine thresholds.
#define KX132_1211_BTSTH 0x4B
#define KX132_1211_BTSC 0x4C
#define KX132_1211_WUFC 0x4D
// Self-Test Enable register:
#define KX132_1211_SELF_TEST 0x5D
// Sample Threshold - determines the number of samples that will trigger a watermark interrupt or will be saved prior to a trigger event. When BRES=1, the maximum number of samples is 86; when BRES=0, the maximum number of samples is 171. The minimum number of samples must be greater than or equal to 2.
#define KX132_1211_BUF_CNTL1 0x5E
// Read/write control register that controls sample buffer operation
#define KX132_1211_BUF_CNTL2 0x5F
// These register reports the status of the sample buffer. Note that BUF_STATUS_1 and BUF_STATUS_2 registers may have a delay of up to 1usec to update the sample level after a buffer read.
#define KX132_1211_BUF_STATUS_1 0x60
// This register reports the status of the sample buffer trigger function
#define KX132_1211_BUF_STATUS_2 0x61
#define KX132_1211_BUF_CLEAR 0x62
#define KX132_1211_BUF_READ 0x63
// Advanced Data Path (ADP) Output Control register 1.
#define KX132_1211_ADP_CNTL1 0x64
// Advanced Data Path (ADP) Control register 2.
#define KX132_1211_ADP_CNTL2 0x65
// Advanced Data Path (ADP) Control register 3.
#define KX132_1211_ADP_CNTL3 0x66
// Advanced Data Path (ADP) Control registers 4, 5 and 6.
#define KX132_1211_ADP_CNTL4 0x67
#define KX132_1211_ADP_CNTL5 0x68
#define KX132_1211_ADP_CNTL6 0x69
// Advanced Data Path (ADP) Control registers 7, 8 and 9.
#define KX132_1211_ADP_CNTL7 0x6A
#define KX132_1211_ADP_CNTL8 0x6B
#define KX132_1211_ADP_CNTL9 0x6C
// Advanced Data Path (ADP) Control register 10.
#define KX132_1211_ADP_CNTL10 0x6D
// Advanced Data Path (ADP) Control register 11.
#define KX132_1211_ADP_CNTL11 0x6E
// Advanced Data Path (ADP) Control registers 12 and 13.
#define KX132_1211_ADP_CNTL12 0x6F
#define KX132_1211_ADP_CNTL13 0x70
#define KX132_1211_ADP_CNTL14 0x71
#define KX132_1211_ADP_CNTL15 0x72
#define KX132_1211_ADP_CNTL16 0x73
#define KX132_1211_ADP_CNTL17 0x74
// ADP Output Control register 18.
#define KX132_1211_ADP_CNTL18 0x75
// ADP Output Control register 19.
#define KX132_1211_ADP_CNTL19 0x76
/* registers bits */
// before set
#define KX132_1211_COTR_DCSTR_BEFORE (0x55 << 0)
// after set
#define KX132_1211_COTR_DCSTR_AFTER (0xAA << 0)
// WAI value for KX132-1211
#define KX132_1211_WHO_AM_I_WAI_ID (0x3D << 0)
// Left state X' negative (x-)
#define KX132_1211_TSCP_LE (0x01 << 5)
// Right state X' positive (x+)
#define KX132_1211_TSCP_RI (0x01 << 4)
// Down state Y' negative (y-)
#define KX132_1211_TSCP_DO (0x01 << 3)
// Up state Y' positive (y+)
#define KX132_1211_TSCP_UP (0x01 << 2)
// Face Down state Z negative (z-)
#define KX132_1211_TSCP_FD (0x01 << 1)
// Face Up Z positive (z+)
#define KX132_1211_TSCP_FU (0x01 << 0)
// Left state X' negative (x-)
#define KX132_1211_TSPP_LE (0x01 << 5)
// Right state X' positive (x+)
#define KX132_1211_TSPP_RI (0x01 << 4)
// Down state Y' negative (y-)
#define KX132_1211_TSPP_DO (0x01 << 3)
// Up state Y' positive (y+)
#define KX132_1211_TSPP_UP (0x01 << 2)
// Face Down state Z negative (z-)
#define KX132_1211_TSPP_FD (0x01 << 1)
// Face Up Z positive (z+)
#define KX132_1211_TSPP_FU (0x01 << 0)
// X' negative (x-)
#define KX132_1211_INS1_TLE (0x01 << 5)
// X' positive (x+)
#define KX132_1211_INS1_TRI (0x01 << 4)
// Y' negative (y-)
#define KX132_1211_INS1_TDO (0x01 << 3)
// Y' positive (y+)
#define KX132_1211_INS1_TUP (0x01 << 2)
// Z  negative (z-)
#define KX132_1211_INS1_TFD (0x01 << 1)
// Z  positive (z+)
#define KX132_1211_INS1_TFU (0x01 << 0)
// Free fall Status (FFS) bit. This bit is cleared when the interrupt latch release register (INT_REL) is read.
#define KX132_1211_INS2_FFS (0x01 << 7)
// Buffer Full Interrupt (BFI) bit indicates that buffer has been filled. This bit is automatically cleared when at least one sample from the buffer is read.
#define KX132_1211_INS2_BFI (0x01 << 6)
// Watermark Interrupt bit indicates that user-defined buffer's sample threshold (watermark) has been exceeded when in FIFO or Stream modes. Not used in Trigger mode. This bit is automatically cleared when buffer is read and the content is below the watermark.
#define KX132_1211_INS2_WMI (0x01 << 5)
// Data Ready (DRDY) interrupt bit indicates that new acceleration data is available in output data registers 0x08 to 0x0D. This bit is cleared when acceleration data is read or the interrupt latch release register (INT_REL) is read.
#define KX132_1211_INS2_DRDY (0x01 << 4)
// 00 = no tap
#define KX132_1211_INS2_TDTS_NOTAP (0x00 << 2)
// 01 = single tap
#define KX132_1211_INS2_TDTS_SINGLE (0x01 << 2)
// 10 = double tap
#define KX132_1211_INS2_TDTS_DOUBLE (0x02 << 2)
// 11 = does not exist
#define KX132_1211_INS2_TDTS_NA (0x03 << 2)
// Tilt Position Status bit
#define KX132_1211_INS2_TPS (0x01 << 0)
// Wake up interrupt. This bit is cleared when the interrupt latch release register (INT_REL) is read. WUFS = 1 - Motion is above wake up threshold, WUFS = 0 - Motion is below wake up threshold
#define KX132_1211_INS3_WUFS (0x01 << 7)
// Back to sleep interrupt. This bit is cleared when the interrupt latch release register (INT_REL) is read. BTS = 1 - Motion is below back to sleep threshold, BTS = 0 - Motion is above back to sleep threshold
#define KX132_1211_INS3_BTS (0x01 << 6)
// X' negative (x-)
#define KX132_1211_INS3_XNWU (0x01 << 5)
// X' positive (x+)
#define KX132_1211_INS3_XPWU (0x01 << 4)
// Y' negative (y-)
#define KX132_1211_INS3_YNWU (0x01 << 3)
// Y' positive (y+)
#define KX132_1211_INS3_YPWU (0x01 << 2)
// Z  negative (z-)
#define KX132_1211_INS3_ZNWU (0x01 << 1)
// Z  positive (z+)
#define KX132_1211_INS3_ZPWU (0x01 << 0)
// reports the combined (OR) interrupt information according to interrupt setting: 0= no interrupt event, 1= interrupt event has occurred.
#define KX132_1211_STATUS_REG_INT (0x01 << 4)
// reports the wake/back to sleep state; 0 = back-to-sleep state,1 = wake state.
#define KX132_1211_STATUS_REG_WAKE (0x01 << 0)
// controls the operating mode.  0= stand-by mode,  1= operating mode.
#define KX132_1211_CNTL1_PC1 (0x01 << 7)
// controls the resolution of the accelerometer output. RES = 0 - low power, higher noise mode. RES = 1 - higher power, lower noise mode
#define KX132_1211_CNTL1_RES (0x01 << 6)
// enables the data ready engine. DRDYE = 0 - disable, DRDYE = 1 - enable
#define KX132_1211_CNTL1_DRDYE (0x01 << 5)
// 00 = +/- 2g
#define KX132_1211_CNTL1_GSEL_2G (0x00 << 3)
// 01 = +/- 4g
#define KX132_1211_CNTL1_GSEL_4G (0x01 << 3)
// 10 = +/- 8g
#define KX132_1211_CNTL1_GSEL_8G (0x02 << 3)
// 11 = +/- 16g
#define KX132_1211_CNTL1_GSEL_16G (0x03 << 3)
// enables the Tap/Double tap engine. TDTE = 0 - disable, TDTE = 1 - enable
#define KX132_1211_CNTL1_TDTE (0x01 << 2)
// enables the Tilt engine.TPE = 0 - disable, TPE = 1 - enable
#define KX132_1211_CNTL1_TPE (0x01 << 0)
// The Software Reset bit initiates software reset, which performs the RAM reboot routine. This bit will remain 1 until the RAM reboot routine is finished.
#define KX132_1211_CNTL2_SRST (0x01 << 7)
// The Command Test Control bit is used to verify proper ASIC functionality. COTC = 0 - no action, COTC = 1 - sets AA to COTR register, when the COTR register is read, COTC is cleared and STR = 55.
#define KX132_1211_CNTL2_COTC (0x01 << 6)
// Tilt Left state mask
#define KX132_1211_CNTL2_LEM (0x01 << 5)
// Tilt Right state mask
#define KX132_1211_CNTL2_RIM (0x01 << 4)
// Tilt Down state mask
#define KX132_1211_CNTL2_DOM (0x01 << 3)
// Tilt Up state mask
#define KX132_1211_CNTL2_UPM (0x01 << 2)
// Tilt Face Down state mask
#define KX132_1211_CNTL2_FDM (0x01 << 1)
// Tilt Face Up state mask
#define KX132_1211_CNTL2_FUM (0x01 << 0)
// 1.563Hz
#define KX132_1211_CNTL3_OTP_1P563 (0x00 << 6)
// 6.25Hz
#define KX132_1211_CNTL3_OTP_6P25 (0x01 << 6)
// 12.5Hz
#define KX132_1211_CNTL3_OTP_12P5 (0x02 << 6)
// 50Hz
#define KX132_1211_CNTL3_OTP_50 (0x03 << 6)
// 12.5Hz
#define KX132_1211_CNTL3_OTDT_12P5 (0x00 << 3)
// 25Hz
#define KX132_1211_CNTL3_OTDT_25 (0x01 << 3)
// 50Hz
#define KX132_1211_CNTL3_OTDT_50 (0x02 << 3)
// 100Hz
#define KX132_1211_CNTL3_OTDT_100 (0x03 << 3)
// 200Hz
#define KX132_1211_CNTL3_OTDT_200 (0x04 << 3)
// 400Hz
#define KX132_1211_CNTL3_OTDT_400 (0x05 << 3)
// 800Hz
#define KX132_1211_CNTL3_OTDT_800 (0x06 << 3)
// 1600Hz
#define KX132_1211_CNTL3_OTDT_1600 (0x07 << 3)
// 0.781Hz
#define KX132_1211_CNTL3_OWUF_0P781 (0x00 << 0)
// 1.563Hz
#define KX132_1211_CNTL3_OWUF_1P563 (0x01 << 0)
// 3.125Hz
#define KX132_1211_CNTL3_OWUF_3P125 (0x02 << 0)
// 6.25Hz
#define KX132_1211_CNTL3_OWUF_6P25 (0x03 << 0)
// 12.5Hz
#define KX132_1211_CNTL3_OWUF_12P5 (0x04 << 0)
// 25Hz
#define KX132_1211_CNTL3_OWUF_25 (0x05 << 0)
// 50Hz
#define KX132_1211_CNTL3_OWUF_50 (0x06 << 0)
// 100Hz
#define KX132_1211_CNTL3_OWUF_100 (0x07 << 0)
// debounce counter is reset if accelerometer data is below threshold
#define KX132_1211_CNTL4_C_MODE_RESET (0x00 << 7)
// debounce counter is decremented if accelerometer data is below threshold
#define KX132_1211_CNTL4_C_MODE_DECREMENTED (0x01 << 7)
// absolute threshold
#define KX132_1211_CNTL4_TH_MODE_ABSOLUTE (0x00 << 6)
// relative threshold
#define KX132_1211_CNTL4_TH_MODE_RELATIVE (0x01 << 6)
// Wake-Up Function Engine is disabled
#define KX132_1211_CNTL4_WUFE_DISABLED (0x00 << 5)
// Wake-Up Function Engine is enabled
#define KX132_1211_CNTL4_WUFE_ENABLED (0x01 << 5)
// Back-to-Sleep Engine is disabled
#define KX132_1211_CNTL4_BTSE_DISABLED (0x00 << 4)
// Back-to-Sleep Engine is enabled
#define KX132_1211_CNTL4_BTSE_ENABLED (0x01 << 4)
// standard operation
#define KX132_1211_CNTL4_PR_MODE_STANDARD (0x00 << 3)
// reject pulse-like motion only in case motion detection in positive and negative directions is enabled (XPWUE and XNWUE bits are set to 1 in INC2 register).
#define KX132_1211_CNTL4_PR_MODE_REJECTED (0x01 << 3)
// 0.781Hz
#define KX132_1211_CNTL4_OBTS_0P781 (0x00 << 0)
// 1.5623Hz
#define KX132_1211_CNTL4_OBTS_1P563 (0x01 << 0)
// 3.125Hz
#define KX132_1211_CNTL4_OBTS_3P125 (0x02 << 0)
// 6.25Hz
#define KX132_1211_CNTL4_OBTS_6P25 (0x03 << 0)
// 12.5Hz
#define KX132_1211_CNTL4_OBTS_12P5 (0x04 << 0)
// 25Hz
#define KX132_1211_CNTL4_OBTS_25 (0x05 << 0)
// 50Hz
#define KX132_1211_CNTL4_OBTS_50 (0x06 << 0)
// 100Hz
#define KX132_1211_CNTL4_OBTS_100 (0x07 << 0)
// ADP disabled
#define KX132_1211_CNTL5_ADPE_DISABLED (0x00 << 4)
// ADP enabled
#define KX132_1211_CNTL5_ADPE_ENABLED (0x01 << 4)
// manual wake-sleep engine overwrite.MAN_WAKE = 0 - default, MAN_WAKE = 1 - forces wake state (bit is self-cleared)
#define KX132_1211_CNTL5_MAN_WAKE (0x01 << 1)
// manual wake-sleep engine overwrite. MAN_SLEEP = 0 - default, MAN_SLEEP = 1 - forces sleep state (bit is self-cleared)
#define KX132_1211_CNTL5_MAN_SLEEP (0x01 << 0)
// I2C auto release function is disabled
#define KX132_1211_CNTL6_I2C_ALE_DISABLED (0x00 << 7)
// I2C auto release function is enabled
#define KX132_1211_CNTL6_I2C_ALE_ENABLED (0x01 << 7)
// 0.5sec
#define KX132_1211_CNTL6_I2C_ALC_0P5 (0x00 << 0)
// 1.0sec
#define KX132_1211_CNTL6_I2C_ALC_1P0 (0x01 << 0)
// 2.0sec
#define KX132_1211_CNTL6_I2C_ALC_2P0 (0x02 << 0)
// 4.0sec
#define KX132_1211_CNTL6_I2C_ALC_4P0 (0x03 << 0)
// IIR filter is not bypassed
#define KX132_1211_ODCNTL_IIR_BYPASS_NOT_BYPASSED (0x00 << 7)
// IIR filter is bypassed
#define KX132_1211_ODCNTL_IIR_BYPASS_BYPASSED (0x01 << 7)
// IIR filter corner frequency set to ODR/9 (default)
#define KX132_1211_ODCNTL_LPRO_ODR_9 (0x00 << 6)
// IIR filter corner frequency set to ODR/2
#define KX132_1211_ODCNTL_LPRO_ODR_2 (0x01 << 6)
// Fast Start is disabled
#define KX132_1211_ODCNTL_FSTUP_DISABLED (0x00 << 5)
// Fast Start is enabled
#define KX132_1211_ODCNTL_FSTUP_ENABLED (0x01 << 5)
// 0.781Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_0P781 (0x00 << 0)
// 1.563Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_1P563 (0x01 << 0)
// 3.125Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_3P125 (0x02 << 0)
// 6.25Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_6P25 (0x03 << 0)
// 12.5Hz Low power mode available
#define KX132_1211_ODCNTL_OSA_12P5 (0x04 << 0)
// 25Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_25 (0x05 << 0)
// 50Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_50 (0x06 << 0)
// 100Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_100 (0x07 << 0)
// 200Hz  Low power mode available
#define KX132_1211_ODCNTL_OSA_200 (0x08 << 0)
// 400Hz
#define KX132_1211_ODCNTL_OSA_400 (0x09 << 0)
// 800Hz
#define KX132_1211_ODCNTL_OSA_800 (0x0A << 0)
// 1600Hz
#define KX132_1211_ODCNTL_OSA_1600 (0x0B << 0)
// 3200Hz
#define KX132_1211_ODCNTL_OSA_3200 (0x0C << 0)
// 6400Hz
#define KX132_1211_ODCNTL_OSA_6400 (0x0D << 0)
// 12800Hz
#define KX132_1211_ODCNTL_OSA_12800 (0x0E << 0)
// 25600Hz
#define KX132_1211_ODCNTL_OSA_25600 (0x0F << 0)
// 50us(10us when OSA>1600Hz)
#define KX132_1211_INC1_PW1_50US_10US (0x00 << 6)
// width 1*OSA period
#define KX132_1211_INC1_PW1_1XOSA (0x01 << 6)
// width 2*OSA period
#define KX132_1211_INC1_PW1_2XOSA (0x02 << 6)
// width 4*OSA period
#define KX132_1211_INC1_PW1_4XOSA (0x03 << 6)
// enables/disables the physical interrupt pin 1. 0=disable, 1=enable.
#define KX132_1211_INC1_IEN1 (0x01 << 5)
// Interrupt active level control for interrupt pin 1, 0=active low, 1=active high.
#define KX132_1211_INC1_IEA1 (0x01 << 4)
// Interrupt latch control for interrupt pin 1, 0=latched, 1=one pulse
#define KX132_1211_INC1_IEL1 (0x01 << 3)
// sets the polarity of Self Test. STPOL = 0 - Negative, STPOL = 1 - Positive
#define KX132_1211_INC1_STPOL (0x01 << 1)
// sets the 3-wire SPI interface. SPI3E = 0 - disabled, SPI3E = 1 - enabled
#define KX132_1211_INC1_SPI3E (0x01 << 0)
// 0=Or combination of selected directions
#define KX132_1211_INC2_AOI_OR (0x00 << 6)
// 1=And combination of selected axes
#define KX132_1211_INC2_AOI_AND (0x01 << 6)
// x negative (x-) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_XNWUE (0x01 << 5)
// x positive (x+) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_XPWUE (0x01 << 4)
// y negative (y-) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_YNWUE (0x01 << 3)
// y positive (y+) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_YPWUE (0x01 << 2)
// z negative (z-) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_ZNWUE (0x01 << 1)
// z positive (z+) mask for WUF, 0=disable, 1=enable.
#define KX132_1211_INC2_ZPWUE (0x01 << 0)
// x negative (x-): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TLEM (0x01 << 5)
// x positive (x+): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TRIM (0x01 << 4)
// y negative (y-): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TDOM (0x01 << 3)
// y positive (y+): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TUPM (0x01 << 2)
// z negative (z-): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TFDM (0x01 << 1)
// z positive (z+): 0 = disabled, 1 = enabled
#define KX132_1211_INC3_TFUM (0x01 << 0)
// Free fall interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_FFI1 (0x01 << 7)
// Buffer full interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_BFI1 (0x01 << 6)
// Watermark interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_WMI1 (0x01 << 5)
// Data ready interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_DRDYI1 (0x01 << 4)
// Back to sleep interrupt reported in interrupt pin 1
#define KX132_1211_INC4_BTSI1 (0x01 << 3)
// Tap/Double Tap interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_TDTI1 (0x01 << 2)
// Wake Up (motion detect) interrupt reported pn physical interrupt pin 1, 0=disable, 1=enable (and IEN1=1).
#define KX132_1211_INC4_WUFI1 (0x01 << 1)
// Tilt position interrupt reported on physical interrupt pin 1, 0=disable, 1=enable.
#define KX132_1211_INC4_TPI1 (0x01 << 0)
// 50us(10us when OSA>1600Hz)
#define KX132_1211_INC5_PW2_50US_10US (0x00 << 6)
// width 1*OSAperiod
#define KX132_1211_INC5_PW2_1XODR (0x01 << 6)
// width 2*OSA period
#define KX132_1211_INC5_PW2_2XODR (0x02 << 6)
// width 4*OSA period
#define KX132_1211_INC5_PW2_4XODR (0x03 << 6)
// enable/disable physical interrupt pin 2, 0=disable, 1=enable.
#define KX132_1211_INC5_IEN2 (0x01 << 5)
// Interrupt active level control for interrupt pin 2, 0=active low, 1=active high.
#define KX132_1211_INC5_IEA2 (0x01 << 4)
// Interrupt latch control for interrupt pin 2, 0=latched, 1=one pulse
#define KX132_1211_INC5_IEL2 (0x01 << 3)
// Latched interrupt source information(INS1-INS3) is cleared and physical interrupt-1 latched pin is changed to its inactive state at pulse interrupt-1 trailing edge. Note: WMI, BFI, and STPWMI are not auto-cleared by a pulse interrupt trailing edge. ACLR2 = 0 - disable, ACLR2 = 1 - enable
#define KX132_1211_INC5_ACLR2 (0x01 << 1)
// Latched interrupt source information(INS1-INS3) is cleared and physical interrupt-1 latched pin is changed to its inactive state at pulse interrupt-2 trailing edge. Note: WMI, BFI, and STPWMI are not auto-cleared by a pulse interrupt trailing edge. ACLR2 = 0 - disable, ACLR2 = 1 - enable
#define KX132_1211_INC5_ACLR1 (0x01 << 0)
// Free fall interrupt reported on physical interrupt pin INT2. FFI2 = 0 - disable, FFI2 = 1 - enable
#define KX132_1211_INC6_FFI2 (0x01 << 7)
// Buffer full interrupt reported on physical interrupt pin INT2. BF2 = 0 - disable, BF2 = 1 - enable
#define KX132_1211_INC6_BFI2 (0x01 << 6)
// Watermark interrupt reported on physical interrupt pin INT2. WMI2 = 0 - disable, WMI2 = 1 - enable
#define KX132_1211_INC6_WMI2 (0x01 << 5)
// Data ready interrupt reported on physical interrupt pin INT2. DRDYI2 = 0 - disable, DRDYI2 = 1 - enable
#define KX132_1211_INC6_DRDYI2 (0x01 << 4)
// Back to sleep interrupt reported on physical interrupt pin INT2. BTSI2 = 0 - disable, BTSI2 = 1 - enable
#define KX132_1211_INC6_BTSI2 (0x01 << 3)
// Tap/Double Tap interrupt reported on physical interrupt pin 2, 0=disable, 1=enable.
#define KX132_1211_INC6_TDTI2 (0x01 << 2)
// Wake-Up (motion detect) interrupt reported on physical interrupt pin INT2. WUFI2 = 0 - disable, WUFI2 = 1 - enable
#define KX132_1211_INC6_WUFI2 (0x01 << 1)
// Tilt position interrupt reported on physical interrupt pin INT. TPI2 = 0 - disable, TPI2 = 1 - enable
#define KX132_1211_INC6_TPI2 (0x01 << 0)
// enables/disables the double tap interrupt. DTRE = 0 - do not update INS1 or DTDS if double tap occurs, DTRE = 1 - update INS1 and DTDS in INS2 with double tap events
#define KX132_1211_TDTRC_DTRE (0x01 << 1)
// enables/disables single tap interrupt. STRE = 0 - do not update INS1 or DTDS if single tap occurs, STRE = 1 - update INS1 and DTDS in INS2 single tap events
#define KX132_1211_TDTRC_STRE (0x01 << 0)
// Free fall engine enable. FFIE = 0 - disable, FFIE = 1 - enable
#define KX132_1211_FFCNTL_FFIE (0x01 << 7)
// Free fall interrupt latch/un-latch control. ULMODE = 0 - latched, ULMODE = 1 - unlatched
#define KX132_1211_FFCNTL_ULMODE (0x01 << 6)
// no delay
#define KX132_1211_FFCNTL_FFDC_NO_DELAY (0x00 << 4)
// 1sec
#define KX132_1211_FFCNTL_FFDC_1 (0x01 << 4)
// 2sec
#define KX132_1211_FFCNTL_FFDC_2 (0x02 << 4)
// 4sec
#define KX132_1211_FFCNTL_FFDC_4 (0x03 << 4)
// Debounce methodology control. DCRM = 0 - count up/down, DCRM = 1 - count up/reset
#define KX132_1211_FFCNTL_DCRM (0x01 << 3)
// 12.5Hz
#define KX132_1211_FFCNTL_OFFI_12P5 (0x00 << 0)
// 25Hz
#define KX132_1211_FFCNTL_OFFI_25 (0x01 << 0)
// 50Hz
#define KX132_1211_FFCNTL_OFFI_50 (0x02 << 0)
// 100Hz
#define KX132_1211_FFCNTL_OFFI_100 (0x03 << 0)
// 200Hz
#define KX132_1211_FFCNTL_OFFI_200 (0x04 << 0)
// 400Hz
#define KX132_1211_FFCNTL_OFFI_400 (0x05 << 0)
// 800Hz
#define KX132_1211_FFCNTL_OFFI_800 (0x06 << 0)
// 1600Hz
#define KX132_1211_FFCNTL_OFFI_1600 (0x07 << 0)
// No Averaging
#define KX132_1211_LP_CNTL1_AVC_NO_AVG (0x00 << 4)
// 2 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_2_SAMPLE_AVG (0x01 << 4)
// 4 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_4_SAMPLE_AVG (0x02 << 4)
// 8 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_8_SAMPLE_AVG (0x03 << 4)
// 16 Samples Averaged (default)
#define KX132_1211_LP_CNTL1_AVC_16_SAMPLE_AVG (0x04 << 4)
// 32 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_32_SAMPLE_AVG (0x05 << 4)
// 64 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_64_SAMPLE_AVG (0x06 << 4)
// 128 Samples Averaged
#define KX132_1211_LP_CNTL1_AVC_128_SAMPLE_AVG (0x07 << 4)
// Digital power shut-off select
#define KX132_1211_LP_CNTL2_LPSTPSEL (0x01 << 0)
// Self test off
#define KX132_1211_SELF_TEST_MEMS_TEST_ST_OFF (0x00 << 0)
// Self test on
#define KX132_1211_SELF_TEST_MEMS_TEST_ST_ON (0xCA << 0)
// controls activation of the sample buffer. BUFE = 0 - sample buffer inactive, BUFE = 1 - sample buffer active
#define KX132_1211_BUF_CNTL2_BUFE (0x01 << 7)
// determines the resolution of the acceleration data samples collected by the sample buffer. BRES = 0 - 8-bit samples are accumulated in the buffer, BRES = 1 - 16-bit samples are accumulated in the buffer
#define KX132_1211_BUF_CNTL2_BRES (0x01 << 6)
// buffer full interrupt enable bit. BFIE = 0 - buffer full interrupt is disabled, BFIE = 1 - buffer full interrupt is enabled and updated in INS2
#define KX132_1211_BUF_CNTL2_BFIE (0x01 << 5)
// The buffer collects 681 sets of 8-bit low resolution values or 339 sets of 16-bit high resolution values and then stops collecting data, collecting new data only when the buffer is not full
#define KX132_1211_BUF_CNTL2_BM_FIFO (0x00 << 0)
// The buffer holds the last 681 sets of 8-bit low resolution values or 339 sets of 16-bit high resolution values. Once the buffer is full, the oldest data is discarded to make room for newer data.
#define KX132_1211_BUF_CNTL2_BM_STREAM (0x01 << 0)
// When a trigger event occurs, the buffer holds the last data set of SMP[9:0] samples before the trigger event and then continues to collect data until full. New data is collected only when the buffer is not full.
#define KX132_1211_BUF_CNTL2_BM_TRIGGER (0x02 << 0)
// Not applicable
#define KX132_1211_BUF_CNTL2_BM_NA (0x03 << 0)
// reports the status of the buffer's trigger function if this mode has been selected
#define KX132_1211_BUF_STATUS_2_BUF_TRIG (0x01 << 7)
// 2 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_2_SAMPLE_AVG (0x00 << 4)
// 4 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_4_SAMPLE_AVG (0x01 << 4)
// 8 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_8_SAMPLE_AVG (0x02 << 4)
// 16 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_16_SAMPLE_AVG (0x03 << 4)
// 32 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_32_SAMPLE_AVG (0x04 << 4)
// 64 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_64_SAMPLE_AVG (0x05 << 4)
// 128 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_128_SAMPLE_AVG (0x06 << 4)
// 256 Samples Averaged
#define KX132_1211_ADP_CNTL1_RMS_AVC_256_SAMPLE_AVG (0x07 << 4)
// 0.781Hz
#define KX132_1211_ADP_CNTL1_OADP_0P781 (0x00 << 0)
// 1.563Hz
#define KX132_1211_ADP_CNTL1_OADP_1P563 (0x01 << 0)
// 3.125Hz
#define KX132_1211_ADP_CNTL1_OADP_3P125 (0x02 << 0)
// 6.25Hz
#define KX132_1211_ADP_CNTL1_OADP_6P25 (0x03 << 0)
// 12.5Hz
#define KX132_1211_ADP_CNTL1_OADP_12P5 (0x04 << 0)
// 25Hz
#define KX132_1211_ADP_CNTL1_OADP_25 (0x05 << 0)
// 50Hz
#define KX132_1211_ADP_CNTL1_OADP_50 (0x06 << 0)
// 100Hz
#define KX132_1211_ADP_CNTL1_OADP_100 (0x07 << 0)
// 200Hz
#define KX132_1211_ADP_CNTL1_OADP_200 (0x08 << 0)
// 400Hz
#define KX132_1211_ADP_CNTL1_OADP_400 (0x09 << 0)
// 800Hz
#define KX132_1211_ADP_CNTL1_OADP_800 (0x0A << 0)
// 1600Hz
#define KX132_1211_ADP_CNTL1_OADP_1600 (0x0B << 0)
// 3200Hz
#define KX132_1211_ADP_CNTL1_OADP_3200 (0x0C << 0)
// 6400Hz
#define KX132_1211_ADP_CNTL1_OADP_6400 (0x0D << 0)
// 12800Hz
#define KX132_1211_ADP_CNTL1_OADP_12800 (0x0E << 0)
// 25600Hz
#define KX132_1211_ADP_CNTL1_OADP_25600 (0x0F << 0)
// Select data to be routed to the sample buffer
#define KX132_1211_ADP_CNTL2_ADP_BUF_SEL (0x01 << 7)
// Input select for the Wake-up/Back-to-Sleep engines
#define KX132_1211_ADP_CNTL2_ADP_WB_ISEL (0x01 << 6)
// Select data out to the WUF/BTS engines.
#define KX132_1211_ADP_CNTL2_RMS_WB_OSEL (0x01 << 5)
// Advanced Data Path Filter-2 bypass control
#define KX132_1211_ADP_CNTL2_ADP_FLT2_BYP (0x01 << 4)
// Advanced Data Path Filter-1 bypass control
#define KX132_1211_ADP_CNTL2_ADP_FLT1_BYP (0x01 << 3)
// Select data out to XADP, YADP, and ZADP registers.
#define KX132_1211_ADP_CNTL2_ADP_RMS_OSEL (0x01 << 1)
// Filter-2 High-pass enable. 0 - Filter-2 is set to Low-pass filter. 1 - Filter-2 is set to High-pass filter
#define KX132_1211_ADP_CNTL2_ADP_F2_HP (0x01 << 0)
// ADP filter-1 output scale shift value
#define KX132_1211_ADP_CNTL11_ADP_F1_OSH (0x01 << 7)
 /*registers bit masks */
#define KX132_1211_MAN_ID_MANID_MASK 0xFF
#define KX132_1211_PART_ID_PARTID_MASK 0xFF
// Command Test Responses
#define KX132_1211_COTR_DCSTR_MASK 0xFF
// WAI value
#define KX132_1211_WHO_AM_I_WAI_MASK 0xFF
// Tap/Double-Tap Status bit. This bit is cleared when the interrupt latch release register (INT_REL) is read
#define KX132_1211_INS2_TDTS_MASK 0x0C
// G-range Select (GSEL) bits select the acceleration range of the accelerometer outputs. This range is also called a full-scale range of the accelerometer.
#define KX132_1211_CNTL1_GSEL_MASK 0x18
// Tilt Position (OTP) sets the output data rate for the Tilt Position function
#define KX132_1211_CNTL3_OTP_MASK 0xC0
// Tap/Double-TapTM (OTDT) sets the output data rate for the Directional-Tap function
#define KX132_1211_CNTL3_OTDT_MASK 0x38
// Wake-Up Function (OWUF) sets the output data rate
#define KX132_1211_CNTL3_OWUF_MASK 0x07
// defines debounce counter clear mode
#define KX132_1211_CNTL4_C_MODE_MASK 0x80
// defines wake / back-to-sleep threshold mode. TH_MODE = 0 - absolute threshold, TH_MODE = 1 - relative threshold
#define KX132_1211_CNTL4_TH_MODE_MASK 0x40
// Wake-Up Function Engine enable bit
#define KX132_1211_CNTL4_WUFE_MASK 0x20
// Back-to-Sleep Engine enable bit.
#define KX132_1211_CNTL4_BTSE_MASK 0x10
// defines Pulse Reject mode
#define KX132_1211_CNTL4_PR_MODE_MASK 0x08
// sets the output data rate at which the back-to-sleep (motion detection) performs its function during wake state
#define KX132_1211_CNTL4_OBTS_MASK 0x07
// Advanced Data Path (ADP) enable. ADPE = 0 - Advanced Data Path is disabled.  ADPE = 1 - Advanced Data Path is enabled. Outputs are available in XADP, YADP, ZADP registers.
#define KX132_1211_CNTL5_ADPE_MASK 0x10
// enables the I2C auto release function. I2C_ALE = 0 - disabled, I2C_ALE = 1 - enabled
#define KX132_1211_CNTL6_I2C_ALE_MASK 0x80
// I2C auto release function counter select
#define KX132_1211_CNTL6_I2C_ALC_MASK 0x03
// IIR Filter Bypass mode enable bit
#define KX132_1211_ODCNTL_IIR_BYPASS_MASK 0x80
// Low-Pass filter roll off control. LPRO = 0 - filter corner frequency set to ODR/9, LPRO = 1 - filter corner frequency set to ODR/2
#define KX132_1211_ODCNTL_LPRO_MASK 0x40
// Fast Start Up Enable bit.
#define KX132_1211_ODCNTL_FSTUP_MASK 0x20
// Acceleration Output data rate.
#define KX132_1211_ODCNTL_OSA_MASK 0x0F
// Pulse interrupt 1 width configuration
#define KX132_1211_INC1_PW1_MASK 0xC0
// And-Or configuration. 0=Or combination of selected directions, 1=And combination of selected axes
#define KX132_1211_INC2_AOI_MASK 0x40
// Pulse interrupt 2 width configuration
#define KX132_1211_INC5_PW2_MASK 0xC0
#define KX132_1211_TILT_TIMER_TSC_MASK 0xFF
#define KX132_1211_TDTC_TDTC_MASK 0xFF
#define KX132_1211_TTH_TTH_MASK 0xFF
#define KX132_1211_TTL_TTL_MASK 0xFF
#define KX132_1211_FTD_FTDH_MASK 0xF8
#define KX132_1211_FTD_FTDL_MASK 0x07
#define KX132_1211_STD_STD_MASK 0xFF
#define KX132_1211_TLT_TLT_MASK 0xFF
#define KX132_1211_TWS_TWS_MASK 0xFF
#define KX132_1211_FFTH_FFTH_MASK 0xFF
#define KX132_1211_FFC_FFC_MASK 0xFF
// Free fall interrupt delayed clear duration for unlatched mode
#define KX132_1211_FFCNTL_FFDC_MASK 0x30
// Free fall function output data rate
#define KX132_1211_FFCNTL_OFFI_MASK 0x07
#define KX132_1211_TILT_ANGLE_LL_LL_MASK 0xFF
#define KX132_1211_TILT_ANGLE_HL_HL_MASK 0xFF
#define KX132_1211_HYST_SET_HYST_MASK 0xFF
// Averaging Filter Control
#define KX132_1211_LP_CNTL1_AVC_MASK 0x70
#define KX132_1211_BTSWUFTH_BTSTH_H_MASK 0x70
#define KX132_1211_BTSWUFTH_WUFTH_H_MASK 0x07
#define KX132_1211_BTSC_BTSC_MASK 0xFF
#define KX132_1211_WUFC_WUFC_MASK 0xFF
// When 0xCA is written to this register, the MEMS self-test function is enabled. Electrostatic-actuation of the accelerometer, results in a DC shift of the X, Y and Z axis outputs
#define KX132_1211_SELF_TEST_MEMS_TEST_MASK 0xFF
#define KX132_1211_BUF_CNTL1_SMP_TH_MASK 0xFF
// selects the operating mode of the sample buffer
#define KX132_1211_BUF_CNTL2_BM_MASK 0x03
#define KX132_1211_BUF_STATUS_2_SMP_LEV_H_MASK 0x03
// Number of samples used to calculate RMS output. Each sample is determined by the Advanced Data Path ODR as set by OADP<3:0> bits.
#define KX132_1211_ADP_CNTL1_RMS_AVC_MASK 0x70
// Output Data Rate (ODR) for Advanced Data Path.
#define KX132_1211_ADP_CNTL1_OADP_MASK 0x0F
#define KX132_1211_ADP_CNTL3_ADP_F1_1A_MASK 0x7F
#define KX132_1211_ADP_CNTL10_ADP_F1_ISH_MASK 0x1F
#define KX132_1211_ADP_CNTL11_ADP_F2_1A_MASK 0x7F
#define KX132_1211_ADP_CNTL18_ADP_F2_ISH_MASK 0x1F
#define KX132_1211_ADP_CNTL19_ADP_F2_OSH_MASK 0x1F
#endif
