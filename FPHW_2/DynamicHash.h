#ifndef DYNAMICHASH_H
#define DYNAMICHASH_H

#include <iostream>
#include "StudentInfo.h"

using namespace std;

//************************************LinkedHashEntry************************************
class LinkedHashEntry {
private:
	int mKey;
	StudentInfo mStudent;
	LinkedHashEntry *mNext;
public:
	LinkedHashEntry(int _key, StudentInfo _student);

	int GetKey() const;
	StudentInfo GetStudent() const;
	LinkedHashEntry* GetNext() const;

	void SetKey(int _key);
	void SetStudent(StudentInfo _student);
	void SetNext(LinkedHashEntry* _next);
};

//************************************Bucket************************************

class Bucket {
private:
	int mNumEntry;
	int mBucketSize;
	LinkedHashEntry* mFirst;
public:
	Bucket();
	LinkedHashEntry* GetFirst() const;
	
};

//************************************HashMap************************************
class HashMap {
private:
	int mHashPrefix;
	int mCurrentEntrySize;
	Bucket** mTable;
	void Resize();
	int HashFunc(StudentInfo _student);
public:
	HashMap();
	StudentInfo GetInfoByKey(int _key);
	void Insert(StudentInfo _student);
	~HashMap();
};

#define DEFAULT_HASH_PREFIX 7
#define DEFAULT_BUCKET_SIZE 4
#endif //  DYNAMICHASH_H
