#include <iostream>
#include "MakeSeuss.hpp"
#include <time.h>
#include <stdlib.h>

using namespace std;
int main() {
	cout << "making voices" << endl;
	srand(time(NULL));
	makeSeuss voice1("DrSeuss.txt","Seussout1.txt",true,true);
	cout << "printed out voice1" << endl;
	makeSeuss voice2("DrSeuss.txt","Seussout2.txt",false,true);
	cout << "printed out voice2" << endl;
	makeSeuss voice3("DrSeuss.txt","Seussout3.txt",true,false);
	cout << "printed out voice3" << endl;
	makeSeuss voice4("DrSeuss.txt","Seussout4.txt",false,false);
	cout << "printed out voice4" << endl;
//OR
	makeSeuss voice5("GEChap1a.txt","GEout1.txt",true,true);
	makeSeuss voice6("GEChap1a.txt","GEout2.txt",false,true);
	makeSeuss voice7("GEChap1a.txt","GEout3.txt",true,false);
	makeSeuss voice8("GEChap1a.txt","GEout4.txt",false,false);
	cout << "return" << endl;
	return 0;
}
