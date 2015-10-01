#include <stdlib.h>
#include <stdio.h>

int nalread(char* in, size_t len);
void* resize(void* data, size_t old, size_t new);

int main(void)
{
	char* in;
	size_t inlen=16;
	in=(char*)calloc(inlen, sizeof(char)*inlen);

	return 0;
}

int nalread(char* in, size_t len)
{

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
