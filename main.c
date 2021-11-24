/*
 * main.c
 */

#include <stdio.h>
#include "include/func.h"
int main(void)
{
	const char *hw4_in = "../data/data.yuv";
	const char *hw4_out = "../output/data_process.txt";
	uint8_t success_hw4 = transfer_arr_p(hw4_in, hw4_out,352,288);
	if (success_hw4 == 0)
		printf("success_hw4!\n");
	else if (success_hw4 == 1)
		printf("Can't open file! Please check your input!\n");
	else
	{
		printf("Unknown error!\n");
	}
}
