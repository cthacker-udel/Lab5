#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {

	this->map = NULL;
	this->first = "";
	this->numKeys = 0;
	this->mapSize = 10;
	this->hashfn = hash1;
	this->collfn = coll1;
	this->collisions = 0;
	this->hashcoll = 0;

}
void hashMap::addKeyValue(string k, string v) { // TODO : ADDKEYVALUE

	// collisions will happen here not in getIndex

}
int hashMap::getIndex(string k) { // TODO : GETINDEX
	reHash();
	// uses calchash and returns the index of the keyword k, use calchash, and then see if the key where the
	//index thats returned is is the same as the key given, if not, then we have a collision, use coll1,
	//find the key there, see if its the same

	// it might happen(the if statements) because if the process of how we got to place the key
	// is through collision functions then we have to repeat the process to find it
	int index1 = calcHash1(k);
	if(*(*(this->map+index1)) != NULL){
		// collision <--- call coll1, see if that returns a value that works, if it doesnt, then call coll2
		/*
		int index2 = calcHash2(k);
		if(*(*(this->map+index2)) != NULL){ <-- replace this with return of coll1 != NULL
			// collision2
		}
		else{
			// place node at index
		}
		*/
	}
	else{
		// place node at index
	}
}

int hashMap::calcHash2(string k){ // complete

	int p = 83;
	int total = 0;
	while(k.length() != 0){
		total += ((int)sqrt((((int)k.at(k.length()-1))*p)));
		k = k.substr(0,k.length()-1);
	}
	return total % this->mapSize;

}

int hashMap::calcHash1(string k){ // complete

	// Horner's rule

	int p = 31;
	int total = 0;
	for(int i = 0; i < k.length(); i++){
		total = p*total + k.at(i);
	}
	return total % this->mapSize;\

}



bool isPrime(int number){ // helper function

	if(number % 2 == 0 || number % 3 == 0 || number % 5 == 0){
		return false;
	}
	else{
		for(int i = 2; i < ((int)sqrt(number))+1; i++){
			if(number % i == 0){
				return false;
			}
		}
		return true;
	}

}

void hashMap::getClosestPrime() { // complete

	// start at 10
	bool foundPrime = false;
	for(int i = this->mapSize*2, j = this->mapSize*2; ; i++,j--){
		if(isPrime(i)){
			this->mapSize = i;
			return;
		}
		if(isPrime(j)){
			this->mapSize = j;
			return;
		}
	}

}
void hashMap::reHash() { // complete

	if(this->numKeys / this->mapSize >= .70){
		// double array size and rehash
		this->mapSize = this->mapSize*2;
		// TODO : rehash all keys
	}

}
int hashMap::coll1(int h, int i, string k) {

	return h + i *calcHash2(k);
	// double hashing

}
int hashMap::coll2(int h, int i, string k) { // TODO : COLL2
	// linear probing
	// h and i aren't used in this collision.
	return k % this->mapSize;

}
int hashMap::findKey(string k) { // TODO : FINDKEY
	// given a key and find it in the map
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 


}




void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


