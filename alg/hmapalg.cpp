#include "algtypes.h"
#include "../utils.cpp"
#include <map>
#include <string>
#include <stack>
#include <set>
#include <vector>

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
					for(k = 0; k < n; k++) {
						v += mul * white[((i >> k) * h) + (j >> k)];
						mul *= 2.0;
					}
					if(v > mv) v = mv;
					m[i * h + j] = (int)v;
				}
			}
			free(white);
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
	}
	map<string, Algo> algos =	{{"fill", Algo(&mazealg::funcs::fill, infos::fill, 1)}
					,{"fill random", Algo(&mazealg::funcs::fillRandom, infos::fillRandom, 2)}
					,{"fractal noise", Algo(&funcs::fractalNoise, infos::fractalNoise, 3)}
					,{"divide values", Algo(funcs::divAll, infos::divAll, 1)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
