#include "DynamicHash.h"
#include <math.h>

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
	
/*
************************************HashMap************************************
*/

HashMap::HashMap() 
	: mHashPrefix(DEFAULT_HASH_PREFIX)
	, mCurrentEntrySize(0) {
	int tableSize = pow(2, mHashPrefix);
	mTable = new Bucket*[tableSize];	
	for (int i = 0; i < tableSize; i++)
		mTable[i] = nullptr;
}

HashMap::~HashMap() {

}

void HashMap::Resize() {
	
}

int HashMap::HashFunc(StudentInfo _student) {

	unsigned value = _student.mStudentID;
	int tableSize = pow(2, mHashPrefix);
	
	return value % tableSize;
}

StudentInfo HashMap::GetInfoByKey(int _key) {

}	