/*unsorted uniq with entries in an array of pointers, entries are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "config.h"
#include "deps/murmurhash/murmurhash.h"

char* nalread(char* in, size_t* len);
int afind(uint32_t key, uint32_t* data, int len);
void* resize(void* data, size_t old, size_t new);
uint32_t hash(const char *key, uint32_t len, uint32_t seed);

typedef struct
{
	uint32_t* entries;
	size_t len, maxlen;
} Bucket;

typedef struct
{
	uint32_t hash;
	char fchar;
} Entry;

int main(void)
{
	int i, bucket, pos;
	size_t inputsize=BUFSIZ;
	uint32_t hashval;
	char* input=(char*)calloc(inputsize, sizeof(char));
	Bucket values[BUCKETS];

	for(i=0; i<=BUCKETS-1; i++)
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
		values[i].maxlen=INITLEN;
	}

	while((input=nalread(input, &inputsize))!=NULL)
	{
		hashval=murmurhash(input, strlen(input), 0xA17A1111);
		bucket=hashval%BUCKETS;
		pos=afind(hashval, values[bucket].entries, values[bucket].len);

		if(values[bucket].entries[pos]!=hashval)
		{
			if(values[bucket].len>=values[bucket].maxlen)
			{
				values[bucket].maxlen=values[bucket].len*RESIZEFACTOR;
				values[bucket].entries=resize(values[bucket].entries,
					values[bucket].len*sizeof(uint32_t),
					values[bucket].maxlen*sizeof(uint32_t));
			}

			memmove(values[bucket].entries+pos+1,
				values[bucket].entries+pos,
				(values[bucket].len-pos)*sizeof(uint32_t));

			values[bucket].entries[pos]=hashval;
			values[bucket].len++;
			fputs(input, stdout);
		}
	}

	for(i=0; i<=BUCKETS-1; i++)
		free(values[i].entries);

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
			in=(char*)resize(in, sizeof(char)*(*len), sizeof(char)*(*len*RESIZEFACTOR));
			if(in==NULL)
				return in;
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
