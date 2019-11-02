/*

	CS 261P - Data Structures Project 1
	Hashing Algorithms

	Title: Cuckoo Hashing Implementation
	Author: Rishabh Saxena
	UCInetID: rsaxena3
	Student ID: 72844211 

*/

#ifndef INCLUDE_CUCKOO_HASHING
#define INCLUDE_CUCKOO_HASHING

/*	header file includes	*/
#include<iostream>
#include<cstdio>		//for printf()
#include<cstdlib>		//for rand()
#include<vector>

// Include HashFunction headerfile
#include"HashFunction.hpp"

using namespace std;

/* Define global paramteres for the Hashing Algorithm */
#define HASH_EMPTY_VAL INT_MIN

class CuckooHashTable {

	const int hashTableLength;
	const int numberOfHashTables;

	vector<vector<int> > hashTable;	
	vector<HashFunction *> hashFunctions;

	// This ensures that the returned values of any internal hash function are modded to the hashTableLength
	int hashKey(int idx, int key) {
		return (hashFunctions[idx]->hashKey(key) % hashTableLength);
	}

public:

	/*	Constructor to initialize the hash table with all values set to INT_MIN	*/
	CuckooHashTable(int tableLength, int newNoOfHashTables): hashTableLength(tableLength), numberOfHashTables(newNoOfHashTables) {
		hashFunctions = vector<HashFunction *>();
		for (int i=0;i<numberOfHashTables;i++) {
			hashFunctions.push_back(new TabulationHash());
			hashTable.push_back(vector<int>());
			for (int j=0;j<hashTableLength;j++) {
				hashTable[i].push_back(HASH_EMPTY_VAL);
			}
		}
	}

	/*	Destructor to deallocate dynamically allocated Hash Function array to avoid Memory Leaks*/
	~CuckooHashTable(){
		for (int i=0;i<numberOfHashTables;i++) {
			delete hashFunctions[i];
		}
	}

	/*	Method to get the contents of the entire Hash Table */
	vector<vector<int> > getHashTable() {
		return hashTable;
	}

	/*	Method to empty the contents of the Cuckoo Hash Table
		Useful for clearing table to run a new Test
		Useful to clear the contents of the HashTable after cycle detection	*/
	bool emptyHashTable() {
		for (int i=0;i<numberOfHashTables;i++) {
			for (int j=0;j<hashTableLength;j++) {
				hashTable[i][j] = HASH_EMPTY_VAL;
			}
		}
		return true;
	}

	/*	Method to refresh the Cuckkoo HashTable 
		i.e.
			Redefine Hash Functions
			Reinitialize all hash table values to empty 
		Used when cycle is detected.	*/
	bool refreshCuckooHashTable() {
		for (int i=0;i<numberOfHashTables;i++) {
			hashFunctions[i]->initTable();
		}
		emptyHashTable();
		return true;
	}

	/*	Method to insert a key into the Cuckoo Hash Table 	*/
	long insertKey(int key) {
		int timesVisitedRoot = 0;
		long totalIterations=0;
		bool sucess = insertKey(key, 0, key, timesVisitedRoot, totalIterations);
		if (!sucess) {
			// Cycle detected .. Rehash
			//cout<<"Cycle Detected"<<endl;
			vector<int> keyList;
			for (int i=0; i<numberOfHashTables;i++) {
				for (int j=0;j<hashTableLength;j++) {
					if (hashTable[i][j] != HASH_EMPTY_VAL) {
						keyList.push_back(hashTable[i][j]);
					}
				}
			}
			keyList.push_back(key);

			// empty table and refresh hash functions;
			int i=0;
			bool ret;
			do {
				i++;
				long iterations=0;
				refreshCuckooHashTable();
				ret = remakeHashTable(keyList, iterations);
				totalIterations += iterations;
			} while (!ret);
			//cout<<"Successful Rehashing attempt"<<i<<endl;
		}
		return totalIterations;
	}

	/*	Recursive method to implement cuckoo hashing insert operation.
		Return true if value is inserted.
		Return false if cycle is detected. 	*/
	bool insertKey (int key, int tableIdx, int& root, int& timesVisitedRoot, long& iterations) {

		int h = hashKey(tableIdx, key);
		iterations++;
		if (hashTable[tableIdx][h] == HASH_EMPTY_VAL) {
			//Base contition: position empty! Insert and exit
			hashTable[tableIdx][h] = key;
			return true;
		}

		//cycle detection condition
		if (key == root) {
			timesVisitedRoot +=1;
			if (timesVisitedRoot>numberOfHashTables) {
				//Loop Detected
				/* Save hashTable values and rehash by refreshing table */
				return false;
			}
		}

		int previous = hashTable[tableIdx][h];
		hashTable[tableIdx][h] = key;
		return insertKey(previous, (tableIdx+1)%numberOfHashTables, root, timesVisitedRoot, iterations);
	}

	/*	Method to delete a key from the Cuckoo Hash Table 	*/
	bool deleteKey(int key) {
		// try to look at all possible numberOfHashTable positions for the key
		for (int i=0;i<numberOfHashTables;i++) {
			int h = hashKey(i, key);
			if (hashTable[i][h] == key) {
				hashTable[i][h] = HASH_EMPTY_VAL;
				return true;
			}
		}
		return false;
	}
	
	/*	Method to lookup a key from the Cuckoo HashTable.
			Iterate through all available hash functions and check if the key is present in the corresponding hash location
		returns true if successful lookup otherwise false if value not found */
	bool lookupKey(int key) {
		// try to look at all possible numberOfHashTable positions for the key
		for (int i=0;i<numberOfHashTables;i++) {
			int h = hashKey(i, key);
			if (hashTable[i][h] == key) {
				return true;
			}
		}
		return false;
	}

	bool remakeHashTable (vector<int> keyList, long& iterations) {
		int size = keyList.size();
		long totalIterations = 0;
		for (int i=0; i<size; i++) {
			int timesVisitedRoot = 0;
			long iterations=0;
			bool ret = insertKey(keyList[i], 0, keyList[i], timesVisitedRoot, iterations);
			totalIterations += iterations;
			if (!ret) {
				return false;
			}
		}
		return true;
	}

	/*	Method to print the contents of the HashTable. 
		returns true after printing the whole HashTable */
	bool printHashTable () {
		cout<<"Idx -> ";
		for (int i=0;i<hashTableLength;i++) {
			printf("%3d ",i);
		}
		cout<<endl;
		for (int i=0;i<numberOfHashTables;i++) {
			cout<<"["<< i <<"] -> ";
			for (int j=0; j<hashTableLength;j++) {
				if (hashTable[i][j] != HASH_EMPTY_VAL) {
					printf("%3d ",hashTable[i][j]);
				} else {
					cout<<"NaN ";
				}
			}
			cout<<endl;
		}
		return true;
	}

};

#endif