#include "algtypes.h"
#include "../utils.cpp"
#include <map>
#include <string>

using namespace algo;
namespace mazealg {
	namespace funcs {
		void fill(int * m, int w, int h, AlgPrefs & p) {
			for(int i = 0; i < w * h; i++) {
				m[i] = p.get("value");
			}
		}
		void fillRandom(int * m, int w, int h, AlgPrefs & p) {
			unsigned int seed = p.get("seed"), hi = p.get("max") + 1;
			Random r = Random(seed);
			for(int i = 0; i < w * h; i++) {
				m[i] = r.next() % hi;
			}
		}
		
	}
	namespace infos {
		AlgPrefInfo fill[] = {AlgPrefInfo("value", 0, 1)};
		AlgPrefInfo fillRandom[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
									,AlgPrefInfo("max", 1, 1)};
	}
	map<string, Algo> algos =	{{"fill", Algo(&funcs::fill, infos::fill, 1)}
								,{"fill random", Algo(&funcs::fillRandom, infos::fillRandom, 2)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
