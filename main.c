/*
 * @Author: your name
 * @Date: 2021-04-10 14:42:57
 * @LastEditTime: 2021-04-10 19:53:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \GCC-PHAT\main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "wave.h"
#include "DelaySum.h"
#include "kiss_fftr.h"
#include "kiss_fft.h"
#include "kiss_fftr.h"
int main()
{
    FILE *fp;
    int16_t samples = 4096;
    int8_t N = 8;
    int32_t buffer[samples * N];

    fp = fopen("C:\\Users\\IRON\\Desktop\\tdoa_c\\GCC-PHAT\\bin\\Yaw270Pitch30.bin", "rb+");
    if (!fp)
    {
        printf("can't open file");
        exit(1);
    }

    fread(buffer, 4, samples* N, fp);
    fclose(fp);
    printf("read ok!");

    int32_t data[N][samples];

    for (uint16_t i = 0; i < N; i++)
    {
        for (uint16_t j = 0; j < samples; j++)
        {
            data[i][j] = buffer[i + 8 * j];
        }
    }

    /*
    uint16_t fs = 48000;

    uint32_t DataLen =4096;

	float *yout = (float *)malloc(DataLen * sizeof(float));

	float E[360];
    float r = 0.0457;
	for (uint16_t i = 0; i < 360; i++)
	{
		DelaySumURA(data, yout, fs, DataLen, N_FFT, WinLen, 256, r, i);
		for (uint16_t j = 0; j < DataLen; j++)
		{
			E[j] = E[j] + yout[j] * yout[j];
		}
	}

    //DelaySumURA(data, yout,fs, DataLen,N_FFT, WinLen, 256, r, 30);
    
	
    for (uint16_t i = 0; i < 360; i++)
    {
        printf ("%f\n",E[i]);
    }
    free(yout);
*/
    getchar();
    return 0;
}
