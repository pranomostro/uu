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
