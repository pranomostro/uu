#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int nalread(char* in, size_t* len);
void* resize(void* data, size_t old, size_t new);

int main(void)
{
	char* in;
	size_t inlen=4;
	in=(char*)calloc(inlen, sizeof(char));

	while(nalread(in, &inlen)>0)
		puts(in);

	return 0;
}

int nalread(char* in, size_t* len)
{
	char* next=in;
	int oldlen=*len;

	do
	{
		next=fgets(next, oldlen, stdin);
		*len*=2;
		in=resize(in, oldlen*sizeof(char), *len*sizeof(char));
		next=in+oldlen;
	}
	while(in[strlen(in)-1!='\n']&&next!=NULL);

	return strlen(in);
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
