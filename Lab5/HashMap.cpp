#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {

	this->first = "";
	this->numKeys = 0;
	this->mapSize = 10;
	this->map = new hashNode*[this->mapSize];
	for(int i = 0; i < this->mapSize; i++){
		*(this->map+i) = NULL;
	}
	this->hashfn = hash1;
	this->collfn = coll1;
	this->collisions = 0;
	this->hashcoll = 0;

}
void hashMap::addKeyValue(string k, string v) { // TODO : ADDKEYVALUE

	// collisions will happen here not in getIndex
	cout << "Entering addkeyvalue with key" << k << " and value " << v << endl;
	reHash();
	int index;
	this->numKeys++;
	if(this->hashfn){
		// use hashfunction1
		index = calcHash1(k);
	}
	else{
		// use hashfunction2
		index = calcHash2(k);
	}
	cout << "index generated was : " << index << endl;
	hashNode *theNode = *(this->map+index);
	if(theNode == NULL){
		// place node here
		*(this->map+index) = new hashNode(k,v);
	}
	else{
		// collision
		if(index == 342 && v == "North!"){
			cout << "breakhere" << endl;
		}
		cout << "Collision occured" << endl;
		theNode = *(this->map+index);
		while(theNode != NULL){
			this->collisions++;
			theNode = *(this->map+index);
			if(theNode == NULL){
				*(this->map+index) = new hashNode(k,v);
			}
			else if(theNode->keyword == k){
				// found node
				theNode = *(this->map+index);
				theNode->addValue(v);
				break;
			}
			else if(theNode->keyword == ""){
				*(this->map+index) = new hashNode(k,v);
				break;
			}
			else{
				// did not find node
				if(this->collfn){
					// coll1
					index = coll1(index,this->collisions,k);
				}
				else{
					// coll2
					index = coll2(index,this->collisions,k);
				}
			}
		}
		this->collisions = 0;
	}



}
int hashMap::getIndex(string k) { // TODO : GETINDEX
	reHash();
	// uses calchash and returns the index of the keyword k, use calchash, and then see if the key where the
	//index thats returned is is the same as the key given, if not, then we have a collision, use coll1,
	//find the key there, see if its the same

	// it might happen(the if statements) because if the process of how we got to place the key
	// is through collision functions then we have to repeat the process to find it
	int index1;
	if(this->hashfn){
		index1 = calcHash1(k);
	}
	else{
		index1 = calcHash2(k);
	}
	if(*(this->map+index1) != NULL){
		this->collisions++;
		hashNode *theNode = *(this->map+index1);
		if(theNode->keyword == k){
			return index1;
		}
		else if(this->collfn){
			index1 = coll1(index1,index1,k);
			return index1;
		}
		else{
			index1 = coll2(index1,index1,k);
			return index1;
		}
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
		return index1;
	}
	return -1;
}

int hashMap::calcHash2(string k){ // complete

	int p = 80;
	int total = 0;
	while(k.length() != 0){
		total += ((int)sqrt((((int)k.at(k.length()-1))*p)));
		k = k.substr(0,k.length()-1);
	}
	while(total > this->mapSize){
		total -= this->mapSize;
	}
	return total % this->mapSize;

}

int hashMap::calcHash1(string k){ // complete

	// Horner's rule, describe why it would work well, sentence or two

	int p = 7;
	int total = 0;
	for(int i = 0; i < ((int)k.length()); i++){
		total = p+total + k.at(i);
	}
	return total % this->mapSize;

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
	for(int i = this->mapSize*2; ; i++){
		if(isPrime(i)){
			this->mapSize = i;
			return;
		}
	}

}

/*
 *
 * May have to remove recursion from calchash, and add that recursive aspect to the functions that call them
 *
 *
 */

void hashMap::reHash() { // complete

	vector<hashNode *> nodes;

	/*
	 *
	 * Steps:
	 *
	 * 1) Remove all nodes <--- to avoid placing a node in a spot which would be empty but is not because we did not remove all nodes first, so we are removing all nodes first
	 * 2) Rehash all the nodes, basically place them back in new spots
	 *
	 */
	if((this->numKeys*1.0 / this->mapSize) == 0.663269){
		cout << "end" << endl;
	}
	cout << "ratio = " << (this->numKeys*1.0 / this->mapSize) << endl;
	if(this->numKeys*1.0 / this->mapSize >= .70){

		cout << "size of map is " << this->numKeys << endl;
		// double array size and rehash
		cout << "entered rehash function" << endl;

		int tmpMapSize = this->mapSize;

		getClosestPrime(); // <---- double map size
		// TODO : rehash all keys, use addkeyvalue

		cout << "before for loop" << endl;

		for(int i = 0; i < tmpMapSize; i++){
			hashNode *theNode = *(this->map+i);
			if(theNode != NULL){
				if(theNode->keyword != ""){
					// value there
					nodes.push_back(theNode);
				}
			}
		}

		// double map size

		this->map = new hashNode*[this->mapSize];
		for(int i = 0; i < this->mapSize; i++){
			*(this->map+i) = NULL;
		}

		cout << "after for loop" << endl;

		// adding in all the nodes

		for(int i = 0; i < ((int)nodes.size()); i++){

			hashNode *theNode = nodes.at(i); // get curr node in node list
			int index1;
			if(this->hashfn){
				// hash1
				index1 = calcHash1(theNode->keyword);
			}
			else{
				index1 = calcHash2(theNode->keyword);
			}

			if(*(this->map+index1) != NULL){ // collision
				this->collisions++;
				if(this->collfn){ // use coll1
					int tmpResult = index1;
					tmpResult = coll1(index1,tmpResult,theNode->keyword);
					// 0,1 -> 0,2 -> 0,3 -> 0,4 -> 0,0
					// control, orig index, cycle up, and result
					// 3 variables, orig index, cycling index, and result
					int tmpIndex = index1;
					while(*(this->map+tmpResult) != NULL){
						tmpResult = ++tmpIndex;
						if(tmpIndex == this->mapSize){
							tmpIndex = 0;
							tmpResult = tmpIndex;
						}
						this->collisions++;
						tmpResult = coll1(index1,tmpResult,theNode->keyword);
					}
					*(this->map+tmpResult) = theNode;
				}
				else{
					// use coll2
					int tmpResult = coll2(index1,index1,theNode->keyword);
					int tmpIndex = index1;
					while(*(this->map+tmpResult) != NULL){
						if(tmpIndex == this->mapSize){
							tmpIndex = 0;
							tmpResult = tmpIndex;
						}
						// coll
						this->collisions++;
						tmpResult = coll2(index1,++tmpIndex,theNode->keyword);
					}
					*(this->map+tmpResult) = theNode;
				}
			}
			else{
				*(this->map+index1) = theNode;
			}

		}
		cout << "\n\n---- AFTER REHASHING ----\n\n" << endl;
		//printMap();

	}

}
int hashMap::coll1(int h, int i, string k) {
	// TODO : TEST DOUBLE HASHING
	// might require same methodology of coll2, in the sense that we keep calling it until it finds a valid index

	//int j = h + i *calcHash2(k);
	/*
	i = j;
	if(i == this->mapSize-1){

		if(*(this->map+this->mapSize-1) != NULL){
			this->collisions++;
			return coll1(h,0,k);
		}
		else{
			return i;
		}
	}
	else{
		if((this->map+i) != NULL){
			this->collisions++;
			return coll1(h,i+1,k);
		}
		else{
			return i;
		}
	}
	*/
	hashNode *theNode = *(this->map+i);
	if(theNode != NULL && theNode->keyword == k){
		return i;
	}

	return (h + i *calcHash2(k)) % this->mapSize;
	// double hashing

}
int hashMap::coll2(int h, int i, string k) { // TODO : COLL2 , should be correct
	// TODO : TEST LINEAR PROBING
	// linear probing
	// h and i aren't used in this collision.
	hashNode *theNode = *(this->map+i);
	if(theNode->keyword == k){
		return i;
	}
	if(i == this->mapSize-1){ // reach the end of the map
		if(*(this->map+this->mapSize-1) != NULL){ // checks the last node of the map
			// last node of the map is taken
			this->collisions++;
			return coll2(h,0,k);
		}
		else{
			return i;
		}
	}
	else if(*(this->map+i) != NULL){ // index is already taken
		this->collisions++;
		return coll2(h,i+1,k); // re-call the function with index+1
	}
	else{
		return i;
	}
	//return k % this->mapSize;

}
int hashMap::findKey(string k) { // TODO : FINDKEY

	int theIndex = getIndex(k);
	return theIndex;
	// call getindex
	// given a key and find it in the map
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
	return -1;

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


