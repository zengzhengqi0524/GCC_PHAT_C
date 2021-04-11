/*
 * @Author: your name
 * @Date: 2021-04-10 14:42:57
 * @LastEditTime: 2021-04-11 14:36:42
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
        for (uint32_t j = 0; j < samples; j++)
        {
            *(data[i] + j)= (float)*(buffer + i + 8 * j)/1000000;
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


//    //debug
//    for (uint16_t k= 0;  k<winlength ; k++)
//    {
//        printf("%lf\n",*(*data_framed[1]+k));
//    }



    float E[90][360];
    float r = 0.04;
    //帧数据缓冲区
    float *framedata[N];
    for (uint16_t i = 0; i < N; i++)
    {
        framedata[i] = (float *)malloc(sizeof(float) * winlength);
    }
    //接收数据内存
    float *yout = (float *)malloc(winlength * sizeof(float));
//空域扫描
 for (uint16_t pitch = 90; pitch >0; pitch--)
 {
     for (uint16_t yaw = 0; yaw < 360; yaw++)
     {
         //多帧
         for (uint16_t frame = 0; frame < 1; frame++)
         {

             //取出一帧数据
             for(uint16_t i = 0; i < N; i++)
             {
                 for (uint16_t k= 0;  k<winlength ; k++)
                 {
                     *(framedata[i]+k) = *(*(data_framed[i]+frame)+k);
                 }

             }

//             //DEBUG
//             float temp[N][winlength];
//             for(uint16_t i = 0; i < N; i++)
//             {
//                 for (uint16_t k= 0;  k<winlength ; k++)
//                 {
//                     temp[i][k] = *(framedata[i]+k);
//                 }
//
//             }
//             for (uint16_t k= 0;  k<winlength ; k++)
//             {
//                 printf("%lf\n",temp[2][k]);
//             }
//
//             printf("/////////////frame:%d\n",frame);

                // DSA计算

             DelaySumURA(framedata[N], yout, fs,N,winlength, r, yaw, pitch);
             //计算能量并多帧平均,还没实现
//
//             for (uint16_t j = 0; j < winlength; j++)
//             {
//                 E[pitch][yaw] = E[pitch][yaw]+ yout[j]*yout[j];
//             }

                //DEBUG
                if(yaw == 90 && pitch == 90 && frame == 0)
                {
                    for (uint16_t j = 0; j < winlength; j++)
                    {
                        printf("%f\n",yout[j]);
                    }
                    printf("end\n");
                }



         }

     }
 }

    free(data);
    free(yout);

    getchar();
    return 0;
}
