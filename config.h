/*
	This file provides configuration
	options for uu, which are mostly
	related to performance optimizations.
*/

/*
	The initial length of the buckets
	and the number of buckets.
	Increasing these numbers will usually
	increase performance.
*/

/*for fnuu*/

#define INITLEN 256
#define BUCKETS 10000

/*for bauu*/

#define BALEN 134217728
#define BITSPERELEM 32
#define SHIFT 5

/* The factor for resizing arrays and strings during input */

#define RESIZEFACTOR 2

/*function definitions from nal.c*/

char* nalread(char* in, size_t* len, FILE* input);
void* resize(void* data, size_t old, size_t new);
