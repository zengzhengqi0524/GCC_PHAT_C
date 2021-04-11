/*
 * @Author: your name
 * @Date: 2021-04-10 14:42:57
 * @LastEditTime: 2021-04-11 12:35:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \undefinedc:\Users\IRON\Desktop\tdoa_c\GCC-PHAT\DelaySum.h
 */

#ifndef DELAYSUM_H__
#define DELAYSUM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "kiss_fft.h"
#include "kiss_fftr.h"

#define Nele 8    //Number of array elements
#define N_FFT 512 //FFT point
#define WinLen 512
#define pi 3.1415926

    typedef struct
    {
        double real;
        double imag;
    } Complex;

    int16_t DelaySumURA(float **framedata, float *yout, uint16_t fs, int16_t N, int16_t frameLength, float r, int16_t angle, int16_t pitch);
    int8_t Angle2Radian(float *gamma);
    void CalculateTau(float *gamma, float *tao, int16_t angle, int16_t pitch);

#ifdef __cplusplus
}
#endif

#endif /* OKAOCOMAPI_H__ */
