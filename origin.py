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
		idx = j_4 + (k>>2) + (l * height);
		*(out_data + idx) = 0;
		for (m = 3; m >= 0; m--)
			*(out_data + idx) += *(tmp_data+ (k>>2<<2) + m) * *(H+ (l<<2)+m);
		
	}
}