//#define BENCH
#ifdef BENCH
#include "bench.h"
#else

#include "static_sort.h"

#include <iostream>
#include <vector>

int main(int argc, const char * argv[])
{
	enum {NUM_VALUES = 32};
	
	// Arrays
	{
		int rands[NUM_VALUES];
		for (int i = 0; i < NUM_VALUES; ++i) rands[i] = rand() % 100;
		std::cout << "Before Sort: \t";
		for (int i = 0; i < NUM_VALUES; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
		StaticSort<NUM_VALUES, int> staticSort;
		staticSort(rands);
		std::cout << "After Sort: \t";
		for (int i = 0; i < NUM_VALUES; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
	}
	
	std::cout << "\n";
	
	// STL Vector
	{
		std::vector<int> rands(NUM_VALUES);
		for (int i = 0; i < NUM_VALUES; ++i) rands[i] = rand() % 100;
		std::cout << "Before Sort: \t";
		for (int i = 0; i < NUM_VALUES; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
		StaticSort<NUM_VALUES, int> staticSort;
		staticSort(rands);
		std::cout << "After Sort: \t";
		for (int i = 0; i < NUM_VALUES; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
	}
	
	return 0;
}

#endif
