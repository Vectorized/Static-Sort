#ifndef bench_10_h
#define bench_10_h

#include <iostream>
#include "static_sort.h"
#include "timer.h"

// Sort Net 10 from http://stackoverflow.com/a/32183266/3686594 in DarioP's answer
inline void sortNet10(int * const data) {  // ten-input sorting network by Waksman, 1969
	int swap;
	if (data[0] > data[5]) { swap = data[0]; data[0] = data[5]; data[5] = swap; }
	if (data[1] > data[6]) { swap = data[1]; data[1] = data[6]; data[6] = swap; }
	if (data[2] > data[7]) { swap = data[2]; data[2] = data[7]; data[7] = swap; }
	if (data[3] > data[8]) { swap = data[3]; data[3] = data[8]; data[8] = swap; }
	if (data[4] > data[9]) { swap = data[4]; data[4] = data[9]; data[9] = swap; }
	if (data[0] > data[3]) { swap = data[0]; data[0] = data[3]; data[3] = swap; }
	if (data[5] > data[8]) { swap = data[5]; data[5] = data[8]; data[8] = swap; }
	if (data[1] > data[4]) { swap = data[1]; data[1] = data[4]; data[4] = swap; }
	if (data[6] > data[9]) { swap = data[6]; data[6] = data[9]; data[9] = swap; }
	if (data[0] > data[2]) { swap = data[0]; data[0] = data[2]; data[2] = swap; }
	if (data[3] > data[6]) { swap = data[3]; data[3] = data[6]; data[6] = swap; }
	if (data[7] > data[9]) { swap = data[7]; data[7] = data[9]; data[9] = swap; }
	if (data[0] > data[1]) { swap = data[0]; data[0] = data[1]; data[1] = swap; }
	if (data[2] > data[4]) { swap = data[2]; data[2] = data[4]; data[4] = swap; }
	if (data[5] > data[7]) { swap = data[5]; data[5] = data[7]; data[7] = swap; }
	if (data[8] > data[9]) { swap = data[8]; data[8] = data[9]; data[9] = swap; }
	if (data[1] > data[2]) { swap = data[1]; data[1] = data[2]; data[2] = swap; }
	if (data[3] > data[5]) { swap = data[3]; data[3] = data[5]; data[5] = swap; }
	if (data[4] > data[6]) { swap = data[4]; data[4] = data[6]; data[6] = swap; }
	if (data[7] > data[8]) { swap = data[7]; data[7] = data[8]; data[8] = swap; }
	if (data[1] > data[3]) { swap = data[1]; data[1] = data[3]; data[3] = swap; }
	if (data[4] > data[7]) { swap = data[4]; data[4] = data[7]; data[7] = swap; }
	if (data[2] > data[5]) { swap = data[2]; data[2] = data[5]; data[5] = swap; }
	if (data[6] > data[8]) { swap = data[6]; data[6] = data[8]; data[8] = swap; }
	if (data[2] > data[3]) { swap = data[2]; data[2] = data[3]; data[3] = swap; }
	if (data[4] > data[5]) { swap = data[4]; data[4] = data[5]; data[5] = swap; }
	if (data[6] > data[7]) { swap = data[6]; data[6] = data[7]; data[7] = swap; }
	if (data[3] > data[4]) { swap = data[3]; data[3] = data[4]; data[4] = swap; }
	if (data[5] > data[6]) { swap = data[5]; data[5] = data[6]; data[6] = swap; }
}

template <class T> static inline void fill(int n, T *a)
{
	static int seed = 76521;
	while (n--) *a++ = (seed = seed * 1812433253 + 12345);
}

int main(int argc, const char * argv[])
{
	enum {
		NumTests = 1000000,
		NumElements = 10 ,
		TotalElements = NumElements * NumTests
	};
	
	{
		int *data = new int[TotalElements];
		fill(TotalElements, data);
		
		Timer timer;
		timer.start();
		
		for (unsigned i = 0; i < TotalElements; i += NumElements)
			sortNet10(data + i);
		
		timer.stop();
		
		std::cout
			<< "Sort 10 (hardcoded sort net 10): "
			<< timer.getElapsedMilliseconds() << std::endl;
		
		delete [] data;
	}

	{
		int *data = new int[TotalElements];
		fill(TotalElements, data);
		
		Timer timer;
		timer.start();
		
		StaticSort<10, int> staticSort;
		
		for (unsigned i = 0; i < TotalElements; i += NumElements)
			staticSort(data + i);
		
		timer.stop();
		
		std::cout
			<< "Sort 10 (templated Bose-Nelson): "
			<< timer.getElapsedMilliseconds() << std::endl;
		
		delete [] data;
	}
	
	
	return 0;
}

#endif