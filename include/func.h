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

/* c_function */

/* matrix transfer*/
uint8_t transfer_arr(const char *yuv_path, const char *save_path,const int32_t height,const int32_t width, const uint8_t is_sa);

int16_t* get_H_kernel();

#endif /* FUNC_H_ */
