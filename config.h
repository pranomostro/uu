/*
	This file provides configuration
	options for fnuu, which are mostly
	related to performance optimizations.
*/

/*
	The initial length of the buckets
	an the number of buckets.
	Increasing these numbers will increase
	performance.
*/

#define INITLEN 256
#define BUCKETS 10000

/* The factor for resizing arrays and strings during input */

#define RESIZEFACTOR 2
