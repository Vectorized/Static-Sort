Static Sort 
===========

A very simple header only C++ class to create a static sort.   
Uses templates to generate a Bose-Nelson sorting network on compile time.  

To enable the magic to happen, please turn on optimizations. =)  
(-O2 or -O3 depending on your compiler)

Benchmarks
----------

Here are the average clocks per sort against other static sorts from   
[http://stackoverflow.com/questions/2786899/fastest-sort-of-fixed-length-6-int-array]   
(Lower is better)  

	Clang -O3 :
	----------
	Direct call to qsort library function   : 342.26
	Naive implementation (insertion sort)   : 136.76
	Insertion Sort (Daniel Stutzbach)       : 101.37
	Insertion Sort Unrolled                 : 110.27
	Rank Order                              : 90.88
	Rank Order with registers               : 90.29
	Sorting Networks (Daniel Stutzbach)     : 93.66
	Sorting Networks (Paul R)               : 31.54
	Sorting Networks 12 with Fast Swap      : 32.06
	Sorting Networks 12 reordered Swap      : 29.74
	Reordered Sorting Network w/ fast swap  : 25.28
	Templated Sorting Network               : 25.01
	
	Intel Compiler 16.0 -O3 :
	------------------------
	Direct call to qsort library function   : 344.51
	Naive implementation (insertion sort)   : 100.48
	Insertion Sort (Daniel Stutzbach)       : 102.27
	Insertion Sort Unrolled                 : 91.09
	Rank Order                              : 41.56
	Rank Order with registers               : 36.33
	Sorting Networks (Daniel Stutzbach)     : 89.72
	Sorting Networks (Paul R)               : 43.71
	Sorting Networks 12 with Fast Swap      : 40.88
	Sorting Networks 12 reordered Swap      : 37.44
	Reordered Sorting Network w/ fast swap  : 26.25
	Templated Sorting Network               : 29.58

References
----------

- http://stackoverflow.com/questions/2786899/fastest-sort-of-fixed-length-6-int-array
- https://github.com/atinm/bose-nelson/blob/master/bose-nelson.c
