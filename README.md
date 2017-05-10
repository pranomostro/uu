What for?
=========

uu can be used when you would like to apply uniq to an input but need to
keep the order of the input lines or you don't want your entire input to
be consumed before processing it (like with `sort | uniq`).
For example, if you want have got a dictionary with the words sorted
after frequency and you want to convert the dictionary to lowercase
while keeping the order of the dictionary, you would write:

	tr 'A-Z' 'a-z' dict | uu >lcdict

This works especially well for huge text streams which would not fit
into RAM for sorting.

Versions
--------

uu is currently implemented in three programs:

-	uu is the recommended one. It is extremely simple
	to understand, memory safe and does not make any errors.
	It uses more memory than fnuu.
-	fnuu (false negatives uu) is an experiment if it is possible to write
	a faster and more memory efficient uu. uu saves the input lines in
	RAM, while fnuu only stores their 32-bit hashes.
	fnuu is written in C and slightly faster than uu.
-	bauu is also written in C, stores the 32-bit hashes of the input lines
	in a bitarray. It uses 512MB RAM constantly, and is twice as fast as the
	other two versions. bauu hash the same hash collisions as fnuu, which
	means that it has the same false negatives.

Installation
------------

Just type

	make install

Thanks and license
==================

Thanks to [jwerle](https://www.github.com/jwerle) for his
implementation of murmurhash.
Licensed under the [MIT license](./LICENSE).
