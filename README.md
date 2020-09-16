Static Sort 
===========

A very simple header only C++ class to create a static sort.   
Uses templates to generate a Bose-Nelson sorting network on compile time.  

To enable the magic to happen, please turn on optimizations. =)  
(-O2 or -O3 depending on your compiler)

Installation
------------

Just copy `include/static_sort.h` into your project and `#include` it. =)  

You can also copy and paste the code from `static_sort.h` directly!  

Requirements
------------

A C++98 and above compiler.

Usage
-----

```c++
// Fast for small randomly ordered arrays.
StaticSort<10> boseNelsonSort;
int a[10] = {6,7,3,2,4,0,9,1,8,5};
boseNelsonSort(a);
boseNelsonSort(a, std::less<int>()); // with less than comparator

// Fast for small arrays. Randomly ordered, reversed, in order.
StaticTimSort<10> timBoseNelsonSort; 
int b[10] = {6,7,3,2,4,0,9,1,8,5};
timBoseNelsonSort(b);
timBoseNelsonSort(b, std::less<int>()); // with less than comparator
``` 

Works on std::vectors, plain old arrays, or other array-like objects.  

Accepts custom less than comparator.

Benchmarks
----------

Here are the number of milliseconds taken to sort 1 million arrays of ints.  
Compiled with clang -O3, a Macbook Air (Mid-2012) Intel i7-3667U 2GHz.

**Random Order**  
`6,7,3,2,4,0,9,1,8,5` -> `0,1,2,3,4,5,6,7,8,9` 

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_random.png" alt="Sort Timings (Random)" width="680"/>

**Reversed Order**  
`9,8,7,6,5,4,3,2,1,0` -> `0,1,2,3,4,5,6,7,8,9` 

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_reversed.png" alt="Sort Timings (Reversed)" width="680"/>

**In Order**  
`0,1,2,3,4,5,6,7,8,9` -> `0,1,2,3,4,5,6,7,8,9` 

<img src="https://raw.githubusercontent.com/webby1111/Static-Sort/master/timings_n_ordered.png" alt="Sort Timings (Ordered)" width="680"/>

For real-world data, it is recommended you use StaticTimSort. 

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

Notes
-----

### On Sorting Pairs

If you want to sort pairs of 32-bit numbers (e.g. `std::pair<int, int>`),  
it is recommended that you pack each pair of numbers into a single 64-bit number.  
This will nudge the compiler to generate min/max instructions for fastest performance.  

The overhead of packing and unpacking the pairs is negligible.  
Sorting packed pairs is approximately 4-5x faster than sorting unpacked pairs.  

At the time of writing, even the best modern compilers are unable to optimize this automatically.  

For a simple example and benchmark, please look into `bench_pair_sort.h`.  

It includes a little helper class for packing various types of 32-bit number pairs.  

### For Real World Data

Use StaticTimSort. 

Like it?
--------

Give it a star!  

Let me know if you have used this library in any of your projects.  

It helps me understand how it is used and plan new features.  


Change Log
----------

**10 June 2020**

- Added example for sorting pairs.

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

License
-------

MIT