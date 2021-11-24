/*
 * func.c
 *
 *  Created on: 2021-10-13
 *      Author: Ann
 */
#pragma warning(disable:4996)
#include "../include/func.h"

uint8_t transfer_arr(const char *yuv_path, const char *save_path, const int32_t height, const int32_t width, const uint8_t is_sa)
{
	int8_t return_val = 0;
	FILE *in_ptr = fopen(yuv_path, "rb");
	FILE *out_ptr = fopen(save_path, "wb");
	const int32_t idx_height = (height >> 2);
	const int32_t read_data_size = idx_height << 4;
	const int32_t idx_width = (width >> 2);
	int32_t i, j, j_4, k, l, m, idx;
	uint8_t *data = (uint8_t *)malloc(sizeof(uint8_t) * read_data_size);
	int16_t *out_data = (int16_t *)malloc(sizeof(int16_t) * read_data_size);
	int16_t *tmp_data  = (int16_t *)malloc(sizeof(int16_t) * 16);
	int16_t* H = get_H_kernel();
	if (!in_ptr || !out_ptr)
	{
		return_val = 1;
	}
	else
	{
		for (i = idx_width - 1; i >= 0; i--)
		{
			fread(data, sizeof(uint8_t), read_data_size, in_ptr);
			if (i % 5 == 0 || i == 0 || i == idx_width - 1)
			{
				printf("process row (%d/%d)\n", i, idx_width);
			}
			if (is_sa)
			{
			}
			else
			{
				for (j = idx_height - 1; j >= 0; j--)
				{
					j_4 = j << 2;
					/* j_4 -> j_4+15 */
					for (k = 15; k >= 0; k--)
					{
						l = k % 4;
						idx = (k >>2<< 2) + l;
						*(tmp_data + idx) = 0;
						for (m = 3; m >= 0; m--)
								//printf("(%d,%d,%d)\n",idx, (k << 2) + m,j_4 + l + (m * height));
							*(tmp_data + idx) += *(H + (k >>2<< 2) + m) * *(data + j_4 + m + (l * height));

					}
					for (k = 15; k >= 0; k--)
					{
						l = k % 4;
						for (l = 3; l >= 0; l--)
						{
							idx = j_4 + (k>>2) + (l * height);
							*(out_data + idx) = 0;
							for (m = 3; m >= 0; m--)
								*(out_data + idx) += *(tmp_data+ (k>>2<<2) + m) * *(H+ (l<<2)+m);
						}
					}
				}
			}
			fwrite(out_data, sizeof(int16_t), read_data_size, out_ptr);
			/*for (j = 0; j < read_data_size; j++)
			{
				if (j % 352 == 0)
					printf("\n\n");
				printf("%d,", *(out_data + j));

			}*/
		}

	}
	free(H);
	free(tmp_data);
	free(data);
	free(out_data);
	fclose(in_ptr);
	fclose(out_ptr);

	return return_val;
}
int16_t *get_H_kernel()
{
	int16_t *H = (int16_t *)malloc(sizeof(int16_t) * 16);
	*(H) = 1;*(H + 1) = 1;*(H + 2) = 1;*(H + 3) = 1;
	*(H + 4) = 2;*(H + 5) = 1;*(H + 6) = -1;*(H + 7) = -2;
	*(H + 8) = 1;*(H + 9) = -1;*(H + 10) = -1;*(H + 11) = 1;
	*(H + 12) = 1;*(H + 13) = -2;*(H + 14) = 2;*(H + 15) = -1;
	return H;
}

