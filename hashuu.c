/*unsorted uniq with hashes in an array that is shifted for inserting*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITLEN 16

long hashs(char* s, size_t len);
long* resize(long* data, size_t old, size_t new);
int linsearch(long key, long* data, size_t len);

int main(int argc, char** argv)
{
	size_t hashlen=INITLEN, pos=0;
	long hash;
	char s[BUFSIZ];
	long* hashes=(long*)malloc(INITLEN*sizeof(long));

	while(fgets(s, BUFSIZ, stdin)!=NULL)
	{
		hash=hashs(s, strlen(s));
		if(linsearch(hash, hashes, pos))
		{
			if(pos>=hashlen)
			{
				hashlen*=2;
				hashes=resize(hashes, pos, hashlen);
				if(hashes==NULL)
					break;
			}
			hashes[pos++]=hash;
			printf(s);
		}
	}

	free(hashes);

	return 0;
}

/*taken from 9base, rc/var.c*/

long hashs(char* s, size_t len)
{
	int h=0, i=1;
	while(*s&&i<len) h+=(*s++)<<4*i++;
	return h;
}

long* resize(long* data, size_t old, size_t new)
{
	size_t c;
	long* na=(long*)realloc(data, new*sizeof(long));
	if(na==NULL)
	{
		na=(long*)malloc(new*sizeof(long));
		if(na==NULL)
		{
			fprintf(stderr, "error: no memory left, exiting.\n");
			return NULL;
		}
		for(c=0; c<=old; c++)
			na[c]=data[c];
	}
	return na;
}

int linsearch(long key, long* data, size_t len)
{
	while(len-->0)
		if(data[len]==key)
			return 0;
	return 1;
}
