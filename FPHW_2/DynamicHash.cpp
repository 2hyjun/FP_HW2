#include "DynamicHash.h"
#include <assert.h>
//***************************      Utils     ************************************

/*
************************************LinkedHashEntry************************************
*/

LinkedHashEntry::LinkedHashEntry(unsigned _key, unsigned _block_number)
	: mKey(_key)
	, mBlockNumber(_block_number)
	, mNext(nullptr) {}

unsigned LinkedHashEntry::GetKey() const {
	return mKey;
}
unsigned LinkedHashEntry::GetBlockNumber() const {
	return mBlockNumber;
}
/*StudentInfo LinkedHashEntry::GetStudent() const {
	return mStudent;
}*/

LinkedHashEntry* LinkedHashEntry::GetNext() const {
	return mNext;
}

void LinkedHashEntry::SetKey(unsigned _key) {
	mKey = _key;
}
/*void LinkedHashEntry::SetStudent(StudentInfo _student) {
	mStudent = _student;
}*/

void LinkedHashEntry::SetBlockNumber(unsigned _block_number) {
	mBlockNumber = _block_number;
}
void LinkedHashEntry::SetNext(LinkedHashEntry* _next) {
	mNext = _next;
}

/*
************************************Bucket************************************
*/

Bucket::Bucket(int _localdepth)
	: mNumEntry(0)
	, mBucketSize(DEFAULT_BUCKET_SIZE) 
	, mLocalDepth(_localdepth)
	, mFirst(nullptr) {
}

LinkedHashEntry* Bucket::GetFirst() const {
	return mFirst;
}

void Bucket::SetFirst(LinkedHashEntry* _newfirst) {
	mFirst = _newfirst;
}

void Bucket::SetNumEntry(int _numentry) {
	mNumEntry = _numentry;
}

int Bucket::GetNumEntry() const {
	return mNumEntry;
}

int Bucket::GetBucketSize() const {
	return mBucketSize;
}

bool Bucket::IsFull() const {
	return mNumEntry == mBucketSize;
}
void Bucket::IncreaseNum() {
	mNumEntry++;
}
int Bucket::GetLocalDepth() const {
	return mLocalDepth;
}

void Bucket::SetLocalDepth(int _depth) {
	mLocalDepth = _depth;
}
void Bucket::Append(LinkedHashEntry* _entry) {
	LinkedHashEntry* ptr = mFirst;

	if (mFirst == nullptr) {
		mFirst = _entry;
		mNumEntry++;
		return;
	}
	
	while (ptr->mNext != nullptr) {
		ptr = ptr->mNext;
	}
	ptr->mNext = _entry;
	mNumEntry++;
}

void Bucket::Delete(LinkedHashEntry* _entry) {

	assert(mFirst != nullptr);
	
	if (mFirst == _entry) {
		mFirst = mFirst->mNext;
		mNumEntry--;
	}

	LinkedHashEntry* entry1 = mFirst;
	LinkedHashEntry* entry2 = entry1->mNext;
	while (entry2 != nullptr) {
		if (entry2 == _entry) {
			entry1->mNext = entry2->mNext;
			mNumEntry--;
			break;
		}
		entry1 = entry1->mNext;
		entry2 = entry2->mNext;
	}
	assert(true);
}
/*
************************************HashMap************************************
*/

HashMap::HashMap() 
	: mTableSize(DEFAULT_TABLE_SIZE)
	, mGlobalDepth(1)
	, mWholeNumEntry(0) {


	mFileDB.open("Student.DB", ios::out | ios::trunc);
	mFileHash.open("Student.Hash", ofstream::binary | ios::out | ios :: in);
	mTable = new Bucket*[mTableSize];	
	for (int i = 0; i < mTableSize; i++)
		mTable[i] = new Bucket(mGlobalDepth);
}

HashMap::~HashMap() {
	for (int i = 0; i < mTableSize; i++)
		Destructor(i);

}
void HashMap::Destructor(int _tablenum) {
	if (mTable[_tablenum] != nullptr) {

	}
}

void HashMap::RecursiveDestuctor(LinkedHashEntry* _entry) {

}

void HashMap::Resize() {
	int oldTableSize = mTableSize;
	mTableSize *= 2;
	Bucket **oldTable = mTable;
	mTable = new Bucket*[mTableSize];
	for (int i = 0; i < mTableSize; i++)
			mTable[i] = nullptr;
	mWholeNumEntry = 0;
	for (int hash = 0; hash < oldTableSize; hash++)
		if (oldTable[hash] != nullptr) {
			LinkedHashEntry *oldEntry;
			LinkedHashEntry *entry = oldTable[hash]->GetFirst();
			while (entry != nullptr) {
				Insert(entry->GetKey());
				oldEntry = entry;
				entry = entry->GetNext();
				delete oldEntry;
		}
	}
	delete[] oldTable;
	cout << "****Hash Table Resized!!\n";
	//PrintHashTable();
}

int HashMap::HashFunc(unsigned _key) {

	return _key % mTableSize;
}

/*StudentInfo HashMap::GetInfoByKey(int _key) {
	return StudentInfo(nullptr);
}*/

void HashMap::Insert(unsigned _key) {
	int hash = HashFunc(_key);
	 
	
	if (mTable[hash]->IsFull()) {
		HandleOverflow(hash, _key);
		return;
		//hash = HashFunc(_key);
	}
	
	if (mTable[hash]->GetFirst() == nullptr) {
		mTable[hash]->SetFirst(new LinkedHashEntry(_key, hash));
	}
	else {
		LinkedHashEntry *entry = mTable[hash]->GetFirst();
		while (entry->GetNext() != NULL)
			entry = entry->GetNext();
		entry->SetNext(new LinkedHashEntry(_key, hash));
	}
	
	mWholeNumEntry++;
	mTable[hash]->IncreaseNum(); //mNumEntry++;
	PrintHashTable();
}
void HashMap::HandleOverflow(int _oldtablenum, unsigned _key) {
	if (mTable[_oldtablenum]->GetLocalDepth() == mGlobalDepth) {
		IncreaseHashTable(); // double hash table size

		Bucket* bucket1 = new Bucket(mGlobalDepth);
		Bucket* bucket2 = new Bucket(mGlobalDepth);

		Redistribute(_oldtablenum, bucket1, bucket2);
		RePointing1(_oldtablenum, _key, bucket1, bucket2);
		
	}
	else if (mTable[_oldtablenum]->GetLocalDepth() < mGlobalDepth) {
		int newLocalDepth = mTable[_oldtablenum]->GetLocalDepth() + 1;

		Bucket* bucket1 = new Bucket(newLocalDepth);
		Bucket* bucket2 = new Bucket(newLocalDepth);
		Redistribute(_oldtablenum, bucket1, bucket2);
		RePointing2(_oldtablenum, _key, bucket1, bucket2);
		/*mTable[_oldtablenum]->SetLocalDepth(newLocalDepth);
		Bucket* newBucket = new Bucket(newLocalDepth);
		Redistriute(_oldtablenum, mTable[_oldtablenum], newBucket);
		RePointing2(_oldtablenum, mTable[_oldtablenum], newBucket);*/
	}
	Insert(_key);
}
void HashMap::IncreaseHashTable() {
	int oldTableSize = mTableSize;
	Bucket** oldTable = mTable;

	mTableSize *= 2;
	mGlobalDepth++;
	mTable = new Bucket*[mTableSize];

	for (int i = 0; i < oldTableSize; i++)
		mTable[i] = oldTable[i];
	for (int i = oldTableSize; i < mTableSize; i++)
		mTable[i] = oldTable[i - mTableSize / 2];

	delete oldTable;
}
void HashMap::Redistribute(int _oldtablenum, Bucket* _bucket1, Bucket* _bucket2) {
	LinkedHashEntry* entry = mTable[_oldtablenum]->GetFirst();

	int blockNumOfFirst = HashFunc(entry->GetKey());

	while (entry != nullptr) {
		int key = entry->GetKey();
		int blockNum = HashFunc(entry->GetKey());
		if (HashFunc(entry->GetKey()) == blockNumOfFirst)
			_bucket1->Append(new LinkedHashEntry(key, blockNum));
		else
			_bucket2->Append(new LinkedHashEntry(key, blockNum));
		entry = entry->mNext;
	}
}
/*void HashMap::Redistriute(int _oldtablenum, Bucket* _oldbucket, Bucket* _newbucket) {
	LinkedHashEntry* entry = _oldbucket->GetFirst();
	// oldbucket에서 oldtablenum과 다른 hash값 가지는 것들 새 버킷에 넣기.
	while (entry != nullptr) {
		if (HashFunc(entry->mKey) != _oldtablenum) {
			_oldbucket->Delete(entry);
			_newbucket->Append(entry);
		}
		entry = entry->mNext;
	}
}*/
void HashMap::RePointing1(int _oldtablenum, int _key, Bucket* _bucket1, Bucket* _bucket2) {
	if (_bucket1->GetFirst() == nullptr) {
		Bucket* oldTable = mTable[_oldtablenum];
		mTable[HashFunc(_key)] = _bucket1;
		mTable[HashFunc(_bucket2->GetFirst()->GetKey())] = _bucket2;
		delete oldTable;
	}
	else if (_bucket2->GetFirst() == nullptr) {
		Bucket* oldTable = mTable[_oldtablenum];
		mTable[HashFunc(_bucket1->GetFirst()->GetKey())] = _bucket1;
		mTable[HashFunc(_key)] = _bucket2;
		delete oldTable;
	}
	else {
		Bucket* oldTable = mTable[_oldtablenum];
		mTable[HashFunc(_bucket1->GetFirst()->GetKey())] = _bucket1;
		mTable[HashFunc(_bucket2->GetFirst()->GetKey())] = _bucket2;
		delete oldTable;
	}
	
}
void HashMap::RePointing2(int _oldtablenum, int _key, Bucket* _bucket1, Bucket* _bucket2) {
	int localDepth = mTable[_oldtablenum]->GetLocalDepth();
	int newLocalDepth = _bucket1->GetLocalDepth();
	int oldDepthDiff = mGlobalDepth - localDepth;
	
	int numOfPointers = pow(2, oldDepthDiff);
	int* pointers = new int[numOfPointers];

	int cnt = 0;
	for (int i = 0; i < mTableSize; i++)
		if (mTable[i] == mTable[_oldtablenum])
			pointers[cnt++] = i;

	Bucket* oldTable = mTable[_oldtablenum];
	if (_bucket1->GetFirst() == nullptr) {
		int delimiter = _bucket2->GetFirst()->GetKey() % (int)pow(2, newLocalDepth);
		for (int i = 0; i < numOfPointers; i++) {
			if (pointers[i] % (int)pow(2, newLocalDepth) == delimiter)
				mTable[pointers[i]] = _bucket2;
			else 
				mTable[pointers[i]] = _bucket1;
		}
	}
	else if (_bucket2->GetFirst() == nullptr) {
		int delimiter = _bucket1->GetFirst()->GetKey() % (int)pow(2, newLocalDepth);
		for (int i = 0; i < numOfPointers; i++) {
			if (pointers[i] % (int)pow(2, newLocalDepth) == delimiter)
				mTable[pointers[i]] = _bucket1;
			else
				mTable[pointers[i]] = _bucket2;
		}
	}
	else {
		int bucket1BlockNumber = _bucket1->GetFirst()->GetKey() % (int)pow(2, newLocalDepth);
		int bucket2BlockNumber = _bucket2->GetFirst()->GetKey() % (int)pow(2, newLocalDepth);
		for (int i = 0; i < numOfPointers; i++) {
			if (pointers[i] % (int)pow(2, newLocalDepth) == bucket1BlockNumber)
				mTable[pointers[i]] = _bucket1;
			else if (pointers[i] % (int)pow(2, newLocalDepth) == bucket2BlockNumber)
				mTable[pointers[i]] = _bucket2;
			else
				assert(true);
		}
	}
	delete[] pointers;
	delete oldTable;
}


void HashMap::PrintHashTable() {
	cout << "***************   Print out Hash Table  ****************\n" << endl;
	cout << "\t\t\tGlobal Depth: " << mGlobalDepth << endl;
	for (int i = 0; i < mTableSize; i++) {
		cout << "Table[" << i 
			<< "]------Local Depth: " << mTable[i]->GetLocalDepth()<<" ---------------------------------\n";
		LinkedHashEntry* entry = mTable[i]->GetFirst();
		int cnt = 0;
		while (entry != nullptr) {
			if (cnt < 6) {
				cout << entry->GetKey() << ", " << entry->GetBlockNumber() << " | ";
				cnt++;
			}
			else {
				cout << entry->GetKey() << ", " << entry->GetBlockNumber() << endl;
				cnt = 0;
			}
			
			entry = entry->GetNext();
		}
		cout << "\n---------------------------------------------------------\n";
	}
	cout << "\n****************************************************\n" << endl;
}

void HashMap::GetDataFromFile() {
	ifstream fin(INPUT_FILE_NAME);
	if (fin.fail()) {
		cout << "Could not find " << INPUT_FILE_NAME << endl;
		exit(0);
	}
	string sData;
	stringstream ss;
	int N;

	getline(fin, sData);
	ss.str(sData);
	ss >> N; 
	
	for (int i = 0; i < N; i++) {
		char name[30];
		string sData2;
		stringstream ss2;
		string split_by_comma[4];
		getline(fin, sData2);
		ss2.str(sData2);
		SplitByComma(sData2, split_by_comma);
		Insert(atoi(split_by_comma[1].c_str()));
		
		strcpy(name, split_by_comma[0].c_str());

		if (split_by_comma[0].length() >= 20) {
			//cout << "WOW" << endl;
		}
	}
}


void HashMap::PrintOutHashFile() {

	for (int i = 0; i < mTableSize; i++) {
		if (mTable[i] == nullptr)
			continue;
		LinkedHashEntry* entry = mTable[i]->GetFirst();

		while (entry != nullptr) {
			mFileHash.write((char*)&(entry->mKey), 4);
			mFileHash.write((char*)&(entry->mBlockNumber), 4);
			entry = entry->GetNext();
		}
	}
}

void HashMap::PrintOutDBFile(char _name[20], unsigned _stdID, 
							float _score, unsigned _advID) {
	for (int i = 0; i < mTableSize; i++) {
		LinkedHashEntry* entry = mTable[i]->GetFirst();
		while (entry != nullptr) {
			int blockNum = HashFunc(_stdID);
			int curEntryNum = mTable[blockNum]->GetNumEntry() - 1;
			int pos = 4096 * blockNum;

			pos += curEntryNum * (
				sizeof(_name) + sizeof(_stdID) + sizeof(_score) + sizeof(_advID));
		}
	}
}

//*********************************** Utils ************************************
void SplitByComma(string sData, string split_by_comma[4]) {
	stringstream ss(sData);

	int cnt = 0;
	ss.str(sData);
	string temp;
	while (getline(ss, split_by_comma[cnt], ',')) {
		//cout << split_by_comma[cnt] << endl;
		cnt++;
	}
}