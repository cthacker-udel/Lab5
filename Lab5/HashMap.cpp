#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <math.h>
#include <vector>
// includes added
#include <unistd.h>

using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {

	this->first = ""; //
	this->numKeys = 0; //
	this->mapSize = 371;
	this->map = new hashNode*[this->mapSize];
	for(int i = 0; i < this->mapSize; i++){
		*(this->map+i) = NULL;
	}
	this->hashfn = hash1; ///
	this->collfn = coll1; //
	this->collisions = 0;
	this->hashcoll = 0; //

}

void hashMap::addKeyValue(string k, string v) { // TODO : ADDKEYVALUE

	// collisions will happen here not in getIndex
	if(v == ""){
		return;
	}
	//cout << "Entering addkeyvalue with key\n" << k << " and value " << v << endl;
	int index = getIndex(k);
	//this->numKeys++;
	//cout << "index generated was : " << index << endl;
	if(*(this->map+index) != NULL){
		hashNode *theNode = *(this->map+index);
		if(theNode->keyword == k){
			theNode->addValue(v);
		}
		else{
			cout << "failed to implement" << endl;
			sleep(5);
		}
	}
	else{
		*(this->map+index) = new hashNode(k,v);
		this->numKeys++;
	}
	reHash(); // check if the size is at the threshold


}

int hashMap::getIndex(string k) { // TODO : GETINDEX
	//reHash();
	// uses calchash and returns the index of the keyword k, use calchash, and then see if the key where the
	//index thats returned is is the same as the key given, if not, then we have a collision, use coll1,
	//find the key there, see if its the same

	// it might happen(the if statements) because if the process of how we got to place the key
	// is through collision functions then we have to repeat the process to find it
	unsigned long index1;
	//cout << "entering getindex" << endl;


	int iter = 0;
	if(this->hashfn){
		index1 = calcHash1(k);
	}
	else{
		index1 = calcHash2(k);
	}
	if(this->map[index1] != NULL && this->map[index1]->keyword != k){
		this->hashcoll++;
	}

	while(*(this->map+index1) != NULL){
		hashNode *theNode = *(this->map+index1);
		if(theNode->keyword == k){
			return index1;
		}
		else if(this->collfn){
			this->collisions++;
			index1 = coll1(index1,iter++,k); // pass in hashcoll in the second
			//return index1;
		}
		else{
			this->collisions++;
			index1 = coll2(index1,iter++,k); // pass in hashcoll in the second
			//return index1;
		}
	}
	return index1;
	//return -1;
}

// TODO : Rework calchash2
int hashMap::calcHash2(string k){ // complete

	int p = 7;
	int total = 0;
	for(int i = k.length()-1; i >= 0; i--){
		total = (p * total) + ((int)k.at(i));
	}
	if(total < 0){
		total = total * -1;
	}
	return total % this->mapSize;

}

int hashMap::calcHash1(string k){ // complete

	int p = 7;
	int total = 0;
	for(int i = 0; i < ((int)k.length()); i++){
		total = p+total + k.at(i);
	}
	if(total < 0){
		total = total * -1;
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
	//cout << "ratio = " << (this->numKeys*1.0 / this->mapSize) << endl;
	if(this->numKeys*1.0 / this->mapSize >= .70){

		//cout << "size of map is " << this->numKeys << endl;
		// double array size and rehash
		//cout << "entered rehash function" << endl;

		int tmpMapSize = this->mapSize;

		getClosestPrime(); // <---- double map size
		// TODO : rehash all keys, use addkeyvalue

		//cout << "before for loop" << endl;

		for(int i = 0; i < tmpMapSize; i++){
			hashNode *theNode = *(this->map+i);
			if(theNode != NULL){
					// value there
					nodes.push_back(theNode);
			}
		}

		// double map size

		this->map = new hashNode*[this->mapSize];
		for(int i = 0; i < this->mapSize; i++){
			*(this->map+i) = NULL;
		}

		//cout << "after for loop" << endl;

		// adding in all the nodes

		for(int i = 0; i < ((int)nodes.size()); i++){

			hashNode *theNode = nodes.at(i); // get curr node in node list
			*(map+getIndex(theNode->keyword)) = theNode;

		}
		//cout << "\n\n---- AFTER REHASHING ----\n\n" << endl;
		//printMap();

	}

}
int hashMap::coll1(int h, int i, string k) {
	// TODO : TEST DOUBLE HASHING
	// might require same methodology of coll2, in the sense that we keep calling it until it finds a valid index

	hashNode *theNode = *(this->map+h);
	if(theNode != NULL && theNode->keyword == k){
		return i;
	}

	int res = calcHash2(k);
	unsigned long result = (h + i *res) % this->mapSize;
	if(result < 0){
		result = result * -1;
	}
	return result;
	// double hashing

}
int hashMap::coll2(int h, int i, string k) { // TODO : COLL2 , should be correct
	// TODO : TEST LINEAR PROBING
	// linear probing
	// h and i aren't used in this collision.
	unsigned long result = (h+(i*i)) % this->mapSize;
	if(result < 0){
		result = result * -1;
	}
	return result;

}
int hashMap::findKey(string k) { // TODO : FINDKEY

	int theIndex = getIndex(k);

	if(*(map+theIndex) != NULL){
		hashNode *theNode = *(map+theIndex);
		if(theNode->keyword == k){
			return theIndex;
		}
		else{
			return -1;
		}
	}
	else{
		return -1;
	}

	/*
	 *
	 * This is most likely where the problem lies
	 *
	 * 2 checks:
	 *
	 * 1) check if the index is empty <--- showing me where to place it
	 * 2) check if the index has values <--- is it the right value
	 *
	 */

	//return theIndex;
	// call getindex
	// given a key and find it in the map
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
	//return -1;

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
	cout << "Reached end of printmap" << endl;
}


