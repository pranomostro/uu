/*unsorted uniq with hashes in an array that is shifted for inserting*/

#include <stdlib.h>
#include <stdio.h>

#define INITLEN 16

long hash(char* s, size_t len);
size_t binfind(long key, long* data, size_t len);
long* resize(long* data, size_t new);
void insert(long* data, size_t pos, long val);

int main(int argc, char** argv)
{
	size_t hashlen=INITLEN, pos=0;
	long hash;
	char s[BUFSIZ];
	long* hashes=(long*)malloc(INITLEN*sizeof(long));

	while(fgets(s, BUFSIZ, stdin)!=EOF)
	{
		hash=hash(s, strlen(s));
		if(pos>=hashlen)
		{
			hashlen*=2;
			hashes=resize(hashes, hashlen);
		}
		hashes[pos]=hash;
	}

	free(hashes);

	return 0;
}

/*taken from 9base, rc/var.c*/

long hash(char* s, size_t len)
{
	int h=0, i=1;
	while(*s&&i<len) h+=*s++*i++;
	return h;
}

long* resize(long* data, size_t new)
{
	/*change this*/
	return data;
}
