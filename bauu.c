/*unsorted uniq with entries in an array of pointers, entries are inserted*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "config.h"
#include "deps/murmurhash/murmurhash.h"

char* nalread(char* in, size_t* len, FILE* input);
void* resize(void* data, size_t old, size_t new);
uint32_t hash(const char *key, uint32_t len, uint32_t seed);

int main(void)
{
	int i;
	size_t inputsize=BUFSIZ;
	uint32_t hashval;
	char* input=(char*)calloc(inputsize, sizeof(char));
	uint32_t* bitarray=calloc(BALEN, sizeof(uint32_t));

	for(i=0; i<BALEN; i++)
		bitarray[i]&=0;

	while((input=nalread(input, &inputsize, stdin))!=NULL)
	{
		hashval=murmurhash(input, strnlen(input, inputsize), 0xA17A1111);
		if(!(bitarray[hashval>>SHIFT]&(1<<hashval%BITSPERELEM)))
		{
			printf(input);
			bitarray[hashval>>SHIFT]|=(1<<hashval%BITSPERELEM);
		}
	}

	free(input);
	free(bitarray);

	return 0;
}

char* nalread(char* in, size_t* len, FILE* input)
{
	size_t readlen=(*len-1)/2;
	char* readpos=in;

	while(1)
	{
		if(fgets(readpos, readlen, input)==NULL)
			break;
		if(readpos[strnlen(readpos, *len)-1]=='\n')
			break;
		in=(char*)resize(in, sizeof(char)*(*len), sizeof(char)*((*len)*RESIZEFACTOR));
		(*len)*=RESIZEFACTOR;
		readlen=(*len)-strnlen(in, *len)-1;
		readpos=in+strnlen(in, *len);
	}

	return feof(input)?NULL:in;
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
