#include <cstdlib>
#include <iostream>
#include <string>
#include "CUI.cpp"
#include "utils.cpp"
#include "alg/mazealg.cpp"

using namespace std;
void mazeScr();
void heightsScr();

int main() {
	CUI::Choice ch[2];
	ch[0].name = "Maze";
	ch[0].func = &mazeScr;
	ch[1].name = "Heights map";
	ch[1].func = &heightsScr;
	while(true) {
		cout << "Choose" << endl;
		if(!CUI::choose(ch, 2, "Exit")) return 0;
	}
}

algo::Algo * c_algptr;
algo::AlgPrefs * c_prefsptr;

void configure() {
	string name;
	int value;
	cout << "Enter argument name: ";
	cin.ignore();
	getline(cin, name);
	if(!(*c_algptr).hasPref(name)) {
		cout << "No such argument" << endl;
		return;
	}
	cout << "New value = ";
	cin >> value;
	const algo::AlgPrefInfo * pi = c_algptr->getPrefInfo(name);
	if(!rangeAssert(value, pi->minVal, pi->maxVal, name)) {
		cin.clear();
		return;
	}
	c_prefsptr->set(name, value);
}

const CUI::Choice confChoice = CUI::Choice("Configure", &configure);

int* abstrScr(map<string, Algo> * algos, int w, int h) {
	int * m = allocMatrix(w, h);
	/*auto fillptr = CUI::chooseValue(*algos, "Nothing");
	if((void*)fillptr == NULL) return m;
	auto fill = *fillptr; 
	algo::AlgPrefs p;
	p.set("value", 2);
	fill.clampPrefs(p);
	fill.printPrefs(p);
	fill.func(m, w, h, p);*/
	Algo *algptr, alg;
	algo::AlgPrefs p;
	while(true) {
		algptr = CUI::chooseValue(*algos, "Finish");
		if((void*)algptr == NULL) break;
		alg = *algptr;
		alg.clampPrefs(p);
		c_algptr = &alg;
		c_prefsptr = &p;
		while(true) {
			alg.printPrefs(p);
			if(CUI::choose(&confChoice, 1, "Ok") == 0) break;
		}
		alg.func(m, w, h, p);
		cout << "Algorithm applied" << endl;
	}
	return m;
}

void mazeScr() {
	/*int * m = allocMatrix(16, 16);
	auto fillptr = CUI::chooseValue(mazealg::algos, "Nothing");
	if((void*)fillptr == NULL) return;
	auto fill = *fillptr; 
	//auto fill = (*mazealg::algos.find("fill")).second;
	algo::AlgPrefs p;
	p.set("value", 2);
	fill.printPrefs(p);
	fill.func(m, 16, 16, p);
	CUI::writeMatrixChars(m, 16, 16, "123", "--> ");*/
	int * m = abstrScr(&mazealg::algos, 16, 16);
	clampMatrix(m, 16, 16, 0, 1);
	CUI::writeMatrixChars(m, 16, 16, " #", "--> ");
	free(m);
}

void heightsScr() {
	
}
