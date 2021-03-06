#include "DynamicHash.h"

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

Bucket::Bucket()
	: mNumEntry(0)
	, mBucketSize(DEFAULT_BUCKET_SIZE) 
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
/*
************************************HashMap************************************
*/

HashMap::HashMap() 
	: mTableSize(DEFAULT_TABLE_SIZE)
	, mWholeNumEntry(0) {


	mFileDB.open("Student.DB", ios::out | ios::trunc);
	mFileHash.open("Student.Hash", ofstream::binary | ios::out | ios :: in);
	mTable = new Bucket*[mTableSize];	
	for (int i = 0; i < mTableSize; i++)
		mTable[i] = nullptr;
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
	 
	if (mTable[hash] == nullptr) {
		mTable[hash] = new Bucket();
		mTable[hash]->SetFirst(new LinkedHashEntry(_key, hash));
		mWholeNumEntry++;
		mTable[hash]->SetNumEntry(mTable[hash]->GetNumEntry() + 1);
	}
	else {
		if (mTable[hash]->IsFull()) {
			Resize();
			Insert(_key);
			return;
		}

		LinkedHashEntry *entry = mTable[hash]->GetFirst();
		while (entry->GetNext() != NULL)
			entry = entry->GetNext();
		entry->SetNext(new LinkedHashEntry(_key, hash));
		mWholeNumEntry++;
		mTable[hash]->SetNumEntry(mTable[hash]->GetNumEntry() + 1);

		
	}
	//PrintHashTable();
}

void HashMap::PrintHashTable() {
	cout << "***************   Print out Hash Table  ****************\n" << endl;
	int cnt = 0;
	for (int i = 0; i < mTableSize; i++) {
		cout << "Table[" << i 
			<< "]---------------------------------------------------\n";
		if (mTable[i] == nullptr)
			continue;
		LinkedHashEntry* entry = mTable[i]->GetFirst();
		
		while (entry != nullptr) {
			if (cnt < 3) {
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