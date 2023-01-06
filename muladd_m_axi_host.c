#include <stdio.h>
#include <stdlib.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xmuladd.h"
#include "xil_cache.h"

#define SIZE 16

//DMA転送元の基底アドレス。型変換はなくてもいいかもしれない。
#define a_base_addr  ((volatile int *)0x10000000)
#define b_base_addr  ((volatile int *)0x10000080)

XMuladd Instance;

int main()
{

	u32 ua[SIZE],ub[SIZE];
	int res;

	if (XMuladd_Initialize(&Instance,XPAR_XMULADD_0_DEVICE_ID)!=XST_SUCCESS) {
		xil_printf("init error\n");
		return XST_FAILURE;
	}

	XMuladd_Set_a(&Instance,(u64)a_base_addr);
	XMuladd_Set_b(&Instance,(u64)b_base_addr);

	for (int i = 0;i < SIZE;i++) {
		a_base_addr[i] = ua[i] = i+1;
		b_base_addr[i] = ub[i] = i+1;
	}

    Xil_DCacheFlush();

	XMuladd_Start(&Instance);
	while(XMuladd_IsDone(&Instance)==0);

	res=XMuladd_Get_return(&Instance);
	xil_printf("result %d\n\r",res);

	return 0;
}
