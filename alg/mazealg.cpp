#include "algtypes.h"
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
	}
	namespace infos {
		AlgPrefInfo fill[] = {AlgPrefInfo("value", 0, 1)};
	}
	map<string, Algo> algos = {{"fill", Algo(&funcs::fill, infos::fill, 1)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
