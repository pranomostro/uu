/*unsorted uniq with entries in an array of pointers, entries are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MIDCALC ((float)(key-data[low])/(float)(data[high]-data[low]))*(float)(high-low)+low

#include "config.h"
#include "deps/murmurhash/murmurhash.h"

size_t abinfind(uint32_t key, uint32_t* data, size_t len);

typedef struct
{
	uint32_t* entries;
	size_t len, cap;
} Bucket;

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

	while((input=nalread(input, &inputsize, stdin))!=NULL)
	{
		hashval=murmurhash(input, strnlen(input, inputsize), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=abinfind(hashval, values[bucket].entries, values[bucket].len);

		if(pos==values[bucket].len||values[bucket].entries[pos]!=hashval)
		{
			if(values[bucket].len>=values[bucket].cap)
			{
				values[bucket].cap=values[bucket].len*RESIZEFACTOR;
				values[bucket].entries=nalgrow(values[bucket].entries,
					values[bucket].len*sizeof(uint32_t),
					values[bucket].cap*sizeof(uint32_t));
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

size_t abinfind(uint32_t key, uint32_t* data, size_t len)
{
	if(len<=0||key<=data[0])
		return 0;
	else if(key>data[len-1])
		return len;

	signed int low, high, mid;
	low=0;
	high=len-1;
	mid=MIDCALC;

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

		mid=MIDCALC;
		if(data[mid]<key)
			low=mid+1;
		else
			high=mid-1;
	}
	return data[mid]<key?mid+1:mid;
}
