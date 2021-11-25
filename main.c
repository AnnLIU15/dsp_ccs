/*
 * main.c
 */

#include <stdio.h>
#include "include/func.h"
int main(void)
{
	uint8_t is_sa = 0;
	const char *hw4_in = "../data/data.yuv";
	const char *hw4_out_c = "../output/data_process.txt";
	const char *hw4_out_sa = "../output/data_process1.txt";
	uint8_t success_hw4;
	if(is_sa)
	{
		success_hw4 = transfer_arr_p(hw4_in, hw4_out_sa,352,288,is_sa);
	}
	else
	{
		success_hw4 = transfer_arr_p(hw4_in, hw4_out_c,352,288,is_sa);
	}
	if (success_hw4 == 0)
		printf("success_hw4!\n");
	else if (success_hw4 == 1)
		printf("Can't open file! Please check your input!\n");
	else
	{
		printf("Unknown error!\n");
	}
}
