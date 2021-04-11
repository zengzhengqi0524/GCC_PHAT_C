/*
 * @Author: your name
 * @Date: 2021-03-31 20:27:08
 * @LastEditTime: 2021-04-11 12:35:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: c:\Users\IRON\Desktop\tdoa_c\GCC-PHAT\enframe.h
 */
#ifndef ENFRAME_H_
#define ENFRAME_H_

#include <stdio.h>
#include <math.h>
#include <stdint.h>

void enframe(float *data, float **data_framed,int datalength, int winlength, int step);
void showmatrix(float **result, int datalength, int winlength, int step);

#endif