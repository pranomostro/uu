/*unsorted uniq with hashes in an array of pointers, hashes are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "murmurhash.h"

#define INITLEN 256
#define BUCKETS 10000

int binfind(uint32_t key, uint32_t* data, int len);
void* resize(void* data, size_t old, size_t new);
uint32_t hash(const char *key, uint32_t len, uint32_t seed);

int main(void)
{
	int i, bucket;
	int pos;
	size_t maxsize[BUCKETS], len[BUCKETS];
	char input[BUFSIZ];
	uint32_t hashval;
	uint32_t* hashes[BUCKETS];

	for(i=0; i<=BUCKETS-1; i++)
	{
		hashes[i]=(uint32_t*)calloc(INITLEN, sizeof(uint32_t));
		if(hashes[i]==NULL)
		{
			fputs("error, no memory left, exiting", stderr);
			for(i--; i>=0; i--)
				free(hashes[i]);
			exit(1);
		}
		len[i]=0;
		maxsize[i]=INITLEN;
	}

	while(fgets(input, BUFSIZ, stdin)!=NULL)
	{
		hashval=murmurhash(input, strlen(input), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=binfind(hashval, hashes[bucket], len[bucket]);

		if(hashes[bucket][pos]!=hashval)
		{
			if(len[bucket]>=maxsize[bucket]-1)
			{
				maxsize[bucket]=len[bucket]*2;
				hashes[bucket]=resize(hashes[bucket], len[bucket]*sizeof(uint32_t), maxsize[bucket]*sizeof(uint32_t));
			}
			memmove(hashes[bucket]+pos+1, hashes[bucket]+pos, (len[bucket]-pos)*sizeof(uint32_t));
			hashes[bucket][pos]=hashval;
			len[bucket]++;
			fputs(input, stdout);
		}
	}

	for(i=0; i<=BUCKETS-1; i++)
		free(hashes[i]);

	return 0;
}

/*Taken from »The C programming language«, adapted for my needs*/

int binfind(uint32_t key, uint32_t* data, int len)
{
	int low, high, mid;
	low=0;
	high=len-1;
	mid=(low+high)/2;

	if(len<=0)
		return 0;

	while(low<=high&&data[mid]!=key)
	{
		mid=(low+high)/2;
		if(data[mid]<key)
			low=mid+1;
		else
			high=mid-1;
	}
	return data[mid]<key?mid+1:mid;
}

void* resize(void* data, size_t old, size_t new)
{
	void* na=realloc(data, new);
	if(na==NULL)
	{
		na=malloc(new);
		if(na==NULL)
		{
			fputs("error: no memory left, exiting.", stderr);
			return NULL;
		}
		memcpy(na, data, old);
		free(data);
	}
	return na;
}
