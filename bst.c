#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 65536

size_t binfind(int* data, size_t len, int key);

int main(int argc, char** argv)
{
	int c, rval, fval, pos;
	int sample[SIZE];
	srand((unsigned)time(NULL));

	for(c=rval=0; c<=SIZE-1; c++, rval+=rand()%4)
		sample[c]=rval;

	while(scanf("%d", &fval)!=0)
	{
		pos=binfind(sample, SIZE, fval);
		printf((pos==-1)?"":"[%i]: %i\n", pos, sample[pos]);
	}

	return 0;
}

/*Taken from »The C programming language«, adapted for my needs*/

size_t binfind(int* data, size_t len, int key)
{
	size_t low, high, mid;
	low=0;
	high=len-1;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(data[mid]<key)
			low=mid+1;
		else if(data[mid]>key)
			high=mid-1;
		else
			break;
	}
	return data[mid]<key?mid+1:mid;
}
