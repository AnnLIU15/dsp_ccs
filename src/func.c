/*
 * func.c
 *
 *  Created on: 2021-10-13
 *      Author: Ann
 */
#include "../include/func.h"

uint8_t ycrbr2rgb(const char *img_path, const char *save_path)
{
	/* ycrbr2rgb
	 * img_path(in): image path
	 * save_path(in): save path
	 */
	/* return value*/
	int8_t return_val = 0;
	int32_t src_height, src_width, equal_width;
	int32_t offset_address, offset_width, equal_offset_address;
	int32_t i;
	int32_t j, j_3;
	float_t* ycrcb_kernel_f;
	int16_t* ycrcb_kernel_i;
	uint8_t y,cr,cb, r,g,b;
	/* bgr bgr brg */
	uint8_t *src_data;
	FILE *in_ptr = fopen(img_path, "rb");
	FILE *out_ptr = fopen(save_path, "wb");
	/* file header */
	BITMAPFILEHEADER *file_header_ptr = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
	/* info header */
	BITMAPINFOHEADER *info_header_ptr = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
	/* get header information */
	get_header_info(in_ptr, file_header_ptr, info_header_ptr, 0);

	if (file_header_ptr->bf_type != 19778)
	{
		/* not BMP file or haven't open file*/
		return_val = 1;
		/* free header */
		free(file_header_ptr);
		free(info_header_ptr);
	}
	else
	{
		// fseek(in_ptr, 0, SEEK_SET);
		/* get source properties*/
		src_height = info_header_ptr->bi_height;
		src_width = info_header_ptr->bi_width;
		/* transform properties and write header */
		write_header_info(out_ptr, file_header_ptr, info_header_ptr, 1, 1);
		free(file_header_ptr);
		free(info_header_ptr);
		offset_address = 4 - (src_width % 4); /* symmetry */
		equal_width = src_width * 3;
		equal_offset_address = offset_address * 3;
		offset_width = (offset_address == 4) ? equal_width : equal_width + equal_offset_address;
		src_data = (uint8_t*)malloc(sizeof(uint8_t) * equal_width);
		for(i = src_height-1;i>=0;i--)
		{

			if (i % 20 == 0 || i == 0 || i == src_height - 1)
			{
				printf("process row (%d/%d)\n", i, src_height);
			}
			get_row_data(in_ptr, src_data, i, src_height, src_width,24);

			//ycbcr2rgb_core(src_data,dst_data,ycrcb_kernel_i,src_width,8);
			 for(j=src_width-1;j>=0;j--)
			 {
			 	j_3 = j * 3;
			 	cr = *(src_data+j_3);
			 	cb = *(src_data+j_3+1);
			 	y = *(src_data+j_3+2);
//
			 	ycbcr2rgb_core(y,cb,cr,&r,&g,&b);
//			 	if(r==255||g==255||b==255)
//			 	{
//			 		printf("rgb(%d,%d,%d)<-",(uint8_t)(1.164*y+1.402*(cr-128)),
//			 					 				 	(uint8_t)(1.164*y-0.344*(cb-128)-0.714*(cr-128)),
//			 					 				 	(uint8_t)(1.164*y+1.772*(cb-128)));
//			 		printf("(%d,%d,%d)->(%d,%d,%d)\n",y,cb,cr,r,g,b);
//			 	}

			 	*(src_data+j_3+2)=r;
			 	*(src_data+j_3+1)=g;
			 	*(src_data+j_3)  =b;
//			 	*(dst_data+j_3)=1.164*y+1.772*(cb-128);//b
//			 	*(dst_data+j_3+1)=1.164*y-0.344*(cb-128)-0.714*(cr-128);//g
//			 	*(dst_data+j_3+2)= 1.164*y+1.402*(cr-128);//r
			 }
			write_row_data(out_ptr,src_data,offset_width);
		}
		free(src_data);
	}
	fclose(in_ptr);
	fclose(out_ptr);
	free(in_ptr);
	free(out_ptr);
	return return_val;
}

void write_ycrcb_k(float_t* data_ptr)
{
	/* get ycrcb_kernel 
	 * data_ptr(inout): ycrcb kernel
	 */
	/*[[1.164,0,1.402],
	 * [1.164,-0.344,-0.714],
	 * [1.164,1.772,0]]
	 */
	*(data_ptr)=1.164;*(data_ptr+1)=0;*(data_ptr+2)=1.402;
	*(data_ptr+3)=1.164;*(data_ptr+4)=-0.344;*(data_ptr+5)=-0.714;
	*(data_ptr+6)=1.164;*(data_ptr+7)=1.772;*(data_ptr+8)=0;
}


uint8_t bilinear_interpolation(const char *img_path, const char *save_path, const float scale_factor, const float times, const int is_sa)
{
	/* bilinear interpolation
	 * img_path(in): image path
	 * save_path(in): save path
	 * scale_factor(in): scale factor
	 * times(in): 1/scale_factor
	 * is_sa(in): using sa code
	 */
	/* return value*/
	int8_t return_val = 0;
	/* image properties */
	int32_t src_height, src_width, dst_height, dst_width, tmp;
	int32_t offset_address, offset_width;
	/* current row */
	uint16_t current_row = 0;
	int32_t i, j;
	uint8_t *src_data;
	uint8_t *dst_data;
	uint8_t a, b, c, d, r_limits, c_limits;
	double_t tmp_x, tmp_y, u, v;
	int32_t x0, y0;
	FILE *in_ptr = fopen(img_path, "rb");
	FILE *out_ptr = fopen(save_path, "wb");
	/* file header */
	BITMAPFILEHEADER *file_header_ptr = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
	/* info header */
	BITMAPINFOHEADER *info_header_ptr = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
	/* get header information */
	get_header_info(in_ptr, file_header_ptr, info_header_ptr, 0);

	if (file_header_ptr->bf_type != 19778)
	{
		/* not BMP file or haven't open file*/
		return_val = 1;
		/* free header */
		free(file_header_ptr);
		free(info_header_ptr);
	}
	else if ((scale_factor * times - 1) > 0.01 || (scale_factor * times - 1) < -0.01)
	{
		/* times * scale_factor not equal to 1 */
		return_val = 2;
		/* free header */
		free(file_header_ptr);
		free(info_header_ptr);
	}
	else
	{
		printf("Is using sa(1->yes):%d\n", is_sa);
		// fseek(in_ptr, 0, SEEK_SET);
		/* get source properties*/
		src_height = info_header_ptr->bi_height;
		src_width = info_header_ptr->bi_width;
		/* get destination properties*/
		dst_height = (int32_t)(scale_factor * src_height);
		dst_width = (int32_t)(scale_factor * src_width);
		/* transform properties and write header */
		write_header_info(out_ptr, file_header_ptr, info_header_ptr, scale_factor, 1);

		free(file_header_ptr);
		free(info_header_ptr);
		write_color_palette(in_ptr, out_ptr);
		/* backward write */

		printf("From(%d,%d) to (%d,%d)\n", src_height, src_width, dst_height, dst_width);
		offset_address = 4 - (dst_width % 4); /* symmetry */
		offset_width = (offset_address == 4) ? dst_width : dst_width + offset_address;

		src_data = (uint8_t *)malloc(sizeof(uint8_t) * (int32_t)((int16_t)src_width * (int16_t)2));
		dst_data = (uint8_t *)malloc(sizeof(uint8_t) * offset_width);
		for (i = offset_width - 1; i >= 0; i--)
			*(dst_data + i) = 0;
		current_row = src_height - 1;
		for (i = dst_height - 1; i >= 0; i--)
		{
			if (i == dst_height - 1)
			{
				get_row_data(in_ptr, src_data + src_width, current_row, src_height, src_width,8);
				current_row = current_row - 1;
				get_row_data(in_ptr, src_data, current_row, src_height, src_width,8);
			}
			else if (current_row - 1 >= ((uint16_t)(times * i)))
			{
				for (j = src_width - 1; j >= 0; j--)
				{
					*(src_data + src_width + j) = *(src_data + j);
				}
				current_row = current_row - 1;
				get_row_data(in_ptr, src_data, current_row, src_height, src_width,8);
			}
			else
			{
				;
			}
			if (i % 20 == 0 || i == 0 || i == dst_height - 1)
			{
				printf("process row (%d/%d) loaded src_row(%d,%d)\n", i, dst_height - 1, current_row, current_row + 1);
			}
			else
			{
				;
			}
			tmp_x = i * times;
			x0 = (int32_t)tmp_x;
			u = tmp_x - x0;
			r_limits = (x0 + 1 < src_height) ? 1 : 0;
			if (!is_sa)
			{
				for (j = dst_width - 1; j >= 0; j--)
				{
					tmp_y = j * times;
					y0 = (int32_t)tmp_y;
					c_limits = y0 + 1 < src_width ? 1 : 0;
					v = tmp_y - y0;
					a = *(src_data + y0);
					tmp = r_limits ? src_width : 0;
					b = *(src_data + tmp + y0);
					c = *(src_data + y0 + c_limits);
					d = *(src_data + tmp + y0 + c_limits);
					*(dst_data + j) = a * (1 - u) * (1 - v) + b * u * (1 - v) +
									  c * v * (1 - u) + u * v * d;
				}
			}
			else
			{
				// _cal_bilinear: .cproc src_data, dst_data, src_w, dst_w, u, r_limit, times,q_var
				cal_bilinear(src_data, dst_data, src_width, dst_width, u, r_limits, times, 8);
			}
			write_row_data(out_ptr,dst_data,offset_width);
			//fwrite(dst_data, sizeof(uint8_t), offset_width, out_ptr);
		}

		free(src_data);
		free(dst_data);
	}
	fclose(in_ptr);
	fclose(out_ptr);
	free(in_ptr);
	free(out_ptr);
	return return_val;
}

void get_row_data(FILE *in_ptr, uint8_t *data, const uint32_t row, const uint32_t src_height, const uint32_t src_width,const uint8_t bi_used_cnt)
{
	/* get data from source image
	 * in_ptr(inout): load file pointer
	 * data(out): get data
	 * row(in): which row you want to get (get src_height - row - 1)
	 * src_height(in): total row
	 * src_width(in): total col
	 * bi_used_cnt(in): bit color used count
	 * out_ptr(inout): write file
	 */
	int32_t offset_address = 4 - (src_width % 4); /* symmetry */
	int32_t offset_width = (offset_address == 4) ? src_width : src_width + offset_address;
	/* data offset */
	uint32_t data_offset_begin;
	int32_t equal_width = src_width;
	if(8==bi_used_cnt)
	{ 
		data_offset_begin = 1078 + (src_height - row - 1) * offset_width;
	}
	else if(24==bi_used_cnt)
	{
		equal_width = equal_width * 3;
		data_offset_begin = 54 + (src_height - row - 1) * offset_width * 3;
	}
	else
	{
		;
	}
	/* set to the target address */
	fseek(in_ptr, data_offset_begin, SEEK_SET);
	fread(data, sizeof(uint8_t), equal_width, in_ptr);
}

void write_row_data(FILE *out_ptr, uint8_t *data, const uint32_t offset_width)
{
	/* write data to dst image
	 * out_ptr(inout): write file pointer
	 * data(in): data
	 * offset_width(in): col after symmetry
	 */
	fwrite(data, sizeof(uint8_t), offset_width, out_ptr);
}

void write_color_palette(FILE *in_ptr, FILE *out_ptr)
{
	/* write the color used
	 * in_ptr(inout): load file
	 * out_ptr(inout): write file
	 */
	BITMAPColorPalette *ColorPalette = (BITMAPColorPalette *)malloc(sizeof(BITMAPColorPalette) * 256);
	fread(ColorPalette, sizeof(BITMAPColorPalette), 256, in_ptr);
	fwrite(ColorPalette, sizeof(BITMAPColorPalette), 256, out_ptr);
	free(ColorPalette);
}

void get_header_info(FILE *in_ptr, PBITMAPFILEHEADER file_header_ptr, PBITMAPINFOHEADER info_header_ptr, const uint8_t show_)
{
	/* read the file header and info header of in_ptr
	 * in_ptr(inout): load file
	 * file_header_ptr(inout): file header pointer
	 * info_header_ptr(inout): info header pointer
	 * show_(in): display the information loaded
	 */
	fread(file_header_ptr, sizeof(BITMAPFILEHEADER), 1, in_ptr);
	fread(info_header_ptr, sizeof(BITMAPINFOHEADER), 1, in_ptr);
	if (show_)
	{
		show_info(file_header_ptr, info_header_ptr);
	}
	else
	{
		;
	}
}

void write_header_info(FILE *out_ptr, const PBITMAPFILEHEADER file_header_ptr,
					   const PBITMAPINFOHEADER info_header_ptr, const float_t scale_factor, const uint8_t show_)
{
	/* write the file header and info header of in_ptr
	 * out_ptr(inout): write file
	 * file_header_ptr(in): file header pointer
	 * info_header_ptr(in): info header pointer
	 * scale_factor(in): scale factor of image
	 * show_(in): display the information loaded
	 */
	int32_t symmetry_width = 0;
	if (scale_factor == 1)
	{
		;
	}
	else
	{
		info_header_ptr->bi_height = (int32_t)(scale_factor * info_header_ptr->bi_height);
		info_header_ptr->bi_width = (int32_t)(scale_factor * info_header_ptr->bi_width);
		/* 4-byte symmetry
		 * 32bits -> 4Bytes
		 * int32_t(bi_width[Byte numbers]*8 +31[32-1])/32*4
		 * ((bi_width*8+31)>>5)*4
		 * (bi_width*8+31)>>5 <<2
		 */
		symmetry_width = (info_header_ptr->bi_width * 8 + 31) >> 5 << 2;
		info_header_ptr->bi_size_image = symmetry_width * info_header_ptr->bi_height;
		file_header_ptr->bf_size = file_header_ptr->bf_off_bits + info_header_ptr->bi_size_image;
	}

	fwrite(file_header_ptr, sizeof(BITMAPFILEHEADER), 1, out_ptr);
	fwrite(info_header_ptr, sizeof(BITMAPINFOHEADER), 1, out_ptr);
	if (show_)
	{
		show_info(file_header_ptr, info_header_ptr);
	}
	else
	{
		;
	}
}

void show_info(const PBITMAPFILEHEADER file_header_ptr, const PBITMAPINFOHEADER info_header_ptr)
{
	/* show the information to screen
	 * file_header_ptr(inout): file header pointer
	 * info_header_ptr(inout): info header pointer
	 */
	printf("SHOWING INFOMATION OF BMP IMAGE\n");
	printf("#####################################################################\nBit Map File Header:\n");
	printf("\tBMP BM:%d\n", file_header_ptr->bf_type);
	printf("\tBMP bitmap file size(Kb):%f\n", (file_header_ptr->bf_size / 1024.0));
	printf("\t0 reserved Byte(Must be 0):%d\n", file_header_ptr->bf_reserved_0);
	printf("\t1 reserved Byte(Must be 0):%d\n", file_header_ptr->bf_reserved_1);
	printf("\tThe actual offset Bytes of bitmap data: %d\n", file_header_ptr->bf_off_bits);
	printf("#####################################################################\nBit Map Info Header:\n");
	printf("\tThe size of info header:%d\n", info_header_ptr->bi_size);
	printf("\tBitmap's width:%d\n", info_header_ptr->bi_width);
	printf("\tBitmap's height:%d\n", info_header_ptr->bi_height);
	printf("\tThe number of planes of the image(default 1):%d\n", info_header_ptr->bi_planes);
	printf("\tNumber of bits per pixel:%d\n", info_header_ptr->bi_bit_count);
	printf("\tCompress mode:%d\n", info_header_ptr->bi_compression);
	printf("\tSize of picture:%d\n", info_header_ptr->bi_size_image);
	printf("\tHorizontal resolution:%d\n", info_header_ptr->bi_x_pels_per_meter);
	printf("\tVertical resolution:%d\n", info_header_ptr->bi_y_pels_per_meter);
	printf("\tNumber of colors used:%d\n", info_header_ptr->bi_clr_used);
	printf("\tNumber of Important colors used:%d\n", info_header_ptr->bi_clr_important);
}
