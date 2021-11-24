/*
 * func.h
 *
 *  Created on: 2021-10-13
 *      Author: Ann
 */

#ifndef FUNC_H_
#define FUNC_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"bmpInfo.h"

/* sa function */
uint8_t cal_abcd(uint8_t, uint8_t, uint8_t, uint8_t, int32_t, int32_t, int32_t);

int16_t float2int(float, int);

int16_t ufloat2int(float, int);

uint8_t single_test(uint8_t *, int32_t, int32_t, float_t, uint8_t, float_t, int32_t);

void cal_bilinear(uint8_t *, uint8_t *, int32_t, int32_t, float_t, uint8_t, float_t, int32_t);

void ycbcr2rgb_col(uint8_t *,int32_t);

/* c_function */

/* matrix transfer*/
uint8_t transfer_arr(const char *yuv_path, const char *save_path,const int32_t height,const int32_t width,const int16_t* H, const uint8_t is_sa);

int16_t* get_H_kernel();

#endif /* FUNC_H_ */
