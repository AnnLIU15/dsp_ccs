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

int ufloat2int(float, int);

uint8_t single_test(uint8_t *, int32_t, int32_t, float_t, uint8_t, float_t, int32_t);

void cal_bilinear(uint8_t *, uint8_t *, int32_t, int32_t, float_t, uint8_t, float_t, int32_t);
/* c_function */
uint8_t bilinear_interpolation(const char *img_path, const char *save_path, const float scale_factor, const float times, const int is_sa);

/* get row(height) image data*/
void get_row_data(FILE *in_ptr, uint8_t *data, const uint32_t row, const uint32_t src_height, const uint32_t src_width);

/* write row(height) image data*/
void write_row_data(FILE *out_ptr, uint8_t *data, const uint32_t dst_width);

/* write the color palette from input image */
void write_color_palette(FILE *in_ptr, FILE *out_ptr);

/* get the header information to file */
void get_header_info(FILE *in_ptr, PBITMAPFILEHEADER file_header_ptr, PBITMAPINFOHEADER info_header_ptr, const uint8_t show_);

/* write the header information to file */
void write_header_info(FILE *out_ptr, const PBITMAPFILEHEADER file_header_ptr,
					   const PBITMAPINFOHEADER info_header_ptr, const float_t scale_factor, const uint8_t show_);

/* show the information of header */
void show_info(const PBITMAPFILEHEADER file_header_ptr, const PBITMAPINFOHEADER info_header_ptr);

#endif /* FUNC_H_ */
