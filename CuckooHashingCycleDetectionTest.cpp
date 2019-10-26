int main(){

	//driver code
	// Random seed if you want random tables to be generated always
	//srand(time(0));
	// Random Seed if you want the same random table to be generated
	srand(15);

	CuckooHashTable cHT = CuckooHashTable(5,2);

	for (int i=0;i<100;i++) {
		cout<<"["<<i<<"] => "<<cHT.hashKey(0,i)<<"  "<<cHT.hashKey(1,i)<<endl;
	}

	bool insert;

	cout<<endl<<"Insert 6"<<endl;
	insert = cHT.insertKey(6);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();

	cout<<endl<<"Insert 7"<<endl;
	insert = cHT.insertKey(7);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}

	cHT.printHashTable();
	cout<<endl<<"Insert 13"<<endl;
	insert = cHT.insertKey(13);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();

	cout<<endl<<"Insert 15"<<endl;
	insert = cHT.insertKey(15);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	
	cHT.printHashTable();
	cout<<endl<<"Insert 66"<<endl;
	insert = cHT.insertKey(66);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();

	/*
	cout<<endl<<"Insert 18"<<endl;
	insert = cHT.insertKey(18);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();
	
	// cout<<endl<<"Insert 41"<<endl;
	// insert = cHT.insertKey(41);
	// if (!insert) {
	// 	cout<<"Insert Failed"<<endl;
	// }
	// cHT.printHashTable();

	// cout<<endl<<"Insert 22"<<endl;
	// insert = cHT.insertKey(22);
	// if (!insert) {
	// 	cout<<"Insert Failed"<<endl;
	// }
	// cHT.printHashTable();
	
	cout<<endl<<"Insert 44"<<endl;
	insert = cHT.insertKey(44);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();

	cout<<endl<<"Insert 59"<<endl;
	insert = cHT.insertKey(59);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();
	
	cout<<endl<<"Insert 32"<<endl;
	insert = cHT.insertKey(32);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();
	
	cout<<endl<<"Insert 31"<<endl;
	insert = cHT.insertKey(31);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();
	
	cout<<endl<<"Insert 18"<<endl;
	insert = cHT.insertKey(18);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();
	
	// cout<<endl<<"Insert 88"<<endl;
	// insert = cHT.insertKey(88);
	// if (!insert) {
	// 	cout<<"Insert Failed"<<endl;
	// }
	// cHT.printHashTable();
	/*
	cout<<endl<<"Insert 21"<<endl;
	insert = cHT.insertKey(21);
	if (!insert) {
		cout<<"Insert Failed"<<endl;
	}
	cHT.printHashTable();	*/
	return 0;
}
