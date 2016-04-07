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

/*for fnuu*/

const int INITLEN=256;
const int BUCKETS=10000;

/*for bauu*/

const int BALEN=134217728;
const int BITSPERELEM=32;
const int SHIFT=5;

/* The factor for resizing arrays and strings during input */

const int RESIZEFACTOR=2;
