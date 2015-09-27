#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int afind(int key, int* data, int len);

int main(void)
{
	int c, in, pos;
	int arr[16];

	for(c=0; c<16; c++)
		arr[c]=0;

	c=0;

	while(scanf("%d", &in)!=EOF)
	{
		pos=afind(in, arr, c);
		memmove(arr+pos+1, arr+pos, c*sizeof(int));
		arr[pos]=in;
		c++;
	}

	for(c=0; c<16; c++)
		printf("%i\n", arr[c]);

	return 0;
}

int afind(int key, int* data, int len)
{
	if(len<=0||data[0]>=key)
		return 0;
	else if (data[len-1]<key)
		return len;

	int low, mid, high;

	high=len-1;
	low=0;
	mid=(int)((float)(data[high]-data[low])/(float)(key-data[low]))*len;

	return mid;
}
