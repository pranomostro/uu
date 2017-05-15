#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"

size_t nalread(char** in, size_t* len, FILE* input)
{
	size_t readlen=(*len-1)/2, res=0, fw;
	char* readpos=*in;

	while(1)
	{
		if(fgets(readpos, readlen, input)==NULL)
			break;
		res=strnlen(readpos, readlen);
		if(readpos[res-1]=='\n')
			break;
		fw=(readpos-(*in))+res;
		*in=(char*)reallocarray(*in, (*len)*2, sizeof(**in));
		if(!*in)
			return 0;
		(*len)*=2;
		readpos=(*in)+fw;
		readlen=(*len)-(readpos-*in);
	}

	return (readpos-*in)+res;
}
