Static Sort 
===========

A very simple header only C++ class to create a static sort.   
Uses templates to generate a Bose-Nelson sorting network on compile time.  

To enable the magic to happen, please turn on optimizations. =)  
(-O2 or -O3 depending on your compiler)

How To Use
----------

Simply `static_sort.h` into your project and `#include` it. =)  

You can also copy and paste the code from `static_sort.h` directly!   

Benchmarks
----------

Here are the number of milliseconds taken to sort 1 million arrays of ints.  
Compiled with clang -O3, a Macbook Air (Mid-2012) Intel i7-3667U 2GHz.

**Random Order**

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_random.png" alt="Sort Timings (Random)" width="680"/>

**Reversed Order**

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_reversed.png" alt="Sort Timings (Reversed)" width="680"/>

**In Order**

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_ordered.png" alt="Sort Timings (Ordered)" width="680"/>

Here are the average clocks per sort against other static sorts from   
[http://stackoverflow.com/questions/2786899/fastest-sort-of-fixed-length-6-int-array]   
(Lower is better)  

These timings are for randomly ordered arrays.

	Clang -O3 :
	----------
	Direct call to qsort library function       : 326.81
	Naive implementation (insertion sort)       : 132.98
	Insertion Sort (Daniel Stutzbach)           : 104.04
	Insertion Sort Unrolled                     : 99.64
	Insertion Sort Unrolled (Glenn Teitelbaum)  : 81.55
	Rank Order                                  : 44.01
	Rank Order with registers                   : 42.40
	Sorting Networks (Daniel Stutzbach)         : 88.06
	Sorting Networks (Paul R)                   : 31.64
	Sorting Networks 12 with Fast Swap          : 29.68
	Sorting Networks 12 reordered Swap          : 28.61
	Reordered Sorting Network w/ fast swap      : 24.63
	Templated Sorting Network (this class)      : 25.37
	
	Intel Compiler 16.0 -O3 :
	------------------------
	Direct call to qsort library function       : 325.28
	Naive implementation (insertion sort)       : 97.38
	Insertion Sort (Daniel Stutzbach)           : 108.97
	Insertion Sort Unrolled                     : 97.16
	Insertion Sort Unrolled (Glenn Teitelbaum)  : 109.65
	Rank Order                                  : 38.13
	Rank Order with registers                   : 32.96
	Sorting Networks (Daniel Stutzbach)         : 85.56
	Sorting Networks (Paul R)                   : 47.57
	Sorting Networks 12 with Fast Swap          : 41.13
	Sorting Networks 12 reordered Swap          : 37.42
	Reordered Sorting Network w/ fast swap      : 25.60
	Templated Sorting Network (this class)      : 29.09

Change Log
----------

**17 Oct 2019**

- Added argument to accept a less-than comparator.

- Added a TimSort inspired Tim-Bose-Nelson sort to handle the case of already ordered arrays.  
  This adds only a very tiny overhead, and is only activated for arrays of 8 or more elements.  
  On average, it beats all the other sorts (except for the sorting-network) on   
  random, in-order and reversed-order arrays. :)

References
----------

- http://stackoverflow.com/questions/2786899/fastest-sort-of-fixed-length-6-int-array
- https://github.com/atinm/bose-nelson/blob/master/bose-nelson.c

License (MIT)
-------------

Copyright (c) 2016 Kang Yue Sheng Benjamin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.