#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int nalread(char* in, size_t* len);
void* resize(void* data, size_t old, size_t new);

int main(void)
{
	char* in;
	size_t inlen=4;
	in=(char*)calloc(inlen, sizeof(char));

	while(nalread(in, &inlen)>=0)
		printf(in);

	return 0;
}

int nalread(char* in, size_t* len)
{
	char c;
	int count=0;

	c=getc(stdin);

	while(c!='\n'&&!feof(stdin))
	{
		if(count>=*(len)-3)
		{
			in=resize(in, sizeof(char)*(*len), sizeof(char)*(*len*2));
			*len*=2;
		}
		in[count++]=c;
		c=getc(stdin);
	}

	in[count++]='\n';
	in[count]='\0';

	return feof(stdin)?-1:count-1;
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
