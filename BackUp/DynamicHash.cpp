#include "DynamicHash.h"

//***************************      Utils     ************************************

/*
************************************LinkedHashEntry************************************
*/

LinkedHashEntry::LinkedHashEntry(int _key, StudentInfo _student)
	: mKey(_key)
	, mStudent(_student)
	, mNext(nullptr) {}

int LinkedHashEntry::GetKey() const {
	return mKey;
}

StudentInfo LinkedHashEntry::GetStudent() const {
	return mStudent;
}

LinkedHashEntry* LinkedHashEntry::GetNext() const {
	return mNext;
}

void LinkedHashEntry::SetKey(int _key) {
	mKey = _key;
}
void LinkedHashEntry::SetStudent(StudentInfo _student) {
	mStudent = _student;
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


	mFileDB.open("Student.DB", ios::binary | ios::out);
	mFileHash.open("Student.Hash", ofstream::binary | ios::out);
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
				Insert(entry->GetStudent());
				oldEntry = entry;
				entry = entry->GetNext();
				delete oldEntry;
		}
	}
	delete[] oldTable;
	cout << "****Hash Table Resized!!\n";
	//PrintHashTable();
}

int HashMap::HashFunc(StudentInfo _student) {

	unsigned value = _student.mStudentID;
	
	return value % mTableSize;
}

StudentInfo HashMap::GetInfoByKey(int _key) {
	return StudentInfo(nullptr);
}

void HashMap::Insert(StudentInfo _stud) {
	int hash = HashFunc(_stud);
	int key = _stud.mStudentID;
	 
	if (mTable[hash] == nullptr) {
		mTable[hash] = new Bucket();
		mTable[hash]->SetFirst(new LinkedHashEntry(key, _stud));
		mWholeNumEntry++;
		mTable[hash]->SetNumEntry(mTable[hash]->GetNumEntry() + 1);
	}
	else {
		if (mTable[hash]->IsFull()) {
			Resize();
			Insert(_stud);
			return;
		}

		LinkedHashEntry *entry = mTable[hash]->GetFirst();
		while (entry->GetNext() != NULL)
			entry = entry->GetNext();
		entry->SetNext(new LinkedHashEntry(key, _stud));
		mWholeNumEntry++;
		mTable[hash]->SetNumEntry(mTable[hash]->GetNumEntry() + 1);

		
	}
	//PrintHashTable();
}

void HashMap::PrintHashTable() {
	cout << "****************************************************\n" << endl;
	for (int i = 0; i < mTableSize; i++) {
		cout << "Table[" << i 
			<< "]---------------------------------------------------\n";
		if (mTable[i] == nullptr)
			continue;
		LinkedHashEntry* entry = mTable[i]->GetFirst();
		
		while (entry != nullptr) {
			cout << "\t\t\t"
				<< entry->GetStudent().mStudentID << ", "
				<< entry->GetStudent().mName << ", "
				<< entry->GetStudent().mScore << ", "
				<< entry->GetStudent().mAdvisorID << endl;
			entry = entry->GetNext();
		}
		cout << "---------------------------------------------------------\n";
	}
	cout << "\n****************************************************\n" << endl;
}

void HashMap::GetDataFromFile() {
	ifstream fin(INPUT_FILE_NAME);
	string sData;
	stringstream ss;
	int N;

	getline(fin, sData);
	ss.str(sData);
	ss >> N; 
	
	for (int i = 0; i < N; i++) {
		string sData2;
		stringstream ss2;

		getline(fin, sData2);
		ss2.str(sData2);
		
		Insert(StudentInfo(sData2));
		//PrintHashTable();
	}
}


void HashMap::PrintOutHashFile() {
	for (int i = 0; i < mTableSize; i++) {
		if (mTable[i] == nullptr)
			continue;
		LinkedHashEntry* entry = mTable[i]->GetFirst();

		while (entry != nullptr) {
			int stdID = entry->GetStudent().mStudentID;
			
			mFileHash.write((char*)&stdID, sizeof(stdID));
			
			entry = entry->GetNext();
		}
	}
}