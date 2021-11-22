/*
 * main.c
 */

#include <stdio.h>
#include "include/func.h"
//int16_t float2int(float_t x,int16_t q_var);
int main(void)
{
//	/* file to load and the save path */
//	const char *hw1_2_in = "../data/lena512.bmp";
//	//const char* hw1_out = "C:/Users/Ann/Desktop/output/lena512_bilinear.bmp";
//	const char *hw2_out = "../output/lena512_bilinear_sa.bmp";
//	//uint8_t success_hw1 = bilinear_interpolation(hw1_2_in, hw1_out, 1.5, 0.666666666666667, 0);
//	/* for test */
//	uint8_t success_hw2 = bilinear_interpolation(hw1_2_in,hw2_out,1.5,0.666666666666667,1);
//	if (success_hw2 == 0)
//		printf("success_hw2!\n");
//	else if (success_hw2 == 1)
//		printf("It is not BMP file or haven't open file! Please check your input!\n");
//	else if (success_hw2 == 2)
//		printf("times * scale_factor not equal to 1!\n");
//	else
//	{
//		printf("Unknown error!\n");
//	}
	const char *hw3_in = "../data/ycbcr.bmp";
	const char *hw3_out = "../output/data4_ycbcr2rgb.bmp";
	uint8_t success_hw3 = ycrbr2rgb(hw3_in,hw3_out);
	if (success_hw3 == 0)
		printf("success_hw3!\n");
	else if (success_hw3 == 1)
		printf("It is not BMP file or haven't open file! Please check your input!\n");
	else
	{
		printf("Unknown error!\n");
	}
//	int i;
//	float_t* data_ptr =(float_t*)malloc(sizeof(float_t)*9);
//	int16_t* data_i = (int16_t*)malloc(sizeof(int16_t)*9);
//	*(data_ptr)=1.164;*(data_ptr+1)=0;*(data_ptr+2)=1.402;
//	*(data_ptr+3)=1.164;*(data_ptr+4)=-0.344;*(data_ptr+5)=-0.714;
//	*(data_ptr+6)=1.164;*(data_ptr+7)=1.772;*(data_ptr+8)=0;
//	for(i=0;i<9;i++)
//		printf("%d\n",float2int(*(data_ptr+i),8));
}
