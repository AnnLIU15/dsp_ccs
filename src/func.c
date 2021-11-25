/*
 * func.c
 *
 *  Created on: 2021-10-13
 *      Author: Ann
 */
#include "../include/func.h"


uint8_t transfer_arr_p(const char* yuv_path, const char* save_path, const int32_t height, const int32_t width,const uint8_t is_sa)
{
	/* get the data from yuv file and transfer them to int16 and save it to txt file
	 * yuv_path(in): yuv data file
	 * save_path(out): save process file
	 * height,width(in): data attribute
	 * is_sa(in): select sa or c function
	 */
	uint8_t return_val = 0;
	uint8_t get_data;
	FILE* in_ptr = fopen(yuv_path, "rb");
	FILE* out_ptr = fopen(save_path, "wb");
	const int32_t idx_height = (height >> 2);
	const int32_t read_data_size = idx_height << 4;
	const int32_t idx_width = (width >> 2);
	int32_t i, j, j_4;
	int16_t* data = (int16_t*)malloc(sizeof(int16_t) * read_data_size);
	int16_t* tmp_data = (int16_t*)malloc(sizeof(int16_t) * 16);
	int16_t* tmp_data_sa = (int16_t*)malloc(sizeof(int16_t) * 16);
	int16_t* H = get_H_kernel();
	for (i = idx_width - 1; i >= 0; i--)
	{
		/* get height<<2 numbers data*/
		for (j_4 = read_data_size - 1; j_4 >= 0; j_4--)
		{
			fread(&get_data, sizeof(uint8_t), 1, in_ptr);
			*(data + (read_data_size - 1 - j_4)) = get_data;
		}
		/* sa func pr c function */
		if(!is_sa)
		{
			for (j = idx_height - 1; j >= 0; j--)
			{
				j_4 = j << 2;
				get_4x4_data(tmp_data, data, j_4, height);
				mat_mpy4x4(tmp_data, H);
				// if(!is_sa)
				// {
				// 	mat_mpy4x4(tmp_data, H);
				// }
				// else
				// {
				// 	mat_process(tmp_data,tmp_data_sa, H);
				// }
				//mat_process(data,tmp_data, H);
				back_4x4_data(data, tmp_data, j_4, height);
			}
		}
		else
		{
			mat_process_c(data,tmp_data, H,idx_height);
		}
			fwrite(data, sizeof(int16_t), read_data_size, out_ptr);
	}
	free(tmp_data_sa);
	free(tmp_data);
	free(H);
	free(data);
	return return_val;
}
void mat_mpy4x4(int16_t* data, const int16_t* H)
{
	/* Y = H * X * H'
	 * data(inout): X matrix -> Y matrix
	 * H(in): H matrix
	 */
	int32_t i, j,m,idx;
	int16_t* tmp = (int16_t*)malloc(sizeof(int16_t) * 16);
	for (i = 15; i >= 0; i--)
	{
		j = i % 4;
		idx = (i >> 2 << 2) + j;
		*(tmp + idx) = 0;
		for (m = 3; m >= 0; m--)
		{
			*(tmp + idx) += *(H + (i >> 2 << 2) + m) * *(data + (m << 2) + j);
		}
	}
	for (i = 15; i >= 0; i--)
	{
		j = i % 4;
		idx = (i >> 2 << 2) + j;
		*(data + idx) = 0;
		for (m = 3; m >= 0; m--)
		{
			*(data + idx) += *(tmp + (i >> 2 << 2) + m) * *(H + (j << 2) + m);
		}
	}
	free(tmp);
}

void get_4x4_data(int16_t* tmp_data, const int16_t* data,const int32_t j_4,const int32_t length)
{
	/* get the data from (height,4) -> (4,4)
	 * tmp_data(out): (4,4)
	 * data(in): (height,4)
	 * j_4,height(in): position var
	 */
	int32_t i, j;
	for (i = 15; i >= 0; i--)
	{
		j = i % 4;
		*(tmp_data + (i >> 2 << 2) + j) = *(data + j_4 + (i >> 2) + j * length);
	}
}

void back_4x4_data(int16_t* data, const int16_t* tmp_data, const int32_t j_4, const int32_t length)
{
	/* back the data from (4,4) -> (height,4)
	 * tmp_data(in): (4,4)
	 * data(out): (height,4)
	 * j_4,height(in): position var
	 */
	int32_t i, j;
	for (i = 15; i >= 0; i--)
	{
		j = i % 4;
		*(data + j_4 + (i >> 2) + j * length) = *(tmp_data + (i >> 2 << 2) + j);
	}
}



int16_t *get_H_kernel()
{
	/*    |--       --|
	 *    | 1, 1, 1, 1|
	 * H= | 2, 1,-1,-2|
	 *    | 1,-1,-1, 1|
	 *    | 1,-2, 2,-1|
	 *    |--       --|
	 */
	int16_t *H = (int16_t *)malloc(sizeof(int16_t) * 16);
	*(H) = 1;*(H + 1) = 1;*(H + 2) = 1;*(H + 3) = 1;
	*(H + 4) = 2;*(H + 5) = 1;*(H + 6) = -1;*(H + 7) = -2;
	*(H + 8) = 1;*(H + 9) = -1;*(H + 10) = -1;*(H + 11) = 1;
	*(H + 12) = 1;*(H + 13) = -2;*(H + 14) = 2;*(H + 15) = -1;
	return H;
}


