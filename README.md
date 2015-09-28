What for?
=========

uu can be used when you would like to apply uniq to an
input but need to keep the order of the input lines or
you don't want your entire input to be consumed before
processing it (like with `sort | uniq`).
For example, if you want have got a dictionary with the
words sorted after frequency and you want to convert the
dictionary to lowercase while keeping the order of the
dictionary, you would write
	tr 'A-Z' 'a-z' dict | uu >lcdict

A small utility
===============

uu is a text filter utility similar to the well known and
loved uniq. The only real difference between uu and uniq
is that in uniq, the second and succeding copies of repeated
lines are removed, while with uu, the lines are not required
to be adjacent.

uu is currently implemented in two languages:
-the awk version is the recommended one. it is extremely simple
	to understand, memory safe, does not make any errors
	and is in nearly every point the better one of these
	two implementations, except when…
-the C version is rather an experiment if it is possible to write a
	faster and more memory efficient version. while the awk program does
	not make any errors, it saves all the input lines, while
	the C program only holds the 32-bit hashes for every input line.
	the C version is also already slightly faster
	than uu.awk when it is compiled with optimization,
	and it is improved further.

Installation
============

Just type
	make install
and enjoy the experience.

Thanks and license
==================

The whole thing is licensed under the MIT-license.
Thanks to [jwerle](https://www.github.com/jwerle) for the murmurhash library.
