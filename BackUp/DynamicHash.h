#ifndef DYNAMICHASH_H
#define DYNAMICHASH_H

#include <iostream>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <fstream>
#include "StudentInfo.h"

using namespace std;

//************************************LinkedHashEntry************************************
class LinkedHashEntry {
private:
	int mKey;
	int mBlockNumber;
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
	bool IsFull() const;
	int GetNumEntry() const;
	int GetBucketSize() const;
};

//************************************HashMap************************************
class HashMap {
private:
	int mTableSize;
	int mWholeNumEntry;
	
	ofstream mFileDB;
	ofstream mFileHash;
	static int count;


	void Resize();
	int HashFunc(StudentInfo _stud);
	
public:
	Bucket** mTable;
	HashMap();
	StudentInfo GetInfoByKey(int _key);
	void Insert(StudentInfo _stud);
	~HashMap();
	void PrintHashTable();
	void GetDataFromFile();
	void PrintOutHashFile();
	void Destructor(int _tablenum);
	void RecursiveDestuctor(LinkedHashEntry* _entry);
};
//*********************************** Utils ************************************

#define DEFAULT_TABLE_SIZE 2
#define DEFAULT_BUCKET_SIZE 512
#define INPUT_FILE_NAME "data3.csv"
#endif //  DYNAMICHASH_H
