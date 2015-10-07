#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int nalread(char* in, int* len);
void* resize(void* data, int old, int new);

int main(void)
{
	char* in;
	int inlen=4;
	int read;
	in=(char*)calloc(inlen, sizeof(char));

	while((read=nalread(in, &inlen))>=0)
		write(1, in, read-1);

	free(in);

	return 0;
}

int nalread(char* in, int* len)
{
	char c;
	int count=0;

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

	return feof(stdin)?-1:count;
}

void* resize(void* data, int old, int new)
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
