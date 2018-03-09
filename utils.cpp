#include <iostream>
#ifndef utilsincluded
#define utilsincluded
#define allocMatrix(w, h) (int*)malloc(w * h * sizeof(int))

using namespace std;
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

void nopFunc() {}

#endif
