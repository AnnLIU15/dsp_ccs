/*
 * main.c
 */

#include <stdio.h>
#include "include/func.h"
int main(void)
{
	/* file to load and the save path */
	const char *hw1_2_in = "../data/lena512.bmp";
	//const char* hw1_out = "C:/Users/Ann/Desktop/output/lena512_bilinear.bmp";
	const char *hw2_out = "../output/lena512_bilinear_sa.bmp";
	//uint8_t success_hw1 = bilinear_interpolation(hw1_2_in, hw1_out, 1.5, 0.666666666666667, 0);
	/* for test */
	uint8_t success_hw2 = bilinear_interpolation(hw1_2_in,hw2_out,1.5,0.666666666666667,1);
	if (success_hw2 == 0)
		printf("success_hw2!\n");
	else if (success_hw2 == 1)
		printf("It is not BMP file or haven't open file! Please check your input!\n");
	else if (success_hw2 == 2)
		printf("times * scale_factor not equal to 1!\n");
	else
	{
		printf("Unknown error!\n");
	}
}
