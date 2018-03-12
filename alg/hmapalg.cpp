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
	}
	namespace infos {
		AlgPrefInfo fill[] = {AlgPrefInfo("value", -2147483648, 2147483647)};
		AlgPrefInfo fillRandom[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
						,AlgPrefInfo("max", 1, 2147483647)};
		AlgPrefInfo divAll[] = {AlgPrefInfo("divider", 1, 8388608)};
	}
	map<string, Algo> algos =	{{"fill", Algo(&mazealg::funcs::fill, infos::fill, 1)}
					,{"fill random", Algo(&mazealg::funcs::fillRandom, infos::fillRandom, 2)}
					,{"divide values", Algo(funcs::divAll, infos::divAll, 1)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
