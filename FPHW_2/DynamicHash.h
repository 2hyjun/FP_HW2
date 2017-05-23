#ifndef DYNAMICHASH_H
#define DYNAMICHASH_H

#include <iostream>
#include <math.h>
#include <fstream>
#include <cstring>
#include <sstream>
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
	void SetFirst(LinkedHashEntry* _newfirst);
	void SetNumEntry(int _numentry);
	
	int GetNumEntry() const;
	int GetBucketSize() const;
	
};

//************************************HashMap************************************
class HashMap {
private:
	int mTableSize;
	int mWholeNumEntry;
	Bucket** mTable;
	void Resize();
	int HashFunc(StudentInfo _student);
public:
	HashMap();
	StudentInfo GetInfoByKey(int _key);
	void Insert(StudentInfo _student);
	~HashMap();
	void PrintHashTable();
	void GetDataFromFile();
};
//*********************************** Utils ************************************

#define DEFAULT_TABLE_SIZE 2
#define DEFAULT_BUCKET_SIZE 2
#endif //  DYNAMICHASH_H
