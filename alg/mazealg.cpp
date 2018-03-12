#include "algtypes.h"
#include "../utils.cpp"
#include <map>
#include <string>
#include <stack>
#include <set>
#include <vector>

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
		void dfsMaze(int * m, int w, int h, AlgPrefs & p) {
			int x = p.get("start x"), y = p.get("start y"), val = p.get("value"), i, j;
			if(x >= w || y >= h) {
				cout << "Start position is not in the maze" << endl;	
			}
			Position t;
			Random r = Random(p.get("seed"));
			std::stack<Position> s;
			std::vector<Position> nb;
			std::set<Position> v;
			v.insert(Position(x, y));
			bool f = true;
			while(f) {
				m[y * w + x] = val;
				/* for(i = -2; i < 3; i += 4) for(j = -2; j < 3; j += 4) {
					t.x = x + j;
					t.y = y + i;
					if(t.x >= 0 && t.x < w && t.y >= 0 && t.y < h && !v.count(t)) nb.push_back(t);
				} */
				for(i = -2; i < 3; i += 4) {
					t.x = x;
					t.y = y + i;
					if(t.x >= 0 && t.x < w && t.y >= 0 && t.y < h && !v.count(t)) nb.push_back(t);
					t.x = x + i;
					t.y = y;
					if(t.x >= 0 && t.x < w && t.y >= 0 && t.y < h && !v.count(t)) nb.push_back(t);
				}
				if(nb.size()) {
					t = nb[r.next() % nb.size()];
					s.push(Position(x, y));
					i = (y + t.y) >> 1;
					j = (x + t.x) >> 1;
					m[i * w + j] = val;
					x = t.x;
					y = t.y;
					v.insert(Position(x, y));
				} else {
					if(s.empty()) {
						f = false;
					} else {
						t = s.top();
						s.pop();
						x = t.x;
						y = t.y;
					}
				}
				nb.clear();
			}
		}
		
	}
	namespace infos {
		AlgPrefInfo fill[] = {AlgPrefInfo("value", 0, 1)};
		AlgPrefInfo fillRandom[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
						,AlgPrefInfo("max", 1, 1)};
		AlgPrefInfo dfsMaze[] =	{AlgPrefInfo("seed", -2147483648, 2147483647)
					,AlgPrefInfo("value", 0, 1)
					,AlgPrefInfo("start x", 0, 255)
					,AlgPrefInfo("start y", 0, 255)};
	}
	map<string, Algo> algos =	{{"fill", Algo(&funcs::fill, infos::fill, 1)}
					,{"fill random", Algo(&funcs::fillRandom, infos::fillRandom, 2)}
					,{"DFS", Algo(&funcs::dfsMaze, infos::dfsMaze, 4)}};
	//const Algo fill = Algo(&funcs::fill, infos::fill, 1);
}
