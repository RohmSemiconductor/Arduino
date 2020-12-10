/*****************************************************************************
    BM1422AGMV_FFT_SPRESENSE.ino

    Copyright (c) 2020 ROHM Co.,Ltd.

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
#include <Arduino.h>
#include <Wire.h>
#include "BM1422AGMV.h"
#include <arduinoFFT.h>

#define SYSTEM_BAUDRATE      (115200)
#define SAMPLES              (256)  // 2^n
#define SAMPLING_FREQUENCY   (600)  // Hz
#define harmonic_start_point (5)  // ignore low frequency

BM1422AGMV bm1422agmv(BM1422AGMV_DEVICE_ADDRESS_0F);
void get_data(double *real_x, double *real_y, double *real_z, double *imag_x, double *imag_y, double *imag_z);
void calc_FFT(double *real, double *imag);
void draw_data(int32_t cnt_max, double *real_x, double *real_y, double *real_z);
void draw_harmonics(double *real_x, double *real_y, double *real_z);
void calc_Harmonics(double *real, int32_t *first_cnt, int32_t *second_cnt, int32_t *third_cnt);

double real_x[SAMPLES], real_y[SAMPLES], real_z[SAMPLES];
double imag_x[SAMPLES], imag_y[SAMPLES], imag_z[SAMPLES];

// make FFT object
arduinoFFT FFT = arduinoFFT();

void setup()
{
    int32_t result;

    Serial.begin(SYSTEM_BAUDRATE);
    while (!Serial);

    Wire.begin();

    result = bm1422agmv.init();
    if (result != 0) {
        Serial.println(F("BM1422AGMV initialization failed"));
        Serial.flush();
    }

    delay(100);
}

void loop()
{
    get_data(real_x, real_y, real_z, imag_x, imag_y, imag_z);

    // for debug  // draw sensor data
    draw_data(SAMPLES, real_x, real_y, real_z);

    // arduinoFFT fanctions
    calc_FFT(real_x, imag_x);
    calc_FFT(real_y, imag_y);
    calc_FFT(real_z, imag_z);

    // draw FFT data
    draw_data((SAMPLES/2), real_x, real_y, real_z);

    draw_harmonics(real_x, real_y, real_z);

    // for debug // single  
    //while(1);

    // Loop
    delay(1000);
}

void get_data(double *real_x, double *real_y, double *real_z, double *imag_x, double *imag_y, double *imag_z)
{
    int32_t cnt;
    uint32_t start_time;
    uint32_t sampling_time = 1.00 / SAMPLING_FREQUENCY * 1000000;
    float mag[3] = {0.0, 0.0, 0.0};

    for(cnt = 0; cnt < SAMPLES; cnt++){
        start_time = micros();
        
        (void)bm1422agmv.get_val(mag);

        real_x[cnt] = (double)mag[0];  // x axsis
        real_y[cnt] = (double)mag[1];  // y axsis
        real_z[cnt] = (double)mag[2];  // z axsis

        imag_x[cnt] = 0;
        imag_y[cnt] = 0;
        imag_z[cnt] = 0;

        // wait sampling time
        while(micros() < (start_time + sampling_time));
    }
}

void calc_FFT(double *real, double *imag)
{
    FFT.DCRemoval(real, SAMPLES);
    FFT.Windowing(real, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(real, imag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(real, imag, SAMPLES);
}

void draw_data(int32_t cnt_max, double *real_x, double *real_y, double *real_z)
{
    int32_t cnt;

    for (cnt = 0; cnt < cnt_max; cnt++) {
        Serial.print(real_x[cnt], 5);
        Serial.print(",");
        Serial.print(real_y[cnt], 5);
        Serial.print(",");
        Serial.println(real_z[cnt], 5);
    }

    Serial.println();
}

void draw_harmonics(double *real_x, double *real_y, double *real_z)
{
    int32_t cnt;
    float frequency[SAMPLES/2];
    int32_t first_cnt, second_cnt, third_cnt;

    first_cnt  = 0;
    second_cnt = 0;
    third_cnt  = 0;
    
    for (cnt = 0; cnt < SAMPLES/2; cnt++) {
        frequency[cnt] = (float)SAMPLING_FREQUENCY / SAMPLES * cnt;
    }

    // x axis
    calc_Harmonics(real_x, &first_cnt, &second_cnt, &third_cnt);
    Serial.println("--- X axis harmonics ---");
    Serial.print("First  harmonic [Hz] : ");
    Serial.println(frequency[first_cnt], 5);
    Serial.print("Second harmonic [Hz] : ");
    Serial.println(frequency[second_cnt], 5);
    Serial.print("Third  harmonic [Hz] : ");
    Serial.println(frequency[third_cnt], 5);
    Serial.println();

    // y axis
    calc_Harmonics(real_y, &first_cnt, &second_cnt, &third_cnt);
    Serial.println("--- Y axis harmonics ---");
    Serial.print("First  harmonic [Hz] : ");
    Serial.println(frequency[first_cnt], 5);
    Serial.print("Second harmonic [Hz] : ");
    Serial.println(frequency[second_cnt], 5);
    Serial.print("Third  harmonic [Hz] : ");
    Serial.println(frequency[third_cnt], 5);
    Serial.println();

    // z axis
    calc_Harmonics(real_z, &first_cnt, &second_cnt, &third_cnt);
    Serial.println("--- Z axis harmonics ---");
    Serial.print("First  harmonic [Hz] : ");
    Serial.println(frequency[first_cnt], 5);
    Serial.print("Second harmonic [Hz] : ");
    Serial.println(frequency[second_cnt], 5);
    Serial.print("Third  harmonic [Hz] : ");
    Serial.println(frequency[third_cnt], 5);
    Serial.println();
}

void calc_Harmonics(double *real, int32_t *first_cnt, int32_t *second_cnt, int32_t *third_cnt)
{
    int32_t cnt;
    double first_val, second_val, third_val;

    first_val  = 0;
    second_val = 0;
    third_val  = 0;

    for (cnt = harmonic_start_point; cnt < SAMPLES/2; cnt++) {
        if (real[cnt] > first_val) {
            first_val = real[cnt];
            *first_cnt = cnt;
        } else if (real[cnt] > second_val) {
            second_val = real[cnt];
            *second_cnt = cnt;
        } else if (real[cnt] > third_val) {
            third_val = real[cnt];
            *third_cnt = cnt;
        }
    }
}
