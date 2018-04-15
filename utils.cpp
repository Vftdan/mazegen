#include <cstdlib>
#include <iostream>
#include <string>
#ifndef utilsincluded
#define utilsincluded
//#define JSOR(a, b) (a?a:b)

using namespace std;
int * allocMatrix(int w, int h) {
	int * m = (int*)malloc(w * h * sizeof(int));
	for(int i = 0; i < w * h; i++) m[i] = 0;
	//cout << w << h << m[w * h - 1];
	return m;
}

template <typename T>
bool rangeAssert(const T & val, const T & lo, const T & hi, string name) {
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

template <typename Tval, typename Tcoef>
Tval lerp(Tval lo, Tval hi, Tcoef k) {
	return lo + k * (hi - lo);
}

template <typename Tval, typename Tcoef>
Tval bilerp(Tval ll, Tval lh, Tval hl, Tval hh, Tcoef kx, Tcoef ky) {
	return lerp(lerp(ll, lh, kx), lerp(hl, hh, kx), ky);
}

void clampMatrix(int * m, int w, int h, int lo, int hi) {
	for(int i = 0; i < w * h; i++) m[i] = clamp(m[i], lo, hi);
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

struct Position {
	int x, y;
	Position(int x, int y) : x(x), y(y) {};
	Position() : x(0), y(0) {};
};
bool operator==(const Position & a, const Position & b) {
	return a.x == b.x && a.y == b.y;
}
bool operator<(const Position & a, const Position & b) {
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}
Position operator*(const Position & p, const double & k) {
	Position r;
	r.x = (int)(k * p.x);
	r.y = (int)(k * p.y);
	return r;
}
Position operator+(const Position & a, const Position & b) {
	Position r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}
Position operator-(const Position & a, const Position & b) {
	Position r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

int mxGetVal(int * m, int w, int h, const Position & p) {
	int x = ((p.x % w) + w) % w;	
	int y = ((p.y % h) + h) % h;	
	return m[y * w + x];
}

void mxSetVal(int * m, int w, int h, const Position & p, int val) {
	int x = ((p.x % w) + w) % w;	
	int y = ((p.y % h) + h) % h;	
	m[y * w + x] = val;
}

double mxGetLerp(int * m, int w, int h, double x, double y) {
	int ix = (int) x, iy = (int) y;
	if(x < 0) ix--;
	if(y < 0) iy--;
	double	 ll = mxGetVal(m, w, h, Position(ix, iy))
		,lh = mxGetVal(m, w, h, Position(ix + 1, iy))
		,hl = mxGetVal(m, w, h, Position(ix, iy + 1))
		,hh = mxGetVal(m, w, h, Position(ix + 1, iy + 1));
	return bilerp(ll, lh, hl, hh, x - ix, y - iy);
}


void nopFunc() {}

#endif
