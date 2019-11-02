/*

	CS 261P - Data Structures Project 1
	Hashing Algorithms

	Title: Hash Chaining Implementation
	Author: Rishabh Saxena
	UCInetID: rsaxena3
	Student ID: 72844211 

*/

#ifndef INCLUDE_CHAIN_HASHING
#define INCLUDE_CHAIN_HASHING

/*	header file includes	*/
#include<iostream>
#include<cstdlib>	//for rand()
#include<vector>

// Include HashFunction headerfile
#include"HashFunction.hpp"

using namespace std;

class HashChainingTable {

	const int hashTableLength;

	HashFunction* hashFunction;
	vector<vector<int> > hashTable;

	// This ensures that the returned values of any internal hash function are modded to the hashTableLength
	int hashKey(int key) {
		return (hashFunction->hashKey(key) % hashTableLength);
	}

public:
	/*	Constructor method for the hashTable intialization	
			assign value to hashTableLength
			assign hashFunction with appropriate object
			create an empty hash table with newHashTableLength number of empty vectors	*/
	HashChainingTable(int newHashTableLength, HashFunction* h):hashTableLength(newHashTableLength) {
		this->hashFunction = h;
		for (int i=0;i<hashTableLength;i++) {
			hashTable.push_back(vector<int>());
		}
	}

	/*	Method to lookup a key from the HashTable.
			First find the position of the key in the appropriate hash cell. 
			Then look for the key in that corresponding chain 
		returns number of times table was accessed if successful lookup otherwise -1 if value not found */
	int lookupKey (int key) {
		int hashIdx = this->hashKey(key);
		int chainSize = hashTable[hashIdx].size();
		for (int i=0; i<chainSize;i++) {
			if (hashTable[hashIdx][i] == key) {
				return i+1;
			}
		}
		return -1;
	}

	/*	Method to insert a key from the HashTable.
			First find the position of the key in the appropriate hash cell. 
			Then add the key at the end of the hash chain 
		returns true if successful insert */
	bool insertKey (int key) {
		int hashIdx = this->hashKey(key);
		hashTable[hashIdx].push_back(key);
		return true;
	}

	/*	Method to delete a key from the HashTable.
			First find the position of the key in the appropriate hash cell. 
			Then swap with the last value and pop_back 
			Both swap and pop_back are constant time 
		returns true if successful delete otherwise false if value not found */
	bool deleteKey (int key) {
		int hashIdx = this->hashKey(key);
		int chainSize = hashTable[hashIdx].size();
		for (int i=0; i<chainSize;i++) {
			if (hashTable[hashIdx][i] == key) {
				hashTable[hashIdx][i] = hashTable[hashIdx][chainSize-1];
				hashTable[hashIdx].pop_back();
				return true;
			}
		}
		return false;
	}

	/*	Method to print the contents of the HashTable. 
		returns true after printing the whole HashTable */
	bool printHashTable () {
		for (int i=0;i<hashTableLength;i++) {
			int s = hashTable[i].size();
			cout<<"["<< i <<"] -> ";
			for (int j=0;j<s;j++) {
				cout<<hashTable[i][j]<<" ";
			}
			cout<<endl;
		}
		return true;
	}

	/*	Method to empty the contents of the Hash Table
		Useful to clear a HashTable to test another scenario	*/
	bool emptyHashTable () {
		for (int i=0;i<hashTableLength;i++) {
			hashTable[i].clear();
		}
		return true;
	}
};

#endif