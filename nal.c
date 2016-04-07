#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

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
