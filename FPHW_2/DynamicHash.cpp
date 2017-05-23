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
/*
************************************HashMap************************************
*/

HashMap::HashMap() 
	: mTableSize(DEFAULT_TABLE_SIZE)
	, mWholeNumEntry(0) {
	
	mTable = new Bucket*[mTableSize];	
	for (int i = 0; i < mTableSize; i++)
		mTable[i] = nullptr;
}

HashMap::~HashMap() {

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
	//PrintHashTable();
}

int HashMap::HashFunc(StudentInfo _student) {

	unsigned value = _student.mStudentID;
	
	return value % mTableSize;
}

StudentInfo HashMap::GetInfoByKey(int _key) {
	return StudentInfo("������", 201524552, 4.5, 123);
}

void HashMap::Insert(StudentInfo _stud) {
	 int hash = HashFunc(_stud);
	 int key = _stud.mStudentID;
	 
	 if (mTable[hash] == NULL) {
		mTable[hash] = new Bucket();
		mTable[hash]->SetFirst(new LinkedHashEntry(key, _stud));
		mWholeNumEntry++;
	} 
	else {
		if (mTable[hash]->GetNumEntry() >= DEFAULT_BUCKET_SIZE)
			Resize();
		LinkedHashEntry *entry = mTable[hash]->GetFirst();
		while (entry->GetNext() != NULL)
			entry = entry->GetNext();
		entry->SetNext(new LinkedHashEntry(key, _stud));
		mWholeNumEntry++;
		mTable[hash]->SetNumEntry(mTable[hash]->GetNumEntry() + 1);
	}
}

void HashMap::PrintHashTable() {
	
	for (int i = 0; i < mTableSize; i++) {
		cout << "Table[" << i << "]\n";
		if (mTable[i] == nullptr)
			continue;
		LinkedHashEntry* entry = mTable[i]->GetFirst();
		
		while (entry != nullptr) {
			cout << "\t\t\t\t\t\t"
				<< entry->GetStudent().mStudentID << ", "
				<< entry->GetStudent().mName << ", "
				<< entry->GetStudent().mScore << ", "
				<< entry->GetStudent().mAdvisorID << endl;
			entry = entry->GetNext();
		}
	}
	cout << endl;
}

void HashMap::GetDataFromFile() {
	ifstream fin("data.inp");
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
	}

}