/*
 * @Author: your name
 * @Date: 2021-04-10 14:42:57
 * @LastEditTime: 2021-04-10 23:47:17
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \GCC-PHAT\main.c
 */
/*
 * @Author: your name
 * @Date: 2021-04-10 14:42:57
 * @LastEditTime: 2021-04-10 20:07:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \GCC-PHAT\main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "DelaySum.h"
#include "enframe.h"
#include "hamming.h"
#include "kiss_fftr.h"
#include "kiss_fft.h"
#include "kiss_fftr.h"
int main()
{
    FILE *fp = NULL;
    int32_t filesize;
    int32_t result;
    int32_t samples = 4096;
    int8_t N = 8;
    int32_t *buffer;

    uint32_t fs = 48000;
    fp = fopen("C:\\Users\\IRON\\Desktop\\tdoa_c\\GCC-PHAT\\bin\\Yaw90Pitch30.bin", "rb+");

    if (fp == NULL)
    {
        printf("can't open file");
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    buffer = (int32_t *)malloc(sizeof(char) * filesize);
    if (buffer == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    // copy the file into the buffer:
    result = fread(buffer, sizeof(int32_t), filesize / 4, fp);
    if (result != filesize / 4)
    {
        fputs("Reading error", stderr);
        exit(3);
    }
    fclose(fp);
    printf("read ok!");

    float *data[N];
    for (uint16_t i = 0; i < N; i++)
    {
        data[i] = (float *)malloc(sizeof(float) * samples);
    }

    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < samples; j++)
        {
            *(data[i] + j)= (float)*(buffer + i + 8 * j)/100000;
        }
    }
    //分帧
    int16_t winlength = 512;
    int16_t step = 256;
    int16_t fn = (samples - winlength) / step + 1; //计算帧数fn

    float **data_framed[N];
    for (uint16_t i = 0; i < N; i++)
    {
        data_framed[i] = (float **)malloc(sizeof(float *) *fn);
        for (uint16_t j = 0; j < fn; j++)
        {
            *(data_framed[i]+j) = (float *)malloc(sizeof(float) * winlength);
        }
    }


    for (uint16_t i = 0; i < N; i++)
    {
        enframe(data[i], data_framed[i] ,samples, winlength , step);
    }

    for (uint16_t i = 0; i < N; i++)
    {
        free(data[i]);
    }


    //加窗
    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0;  j<fn ; j++)
        {
            for (uint16_t k= 0;  k<winlength ; k++)
            {
                *(*(data_framed[i]+j) + k) = *(*(data_framed[i]+j) + k) * win[k];
            }
        }

    }


    //debug
    for (uint16_t k= 0;  k<winlength ; k++)
    {
        printf("%lf\n",*(*data_framed[1]+k));
    }



//    float E[90][360];
//    float r = 0.04;
//
//    float *yout = (float *)malloc(samples * sizeof(float));
// for (uint16_t pitch = 0; pitch < 90; pitch++)
// {
//     for (uint16_t yaw = 0; yaw < 360; yaw++)
//     {
//         DelaySumURA(data, yout, fs, samples, N_FFT, WinLen, 256, r, yaw, pitch);
//         for (uint16_t j = 0; j < samples; j++)
//         {
//             E[pitch][yaw] = E[pitch][yaw]+ yout[j]*yout[j];
//         }
//
//
//         printf("pitch=%d,yaw=%d,E=%lf\n",pitch,yaw,E[pitch][yaw]);
//     }
// }
//
//    free(data);
//    free(yout);
//
    getchar();
    return 0;
}
