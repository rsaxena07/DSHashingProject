/*

	CS 261P - Data Structures Project 1
	Hashing Algorithms

	Title: Hashing Algorithms Test Suite
	Author: Rishabh Saxena
	UCInetID: rsaxena3
	Student ID: 72844211 

*/
/*	Header Files include	*/
#include<iostream>
#include<ctime>			// for srand intilization time()
#include<iomanip>		// for setprecision()
#include<fstream>		// for file i/o
#include<sys/time.h> 	// for time calc 

/*	Including user defined header files for CodeBase	*/
#include"HashFunction.hpp"
#include"Chaining.hpp"
#include"Cuckoo.hpp"

/*	TEST PARAMETERS	*/
#define CHAIN_ALPHAS_GENERATED 1000
#define CHAIN_HASH_SIZE 10000
#define CHAIN_MAX_ALPHA 5
#define CUCKOO_ALPHAS_GENERATED 1000
#define CUCKOO_HASH_SIZE 10000
#define CUCKOO_N_TABLES 2

using namespace std;

void ChainHashingTester(bool printDetails) {

	TabulationHash h = TabulationHash();
	HashChainingTable hT(CHAIN_HASH_SIZE, &h);

	//File IO fpointer
	ofstream inputDataDump, executionTimeDump, executionParams;
	executionTimeDump.open("data/chainingExecutionTimeRecords.csv");
	inputDataDump.open("data/chainingInputDataDump.csv");
	
	//Storing execution parameters
	executionParams.open("data/chainingExecutionParams.txt");
	executionParams<<"Hash Table Size: "<<CHAIN_HASH_SIZE<<endl;
	executionParams<<"Alphas generated: "<<CHAIN_ALPHAS_GENERATED<<endl;
	executionParams<<"Max Alpha: "<<CHAIN_MAX_ALPHA<<endl;
	executionParams.close();

	executionTimeDump<<"alpha,keysToInsert,timeTaken,accessCount"<<endl;
	for (int i=0;i<CHAIN_ALPHAS_GENERATED;i++) {
		double alpha = (((double) (rand() % CHAIN_HASH_SIZE)) / CHAIN_HASH_SIZE) * CHAIN_MAX_ALPHA;
		int keysToInsert = alpha * CHAIN_HASH_SIZE;
		struct timespec start, end; 
		double totalTimeTaken=0;
		int key, totalAccessCount=0, accessCount;

		cout<<"i: "<<i<<" ALPHA: "<<alpha<<" KEYS TO INSERT: "<<keysToInsert<<endl;

		for (int j=0;j<keysToInsert;j++) {
			key = rand() % INT_MAX;

			clock_gettime(CLOCK_MONOTONIC, &start); 
			hT.insertKey(key);
			clock_gettime(CLOCK_MONOTONIC, &end); 

			//lookup to calculate access count
			accessCount = hT.lookupKey(key);
			if (accessCount == -1) {
				cout<<"ERROR!!"<<endl;
				continue;
			}

			// calculate time taken
			double time_taken = 0; 
			time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
			time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-3; 
			totalTimeTaken += time_taken;
			totalAccessCount+=accessCount;
			if (j!=0)
				inputDataDump<<",";
			inputDataDump<<key;
		}
		cout << "Time taken by program is : " << fixed << totalTimeTaken << setprecision(6)<<" msec"<<endl;

		// file operations
		executionTimeDump<<alpha<<","<<keysToInsert <<","<<totalTimeTaken << setprecision(6)<<","<<totalAccessCount<<endl;
		inputDataDump<<endl;

		if (printDetails)
			hT.printHashTable();
		hT.emptyHashTable();
	}

	executionTimeDump.close();
	inputDataDump.close();
	return;
}


void CuckooHashingTester(bool printDetails) {

	CuckooHashTable cHT = CuckooHashTable(CUCKOO_HASH_SIZE, CUCKOO_N_TABLES);

	//File IO fpointer
	ofstream inputDataDump, executionTimeDump, executionParams;
	executionTimeDump.open("data/cuckooExecutionTimeRecords.csv");
	inputDataDump.open("data/cuckooInputDataDump.csv");
	executionParams.open("data/cuckooExecutionParams.txt");
	executionParams<<"Hash Table Size: "<<CUCKOO_HASH_SIZE<<endl;
	executionParams<<"Number of Cuckoo Hash Tables: "<<CUCKOO_N_TABLES<<endl;
	executionParams<<"Alphas generated: "<<CUCKOO_ALPHAS_GENERATED<<endl;
	executionParams.close();
	executionTimeDump<<"alpha,keysToInsert,timeTaken,accessCount"<<endl;

	int totalHashTableBuckets = CUCKOO_HASH_SIZE * CUCKOO_N_TABLES; 
	for (int i=0;i<CUCKOO_ALPHAS_GENERATED;i++) {
		// We do not increase alpha beyong 0.5 for Cuckoo Hashing
		double alpha = ((double) (rand() % CUCKOO_HASH_SIZE))/ totalHashTableBuckets;
		int keysToInsert = alpha * totalHashTableBuckets;
		double totalTimeTaken=0;
		long totalAccessCount = 0;

		cout<<"i: "<<i<<" ALPHA: "<<alpha<<" KEYS TO INSERT: "<<keysToInsert<<endl;

		for (int j=0;j<keysToInsert;j++) {
			int key = rand() % INT_MAX;
			long accessCount;
			struct timespec start, end; 
			clock_gettime(CLOCK_MONOTONIC, &start); 
			accessCount = cHT.insertKey(key);
			clock_gettime(CLOCK_MONOTONIC, &end); 

			double time_taken; 
			time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
			time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-3; 
			totalTimeTaken += time_taken;
			totalAccessCount += accessCount;

			if (j!=0)
				inputDataDump<<",";
			inputDataDump<<key;
		}
		cout << "Time taken by program is : " << fixed << totalTimeTaken << setprecision(6)<<" msec"<<endl;  
		
		executionTimeDump<<alpha<<","<<keysToInsert<<","<<totalTimeTaken<<","<<totalAccessCount<<endl;
		inputDataDump<<endl;
		if (printDetails)
			cHT.printHashTable();
		cHT.emptyHashTable();
	}
	inputDataDump.close();
	executionTimeDump.close();
	return;
}

int main(){
	//driver code

	// Random seed if you want random tables to be generated always
	// srand(time(0));
	// Random Seed if you want the same random table to be generated
	srand(12);

	ChainHashingTester(false);

	return 0;
}