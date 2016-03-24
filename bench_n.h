#ifndef bench2_h
#define bench2_h

#include <string>
#include <iostream>
#include <algorithm>

#include "timer.h"

#include "static_sort.h"

template <unsigned NumElements, class T, class Compare = void> class StaticRankOrderSort
{
private:
	template <class A, unsigned MaxIndex, unsigned Index, unsigned MaxI = MaxIndex-1, unsigned I = 0>
	struct RankOrder
	{
		const unsigned value;
		inline RankOrder(A &d):
		value((I < MaxIndex ? (d[Index] > d[I + (I >= Index)]) : (d[Index] >= d[I + (I >= Index)])) +
			  RankOrder<A, MaxIndex, Index, MaxI, I + 1>(d).value) {}
	};
	
	template <class A, unsigned MaxIndex, unsigned Index, unsigned I>
	struct RankOrder <A, MaxIndex, Index, I, I>
	{
		const unsigned value;
		inline RankOrder(A &d):
		value((I < MaxIndex ? (d[Index] > d[I + (I >= Index)]) : (d[Index] >= d[I + (I >= Index)]))) {}
	};
	
	template <class A0, class A1, unsigned MaxIndex, unsigned Index=0> struct RankOrderSort
	{
		inline RankOrderSort(A0 &d, const A1 e, unsigned sum = 0, unsigned sum2 = 0)
		{
			unsigned i = RankOrder<A0, MaxIndex, Index>(d).value;
			RankOrderSort<A0, A1, MaxIndex, Index + 1>(d, e, sum + Index + 1, i + sum2);
			d[i] = e[Index];
		}
	};
	
	template <class A0, class A1, unsigned Index> struct RankOrderSort <A0, A1, Index, Index>
	{
		inline RankOrderSort(A0 &d, const A1 e, unsigned sum, unsigned sum2)
		{
			d[sum - sum2] = e[Index];
		}
	};
	
public:
	template <class Container> inline void operator() (Container &arr) const 
	{
		T b[NumElements];
		for (unsigned i = 0; i < NumElements; ++i) b[i] = arr[i];
		RankOrderSort<Container, T*, NumElements - 1>(arr, b);
	};
	
	inline void operator() (T *arr) const
	{
		T b[NumElements];
		for (unsigned i = 0; i < NumElements; ++i) b[i] = arr[i];
		RankOrderSort<T*, T*, NumElements - 1>(arr, b);
	};
};

template <unsigned NumElements, class T, class Compare = void> class StaticInsertionSort
{
public:
	inline void operator() (T *arr) const
	{
		for (unsigned i = 1; i < NumElements; ++i) {
			T value = arr[i];
			unsigned hole = i;
			for (; hole && value < arr[hole-1]; --hole)
				arr[hole] = arr[hole-1];
			arr[hole] = value;
		}
	};
	
	template <class Container> inline void operator() (Container &arr) const
	{
		operator()(&arr[0]);
	};
};

template <unsigned NumElements, class T, class Compare = void> class STLSort
{
public:
	inline void operator() (T *arr) const
	{
		std::sort(arr, arr + NumElements);
	};
	
	template <class Container> inline void operator() (Container &arr) const
	{
		std::sort(&arr[0], (&arr[0]) + NumElements);
	};
};

template <unsigned NumTests, unsigned NumElements> struct Test
{
	template <class T> static inline void fill(int n, T *a)
	{
		static int seed = 76521;
		while (n--) *a++ = (seed = seed * 1812433253 + 12345);
	}
	
	template <class T, class Compare, template <unsigned, class, class> class Sort>
	inline void test(const Sort<NumElements, T, Compare> &sort,
					   const std::string &description)
	{
		enum { TotalElements = NumElements * NumTests };
		
		T *data = new T[TotalElements];
		
		fill(TotalElements, data);
		
		Timer timer;
		timer.start();
		
		for (unsigned i = 0; i < TotalElements; i += NumElements) {
			sort(data + i);
		}
		
		timer.stop();
		
		std::cout
		<< description << ": "
		<< timer.getElapsedMilliseconds()
		<< std::endl;
		
		for (unsigned i = 0; i < NumTests; ++i) {
			bool sortFailed = false;
			for (unsigned j = 0; j < NumElements - 1 && !sortFailed; ++j) {
				unsigned ij = (i * NumElements) + j;
				if (data[ij] > data[ij + 1]) {
					sortFailed = true;
				}
			}
			if (sortFailed) {
				std::cout << i << ":";
				for (unsigned j = 0; j < NumElements; ++j) {
					unsigned ij = (i * NumElements) + j;
					std::cout << " " << data[ij];
				}
				std::cout << std::endl;
			}
		}
		delete [] data;
	}
	
	Test()
	{
		typedef int Number;
		std::cout << NumElements << " Elements: \n";
		test(StaticSort<NumElements, Number>(),
			 "\tTemplated Bose-Nelson Sorting Network ");
		test(StaticRankOrderSort<NumElements, Number>(),
			 "\tTemplated Rank Order                  ");
		test(StaticInsertionSort<NumElements, Number>(),
			 "\tTemplated Insertion Sort              ");
		test(STLSort<NumElements, Number>(),
			 "\tSTL Sort                              ");
		Test<NumTests, NumElements + 1> ();
	}
};

template <unsigned NumTests> struct Test <NumTests, 33> {};

int main(int argc, const char * argv[])
{
	enum { NumTests = 1000000 };
	
	std::cout << "Milliseconds taken to sort " << NumTests << " arrays." << std::endl;
	
	Test<NumTests, 2> t;
	
	return 0;
}

#endif /* bench2_h */
