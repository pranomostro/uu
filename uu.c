/*unsorted uniq with hashes in an array of pointers, hashes are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "murmurhash.h"

#define INITLEN 256
#define BUCKETS 10000

char* nalread(char* in, size_t* len);
int afind(uint32_t key, uint32_t* data, int len);
void* resize(void* data, size_t old, size_t new);
uint32_t hash(const char *key, uint32_t len, uint32_t seed);

int main(void)
{
	int i, bucket;
	int pos;
	size_t maxsize[BUCKETS], len[BUCKETS], inputsize=BUFSIZ;
	char* input=(char*)calloc(inputsize, sizeof(char));
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

	while((input=nalread(input, &inputsize))!=NULL)
	{
		hashval=murmurhash(input, strlen(input), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=afind(hashval, hashes[bucket], len[bucket]);

		if(hashes[bucket][pos]!=hashval)
		{
			if(len[bucket]>=maxsize[bucket])
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

char* nalread(char* in, size_t* len)
{
	char c;
	size_t count=0;

	c=getc(stdin);

	while(c!='\n'&&!feof(stdin))
	{
		if(count>=*(len)-3)
		{
			in=(char*)resize(in, sizeof(char)*(*len), sizeof(char)*(*len*2));
			(*len)*=2;
		}
		in[count++]=c;
		c=getc(stdin);
	}

	in[count++]='\n';
	in[count]='\0';

	return feof(stdin)?NULL:in;
}

int afind(uint32_t key, uint32_t* data, int len)
{
	if(len<=0||data[0]>=key)
		return 0;
	else if(data[len-1]<key)
		return len;

	float high;
	int mid, dir;

	high=(float)(data[len-1]-data[0]);
	mid=(int)((((float)key-data[0])/high)*(float)(len-1));

	if(data[mid]<key)
		dir=1;
	else
		dir=-1;

	while(!(data[mid]>=key&&data[mid-1]<key))
		mid+=dir;

	return mid;
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
