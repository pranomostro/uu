/*unsorted uniq with hashes in an array of pointers, hashes are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define INITLEN 256
#define BUCKETS 10000

int binfind(uint32_t key, uint32_t* data, int len);
uint32_t* resize(uint32_t* data, size_t old, size_t new);
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
		len[i]=0;
		maxsize[i]=INITLEN;
	}

	while(fgets(input, BUFSIZ, stdin)!=NULL)
	{
		hashval=hash(input, strlen(input), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=binfind(hashval, hashes[bucket], len[bucket]);

		if(pos==-1)
			break;

		if(hashes[bucket][pos]!=hashval)
		{
			if(len[bucket]>=maxsize[bucket]-1)
			{
				maxsize[bucket]=len[bucket]*2;
				hashes[bucket]=resize(hashes[bucket], len[bucket], maxsize[bucket]);
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
	if(data==NULL)
		return -1;

	while(low<=high)
	{
		mid=(low+high)/2;
		if(data[mid]<key)
			low=mid+1;
		else if(data[mid]==key)
			break;
		else
			high=mid-1;
	}
	return data[mid]<key?mid+1:mid;
}

uint32_t* resize(uint32_t* data, size_t old, size_t new)
{
	size_t c;
	uint32_t* na=(uint32_t*)realloc(data, new*sizeof(uint32_t));
	if(na==NULL)
	{
		na=(uint32_t*)malloc(new*sizeof(uint32_t));
		if(na==NULL)
		{
			fputs("error: no memory left, exiting.", stderr);
			return NULL;
		}
		for(c=0; c<=old; c++)
			na[c]=data[c];
		free(data);
	}
	return na;
}

/*Murmur3 hashing algorithm, taken from Wikipedia. Tested with different datasets, don't worry.*/

uint32_t hash(const char *key, uint32_t len, uint32_t seed)
{
	static const uint32_t c1 = 0xcc9e2d51;
	static const uint32_t c2 = 0x1b873593;
	static const uint32_t r1 = 15;
	static const uint32_t r2 = 13;
	static const uint32_t m = 5;
	static const uint32_t n = 0xe6546b64;

	uint32_t hash = seed;

	const int nblocks = len / 4;
	const uint32_t *blocks = (const uint32_t *) key;
	int i;
	for (i = 0; i < nblocks; i++)
	{
		uint32_t k = blocks[i];
		k *= c1;
		k = (k << r1) | (k >> (32 - r1));
		k *= c2;

		hash ^= k;
		hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
	}

	const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
	uint32_t k1 = 0;

	switch (len & 3)
	{
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = (k1 << r1) | (k1 >> (32 - r1));
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}
