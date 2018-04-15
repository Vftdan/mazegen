#include "algtypes.h"
#include "../utils.cpp"
//#include "../CUI.cpp"
#include <map>
#include <string>
#include <stack>
#include <set>
#include <vector>
//#include <iostream>

using namespace algo;
namespace hmapalg {
	namespace funcs {
		void divAll(int * m, int w, int h, AlgPrefs & p) {
			int d = p.get("divider");
			for(int i = 0; i < w * h; i++) {
				m[i] /= d;	
			}
		}
		void fractalNoise(int * m, int w, int h, AlgPrefs & p) {
			int * white = (int*)malloc(w * h * sizeof(int));
			AlgPrefs wp;
			int mv = p.get("max");
			wp.set("seed", p.get("seed"));
			wp.set("max", mv);
			mazealg::funcs::fillRandom(white, w, h, wp);
			int n = p.get("depth"), i, j, k;
			for(i = 0; i < w; i++) {
				for(j = 0; j < h; j++) {
					double v = 0;
					double mul = 1.0 / (1 << k);
					double kexp2 = 1.0;
					for(k = 0; k < n; k++) {
						//v += mul * white[((i >> k) * h) + (j >> k)];
						v += mul * mxGetLerp(white, w, h, j / kexp2, i / kexp2);
						kexp2 *= 2.0;
						mul *= 2.0;
					}
					if(v > mv) v = mv;
					m[i * h + j] = (int)v;
				}
			}
			free(white);
		}
		void midpDis4(int * m, int w, int h, Position p1, Position p2, Position p3, Position p4, int add) {
			int v = (mxGetVal(m, w, h, p1)
			       + mxGetVal(m, w, h, p2)
			       + mxGetVal(m, w, h, p3)
			       + mxGetVal(m, w, h, p4)) >> 2;
			Position p = (p1 + p2 + p3 + p4) * .25;
			//if(wrapX) p.x += (w >> 1);
			//if(wrapY) p.y += (h >> 1);
			mxSetVal(m, w, h, p, v + add);
			//cout << "set (" << p.x << ", " << p.y << ") : " << v << " + " << add << endl;
		}
		void diamondSquare(int * m, int w, int h, AlgPrefs & p) {
			int step = max(w, h) >> 1;
			Random r = Random(p.get("seed"));
			//int hi = (p.get("noise amplitude") || 4) + 1;
			//int v = JSOR(p.get("avg"), 12);
			int hi = p.get("noise amplitude") + 1;
			int v = p.get("avg");
			const int sx = w >> 2, sy = h >> 2;
			Position p1, p2, p3, p4;
			//cout << "avg = " << v << endl;
			mxSetVal(m, w, h, Position(sx, sy), v);
			mxSetVal(m, w, h, Position(sx, sy + step), v);
			mxSetVal(m, w, h, Position(sx + step, sy), v);
			mxSetVal(m, w, h, Position(sx + step, sy + step), v);
			//CUI::writeMatrixChars(m, w, h, "0123456789ABCDEFGHIJKLM", "");
			while(step) {
				int x, y;
				//cout << "Square:" << endl;
				for(x = sx % step; x < w; x += step) {
					for(y = sy % step; y < h; y += step) {
						p1.x = x; p1.y = y;
						p2.x = x; p2.y = y + step;
						p3.x = x + step; p3.y = y;
						p4.x = x + step; p4.y = y + step;
						midpDis4(m, w, h, p1, p2, p3, p4, (r.next() % (hi * 2)) - hi);
					}
				}
				//cout << "x = " << x << endl << "y = " << y << endl;
				//cout << "Diamond:" << endl;
				for(x = (sx % step) + (step >> 1); x <= w; x += step) {
					for(y = (sy % step) + (step >> 1); y <= h; y += step) {
						p1.x = x; p1.y = y;
						p2.x = x - (step >> 1); p2.y = y + (step >> 1);
						p3.x = x; p3.y = y + step;
						p4.x = x + (step >> 1); p4.y = y + (step >> 1);
						midpDis4(m, w, h, p1, p2, p3, p4, (r.next() % (hi * 2)) - hi + 1);
						p2.x = x + (step >> 1); p2.y = y - (step >> 1);
						p3.x = x + step; p3.y = y;
						p4.x = x + (step >> 1); p4.y = y + (step >> 1);
						midpDis4(m, w, h, p1, p2, p3, p4, (r.next() % (hi * 2)) - hi + 1);
					}
				}
				step >>= 1;
				hi = ((hi - 1) >> 1) + 1;
			}
		}
	}
	namespace infos {
		AlgPrefInfo fill[] = {AlgPrefInfo("value", -2147483648, 2147483647)};
		AlgPrefInfo fillRandom[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
						,AlgPrefInfo("max", 1, 2147483647)};
		AlgPrefInfo divAll[] = {AlgPrefInfo("divider", 1, 8388608)};
		AlgPrefInfo fractalNoise[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
						,AlgPrefInfo("max", 1, 2147483647)
						,AlgPrefInfo("depth", 1, 16)};
		AlgPrefInfo diamondSquare[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
						,AlgPrefInfo("noise amplitude", 1, 2147483647)
						,AlgPrefInfo("avg", 1 -2147483648, 2147483647)};
	}
	map<string, Algo> algos =	{{"fill", Algo(&mazealg::funcs::fill, infos::fill, 1)}
					,{"fill random", Algo(&mazealg::funcs::fillRandom, infos::fillRandom, 2)}
					,{"fractal noise", Algo(&funcs::fractalNoise, infos::fractalNoise, 3)}
					,{"diamond square", Algo(&funcs::diamondSquare, infos::diamondSquare, 3)}
					,{"divide values", Algo(funcs::divAll, infos::divAll, 1)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
