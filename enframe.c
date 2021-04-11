/*
 * @Author: your name
 * @Date: 2021-03-31 20:27:08
 * @LastEditTime: 2021-04-11 12:34:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: c:\Users\IRON\Desktop\tdoa_c\GCC-PHAT\enframe.c
 */
#include "enframe.h"

void enframe(float *data, float **data_framed,int datalength, int winlength, int step)
{
    int fn = (datalength - winlength) / step + 1; //计算帧数fn
    int i, j, k;
    for (i = 0; i < fn; i++) //i控制矩阵的行
    {
        for (j = 0; j < winlength; j++) //j控制矩阵的列
        {
            *(*(data_framed+i)+j) = 0; //对矩阵data_framed进行初始化
        }
    }

    for (i = 0; i < fn; i++)
    {
        if (i < fn - 1) //向前fn-1帧（矩阵data_framed的前fn-1行）存入数据
        {
            for (j = 0, k = step * i; j < winlength, k < step * i + winlength; j++, k++) //前fn-1行每行存入winlength个数据
                *(*(data_framed+i)+j) = data[k];
        }
        else //向第fn帧（矩阵data_framed的第fn行）存入数据
        {
            for (j = 0, k = step * i; j < datalength - (fn - 1) * step, k <= step * i + (datalength - (fn - 1) * step); j++, k++) //最后一行存入N-(fn-1)*inc个数据
                *(*(data_framed+i)+j) = data[k];
        }
    }
}

void showmatrix(float **result, int datalength, int winlength, int step)
{
    int i, j;

    int fn = (datalength - winlength) / step + 1;
    float arr[fn][winlength];

    for (i = 0; i < fn; i++)
    {
        if (i < fn - 1) //前fn-1行，行与行之间换行
        {
            for (j = 0; j < winlength; j++)
            {
                if (j < winlength - 1)
                    printf("%f ", arr[i][j]);
                else
                    printf("%f", arr[i][j]);
            }
            printf("\n");
        }
        else
        {
            for (j = 0; j < winlength; j++)
            {
                if (j < winlength - 1)
                    printf("%f ", arr[i][j]);
                else
                    printf("%f", arr[i][j]);
            }
        }
    }
}

