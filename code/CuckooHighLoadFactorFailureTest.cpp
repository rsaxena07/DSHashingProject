/*

	CS 261P - Data Structures Project 1
	Hashing Algorithms

	Title: Cuckoo Hashing High Alpha Test Suite
	Author: Rishabh Saxena

*/
#include<iostream>
#include<sys/time.h>
#include<fstream>
#include<iomanip>

#include"HashFunction.hpp"
#include"Cuckoo.hpp"

using namespace std;

#define CUCKOO_HASH_SIZE 100
#define CUCKOO_N_TABLES 2
#define ALPHA_TEST_INCREMENT .025
#define ALPHA_MAX .90

int main() {

	srand(time(0));
	CuckooHashTable cHT = CuckooHashTable(CUCKOO_HASH_SIZE, CUCKOO_N_TABLES);

	int totalHashTableBuckets = CUCKOO_HASH_SIZE * CUCKOO_N_TABLES;
	
	struct timespec start, end; 
	double alpha = ALPHA_TEST_INCREMENT;	

	//File IO fpointer
	ofstream inputDataDump, executionTimeDump, executionParams;
	executionTimeDump.open("data/cuckooHighAlphaExecutionTimeRecords.csv");
	inputDataDump.open("data/cuckooHighAlphaInputDataDump.csv");
	executionParams.open("data/cuckooHighAlphaExecutionParams.txt");
	executionParams<<"Hash Table Size: "<<CUCKOO_HASH_SIZE<<endl;
	executionParams<<"Number of Cuckoo Hash Tables: "<<CUCKOO_N_TABLES<<endl;
	executionParams<<"Alphas Max: "<<ALPHA_MAX<<endl;
	executionParams<<"Alpha Increment: "<<ALPHA_TEST_INCREMENT<<endl;
	executionParams.close();
	executionTimeDump<<"alpha,keysToInsert,timeTaken,accessCount"<<endl;

	while (alpha<ALPHA_MAX) {

		int keysToInsert = alpha * totalHashTableBuckets, key;
		long totalAccessTimes=0;
		double totalTimeTaken=0;		
	
		cout<<endl<<endl<<"------------------------------------------------------------------"<<endl;
		cout<<"    ALPHA SELECTED=> "<<alpha<<endl;
		cout<<"------------------------------------------------------------------"<<endl<<endl;
			
		for (int j=0;j<keysToInsert;j++) {
			key = rand() % INT_MAX;
			long access;
			//cout<<j<<"insert "<<key<<endl;
			clock_gettime(CLOCK_MONOTONIC, &start); 
			access = cHT.insertKey(key);
			clock_gettime(CLOCK_MONOTONIC, &end); 

			double time_taken; 
			time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
			time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-6; 
			totalTimeTaken += time_taken;
			totalAccessTimes += access;

			if (j!=0)
				inputDataDump<<",";
			inputDataDump<<key;
		}
		cout<< "Total time taken = "<<totalTimeTaken<<"   total hash table access = "<<totalAccessTimes<<endl;
		cHT.emptyHashTable();

		executionTimeDump<<alpha<<","<<keysToInsert<<","<<totalTimeTaken<< setprecision(6)<<","<<totalAccessTimes<<endl;
		inputDataDump<<endl;
		
		alpha += ALPHA_TEST_INCREMENT;
	}
	executionTimeDump.close();
	inputDataDump.close();
	return 0;
}
