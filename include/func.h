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
/* just 4x4 process */
//void mat_process(int16_t*data,int16_t*tmp_data,int16_t*H);

/* process & get data */
void mat_process_c(int16_t*data,int16_t*tmp_data,int16_t*H,int16_t height_div4);

/* c_function */

/* matrix transfer*/
uint8_t transfer_arr_p(const char* yuv_path, const char* save_path, const int32_t height, const int32_t width,const uint8_t is_sa);

/* DATA = H * DATA *H' */
void mat_mpy4x4(int16_t* data, const int16_t* H);

/* get the data from heightx4 -> 4x4 */
void get_4x4_data(int16_t* tmp_data, const int16_t* data, const int32_t j_4, const int32_t length);

/* back the data from 4x4 -> heightx4 */
void back_4x4_data(int16_t* data, const int16_t* tmp_data, const int32_t j_4, const int32_t length);

/* H matrix */
int16_t* get_H_kernel();

#endif /* FUNC_H_ */
