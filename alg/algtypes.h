#include <map>
#include <set>
#include <string>
#include <iostream>
#include "../utils.cpp"

#ifndef algtypesincluded
#define algtypesincluded
namespace algo {
	struct AlgPrefInfo {
		string name;
		int minVal, maxVal;
		AlgPrefInfo(string name, int minVal, int maxVal) : name(name), minVal(minVal), maxVal(maxVal) {}
		};
		bool operator<(const AlgPrefInfo& a, const AlgPrefInfo& b) {
			return a.name < b.name;
		} 
	struct AlgPrefs {
		map<string, int> data;
		int get(string k) {
			auto it = data.find(k);
			if(it == data.end()) return 0;
			return it->second;
		}
		void set(string k, int v) {
			auto it = data.find(k);
			if(it != data.end()) {
				data.erase(it);
			}
			data.insert(pair<string, int>(k, v));
		}
		void clampTo(string k, int lo, int hi) {
			auto it = data.find(k);
			int v = 0;
			if(it != data.end()) {
				v = (*it).second;
				data.erase(it);
			}
			data.insert(pair<string, int>(k, clamp(v, lo, hi)));
		}
	};
	typedef void (*AlgFunc)(int*, int, int, AlgPrefs&);
	struct Algo {
		AlgFunc func;
		set<AlgPrefInfo> info;
		Algo(AlgFunc f, AlgPrefInfo * infarr, int inflen) {
			func = f;
			for(int i = 0; i < inflen; i++) {
				info.insert(infarr[i]);
			}
		}
		void printPrefs(AlgPrefs & p) {
			for(auto it = info.begin(); it != info.end(); it++) {
				string name = (*it).name;
				cout << name << "\t=\t" << p.get(name) << endl;
			}
		}
		void clampPrefs(AlgPrefs & p) {
			for(auto it = info.begin(); it != info.end(); it++) {
				p.clampTo((*it).name, (*it).minVal, (*it).maxVal);
			}
		}
	};
}
#endif
