#define SIZE 16


int muladd(volatile int a[SIZE], volatile int b[SIZE])
{
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=m_axi port=a bundle=gmem offset=slave depth=16
#pragma HLS INTERFACE mode=m_axi port=b bundle=gmem offset=slave depth=16
#pragma HLS INTERFACE mode=s_axilite port=a bundle=control
#pragma HLS INTERFACE mode=s_axilite port=b bundle=control

	int temp;
	for(int i = 0;i < SIZE;i++){
		temp += a[i]*b[i];
	}
	//printf("%d\n",temp);
	return temp;
}
