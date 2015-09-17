#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int afind(int key, int* data, int len);

int main(void)
{
	int c, in, pos;
	int* arr=(int*)calloc(16, sizeof(int));

	for(c=0; c<16; c++)
	{
		scanf("%i", &in);
		pos=afind(in, arr, c);
		memmove(arr+1, arr, c*sizeof(int));
		arr[pos]=in;
	}

	return 0;
}

int afind(int key, int* data, int len)
{
	int low, mid, high;
}
