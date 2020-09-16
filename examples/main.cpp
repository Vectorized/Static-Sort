/*
 Copyright (c) 2020 Kang Yue Sheng Benjamin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#define BENCH_PAIR_SORT

#if defined(BENCH_6)
#include "bench_6.h"
#elif defined(BENCH_10)
#include "bench_10.h"
#elif defined(BENCH_N)
#include "bench_n.h"
#elif defined(BENCH_PAIR_SORT)
#include "bench_pair_sort.h"
#else

#include "static_sort.h"

#include <iostream>
#include <vector>

int main(int argc, const char * argv[])
{
	enum { NumValues = 32 };
	
	// Arrays
	{
		int rands[NumValues];
		for (int i = 0; i < NumValues; ++i) rands[i] = rand() % 100;
		std::cout << "Before Sort: \t";
		for (int i = 0; i < NumValues; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
		StaticSort<NumValues> staticSort;
		staticSort(rands);
		std::cout << "After Sort: \t";
		for (int i = 0; i < NumValues; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
	}
	
	std::cout << "\n";
	
	// STL Vector
	{
		std::vector<int> rands(NumValues);
		for (int i = 0; i < NumValues; ++i) rands[i] = rand() % 100;
		std::cout << "Before Sort: \t";
		for (int i = 0; i < NumValues; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
		StaticSort<NumValues> staticSort;
		staticSort(rands);
		std::cout << "After Sort: \t";
		for (int i = 0; i < NumValues; ++i) std::cout << rands[i] << " ";
		std::cout << "\n";
	}
	
	return 0;
}

#endif