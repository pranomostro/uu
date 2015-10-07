#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* nalread(char* in, size_t* len);
void* resize(void* data, size_t old, size_t new);

int main(void)
{
	char* in;
	size_t inlen=4;
	in=(char*)calloc(inlen, sizeof(char));

	while((in=nalread(in, &inlen))!=NULL)
			printf(in);
	free(in);

	return 0;
}

char* nalread(char* in, size_t* len)
{
	char c;
	size_t count=0;

	while((c=getc(stdin))!='\n'&&!feof(stdin))
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
