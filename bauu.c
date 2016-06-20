/*bitarray, hashed lines are set.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "config.h"
#include "deps/murmurhash/murmurhash.h"

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
			fputs(input, stdout);
			bitarray[hashval>>SHIFT]|=(1<<hashval%BITSPERELEM);
		}
	}

	free(input);
	free(bitarray);

	return 0;
}
