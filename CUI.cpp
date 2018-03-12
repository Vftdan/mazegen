#include <map>
//#include <pair>
#include <iostream>
#include <string>
#include <vector>
#include "utils.cpp"

using namespace std;
namespace CUI {
	typedef void (*ChoiceFunc)();
	struct Choice {
		char * name;
		ChoiceFunc func;
		Choice() {}
		Choice(char * name, ChoiceFunc func) : name(name), func(func) {}
	};
	int choose(const Choice * ch, int len, char * nth) {
		//map<int, ChoiceFunc> m;
		if(len < 1) return 0;
		int i;
		while(true) {
			for(i = 1; i <= len; i++) {
				//m.insert(pair<int, ChoiceFunc>(i, ch[i - 1].func));
				cout << i << '\t' << ch[i - 1].name << endl;
			}
			cout << 0 << "\t" << nth << endl;
			cin >> i;
			if(!rangeAssert(i, 0, len, "Choice")) {
				cin.clear();
				continue;
			}
			if(i == 0) return 0;
			ch[i - 1].func();
			return i;
		}
	}
	template <typename T>
	T* chooseValue(map<string, T> & m, char * nth) {
		int i, len;
		vector<string> v;
		for(auto it = m.begin(); it != m.end(); it++) {
			v.push_back((*it).first);
		}
		len = v.size();
		while(true) {
			for(i = 1; i <= len; i++) {
				cout << i << '\t' << v[i - 1] << endl;
			}
			cout << 0 << "\t" << nth << endl;
			cin >> i;
			if(!rangeAssert(i, 0, len, "Choice")) {
				cin.clear();
				continue;
			}
			if(i == 0) return (T*)NULL;
			return &(*m.find(v[i - 1])).second;;
		}
	}
	void writeMatrixChars(int * m, int w, int h, char * lut, char * lnprefix) {
		int i, j;
		for(i = 0; i < h; i++) {
			cout << lnprefix;
			for(j = 0; j < w; j++) {
				cout << lut[m[i * w + j]];
			}
			cout << endl;
		}
	}
}
