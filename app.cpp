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

int* abstrScr(map<string, Algo> * algos, int w, int h) {
	int * m = allocMatrix(w, h);
	auto fillptr = CUI::chooseValue(*algos, "Nothing");
	if((void*)fillptr == NULL) return NULL;
	algo::AlgPrefs p;
	p.set("value", 2);
	fill.printPrefs(p);
	fill.func(m, w, h, p);
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
	CUI::writeMatrixChars(m, 16, 16, "123", "--> ");
}

void heightsScr() {
	
}
