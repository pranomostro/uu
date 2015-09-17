#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int afind(int key, int* data, int len);

int main(void)
{
	int c, in, pos;
	int arr[16];

	for(c=0; c<16; c++)
	{
		scanf("%i\n", &in);
		pos=afind(in, arr, c);
		memmove(arr+c+1, arr+c, c*sizeof(int));
		arr[pos]=in;
	}

	for(c=0; c<16; c++)
		printf("%i\n", c);

	return 0;
}

int afind(int key, int* data, int len)
{
	if(len<=0||data[0]>=key)
		return 0;
	else if (data[len-1]<key)
		return len;

	int low, mid, high;
	return 0;
}
