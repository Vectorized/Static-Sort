/*
 Copyright (c) 2020 Kang Yue Sheng Benjamin.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef bench_pair_sort_h
#define bench_pair_sort_h

#include "static_sort.h"
#include "timer.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <ctype.h>
#include <cstring>

/**
 * A helper class for packing two 4 byte numbers together into a uint64_t.
 */
class PairPacker
{
	typedef uint64_t Packed;
	static inline uint64_t _(uint32_t x)
	{
		return x;
	}
	
	static inline uint64_t _(int32_t x)
	{
		return x + 0x80000000;
	}
	
	static inline uint64_t _(float x)
	{
		uint32_t i;
		std::memcpy(&i, &x, sizeof(float));
		return i;
	}
	
	static inline void _(uint32_t x, uint32_t &a)
	{
		a = x;
	}
	
	static inline void _(uint32_t x, int32_t &a)
	{
		a = x - 0x80000000;
	}
	
	static inline void _(uint32_t x, float &a)
	{
		std::memcpy(&a, &x, sizeof(float));
	}
	
public:
	
#define _DEF_PAIR_PACK(A, B) \
\
static inline void pack(uint64_t &p, A a, B b) \
{ p = _(a) << 32 | _(b); } \
\
static inline void unpack(uint64_t p, A &a, B &b) \
{ _((uint32_t) (p >> 32), a); _((uint32_t) p, b); }
	
	_DEF_PAIR_PACK(int32_t, int32_t)
	_DEF_PAIR_PACK(int32_t, uint32_t)
	_DEF_PAIR_PACK(int32_t, float)
	
	_DEF_PAIR_PACK(uint32_t, int32_t)
	_DEF_PAIR_PACK(uint32_t, uint32_t)
	_DEF_PAIR_PACK(uint32_t, float)
	
#undef _DEF_PAIR_PACK
};


int main(int argc, const char * argv[])
{
	Timer timer;
	
	typedef std::pair<int, int> P;
	typedef std::vector<P> PV;
	
	enum { S = 32, N = 3000 };
	
	StaticSort<S> staticSort;
	
	std::vector<PV> pvv(N);
	
	
	for (size_t i = 0; i < N; ++i) {
		pvv[i].resize(S);
		for (size_t j = 0; j < S; ++j) {
			pvv[i][j] = P(rand(), rand());
		}
	}
	
	timer.start();
	
	for (size_t i = 0; i < N; ++i) {
		uint64_t t[S];
		for (size_t j = 0; j < S; ++j) {
			PairPacker::pack(t[j], pvv[i][j].first, pvv[i][j].second);
		}
		staticSort(t);
		for (size_t j = 0; j < S; ++j) {
			PairPacker::unpack(t[j], pvv[i][j].first, pvv[i][j].second);
		}
	}
	
	timer.stop();
	std::cout << "static sort (packed): " << timer.getElapsedMilliseconds() << "s\n";
	
	for (size_t i = 0; i < N; ++i) {
		pvv[i].resize(S);
		for (size_t j = 0; j < S; ++j) {
			pvv[i][j] = P(rand(), rand());
		}
	}
	
	timer.start();
	
	for (size_t i = 0; i < N; ++i) {
		uint64_t t[S];
		for (size_t j = 0; j < S; ++j) {
			PairPacker::pack(t[j], pvv[i][j].first, pvv[i][j].second);
		}
		std::sort(t, t + S);
		for (size_t j = 0; j < S; ++j) {
			PairPacker::unpack(t[j], pvv[i][j].first, pvv[i][j].second);
		}
	}
	
	
	timer.stop();
	std::cout << "std sort (packed): " << timer.getElapsedMilliseconds() << "s\n";
	
	
	
	for (size_t i = 0; i < N; ++i) {
		pvv[i].resize(S);
		for (size_t j = 0; j < S; ++j) {
			pvv[i][j] = P(rand(), rand());
		}
	}
	
	timer.start();
	
	for (size_t i = 0; i < N; ++i) {
		std::sort(pvv[i].begin(), pvv[i].end());
	}
	
	timer.stop();
	std::cout << "std sort: " << timer.getElapsedMilliseconds() << "s\n";
	
	
	for (size_t i = 0; i < N; ++i) {
		pvv[i].resize(S);
		for (size_t j = 0; j < S; ++j) {
			pvv[i][j] = P(rand(), rand());
		}
	}
	
	timer.start();
	
	for (size_t i = 0; i < N; ++i) {
		staticSort(pvv[i]);
	}
	
	timer.stop();
	std::cout << "static sort: " << timer.getElapsedMilliseconds() << "s\n";
	return 0;
	
}

#endif /* bench_pair_sort_h */
