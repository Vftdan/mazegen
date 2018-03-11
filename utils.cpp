#include <iostream>
#ifndef utilsincluded
#define utilsincluded

using namespace std;
int * allocMatrix(int w, int h) {
	int * m = (int*)malloc(w * h * sizeof(int));
	for(int i = 0; i < w * h; i++) m[i] = 0;
	//cout << w << h << m[w * h - 1];
	return m;
}
template <typename T>
bool rangeAssert(T val, T lo, T hi, char * name) {
	if(val < lo) {
		cout << name << " is lower than " << lo << endl;
		return false;
	}
	if(val > hi) {
		cout << name << " is greater than " << hi << endl;
		return false;
	}
	return true;
}

template <typename T>
T clamp(T val, T lo, T hi) {
	if(val > hi) return hi;
	if(val < lo) return lo;
	return val;
}

struct Random {
	unsigned int r1, r2;
	Random(unsigned int seed) {
		r1 = seed * 3 + 2;
		r2 = seed >> 5;
		//cout << "r1, r2 = " << r1 << ", " << r2 << endl;
	}
	void skip() {
		r2 ^= r1;
		r1 ^= r1 << 13;
		r1 ^= r1 >> 17;
		r1 ^= r1 << 5;
		r1 += r2;
	}
	unsigned int next() {
		skip();
		return r1 ^ r2;
	}
};

void nopFunc() {}

#endif
