/*unsorted uniq with entries in an array of pointers, entries are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "config.h"
#include "murmurhash.h"

size_t midcalc(uint32_t key, uint32_t* data, size_t high, size_t low);
size_t ifind(uint32_t key, uint32_t* data, size_t len);

typedef struct
{
	uint32_t* entries;
	size_t len, cap;
} Bucket;

size_t midcalc(uint32_t key, uint32_t* data, size_t high, size_t low)
{
	if(data[high]==data[low])
		return low;
	float kld=key-data[low], hld=data[high]-data[low];
	double hl=high-low;
	return (kld/hld)*hl+low;
}

size_t ifind(uint32_t key, uint32_t* data, size_t len)
{
	if(len<=0||key<=data[0])
		return 0;
	else if(key>data[len-1])
		return len;

	size_t low, high, mid;
	low=0;
	high=len-1;
	mid=midcalc(key, data, high, low);

	while(low<=high&&data[mid]!=key)
	{
		if(data[low]>key)
		{
			mid=low-1;
			break;
		}
		else if(data[high]<key)
		{
			mid=high+1;
			break;
		}

		mid=midcalc(key, data, high, low);
		if(data[mid]<key)
			low=mid+1;
		else
			high=mid-1;
	}
	return data[mid]<key?mid+1:mid;
}

int main(void)
{
	int i;
	size_t inputsize=BUFSIZ, pos, bucket;
	uint32_t hashval;
	char* input=(char*)calloc(inputsize, sizeof(char));
	Bucket values[BUCKETS];

	for(i=0; i<BUCKETS; i++)
	{
		values[i].entries=(uint32_t*)calloc(INITLEN, sizeof(uint32_t));
		if(values[i].entries==NULL)
		{
			fputs("error, no memory left, exiting", stderr);
			for(i--; i>=0; i--)
				free(values[i].entries);
			exit(1);
		}
		values[i].len=0;
		values[i].cap=INITLEN;
	}

	while(nalread(&input, &inputsize, stdin)&&!feof(stdin))
	{
		hashval=murmurhash(input, strnlen(input, inputsize), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=ifind(hashval, values[bucket].entries, values[bucket].len);

		if(pos==values[bucket].len||values[bucket].entries[pos]!=hashval)
		{
			if(values[bucket].len>=values[bucket].cap)
			{
				values[bucket].cap=values[bucket].len*RESIZEFACTOR;
				values[bucket].entries=(uint32_t *)reallocarray(values[bucket].entries,
					values[bucket].cap*sizeof(uint32_t), sizeof(uint32_t));
			}

			memmove(values[bucket].entries+pos+1,
				values[bucket].entries+pos,
				(values[bucket].len-pos)*sizeof(uint32_t));

			values[bucket].entries[pos]=hashval;
			values[bucket].len++;
			fputs(input, stdout);
		}
	}

	for(i=0; i<BUCKETS; i++)
		free(values[i].entries);
	free(input);

	return 0;
}
