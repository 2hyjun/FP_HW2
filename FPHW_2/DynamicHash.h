#ifndef DYNAMICHASH_H
#define DYNAMICHASH_H

#include <iostream>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <fstream>
//#include "StudentInfo.h"

using namespace std;

//************************************LinkedHashEntry************************************
class LinkedHashEntry {
private:
	unsigned mKey;
	unsigned mBlockNumber;
	//StudentInfo mStudent;
	LinkedHashEntry *mNext;
public:
	LinkedHashEntry(unsigned _key, unsigned _block_number);

	unsigned GetKey() const;
	//StudentInfo GetStudent() const;
	unsigned GetBlockNumber() const;
	LinkedHashEntry* GetNext() const;

	void SetKey(unsigned _key);
	//void SetStudent(StudentInfo _student);
	void SetBlockNumber(unsigned _block_number);
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

	void Resize();
	int HashFunc(unsigned _key);
	
public:
	Bucket** mTable;
	HashMap();
	//StudentInfo GetInfoByKey(int _key);
	void Insert(unsigned _key);
	~HashMap();
	void PrintHashTable();
	void GetDataFromFile();
	void PrintOutHashFile();
	void PrintOutDBFile(char _name[20], unsigned _stdID, float _score, unsigned _advID);
	void Destructor(int _tablenum);
	void RecursiveDestuctor(LinkedHashEntry* _entry);
};
//*********************************** Utils ************************************
void SplitByComma(string _data, string split_by_comma[4]);
#define DEFAULT_TABLE_SIZE 2
#define DEFAULT_BUCKET_SIZE (int)(4096 / 35)
							// block size / (20 + 4 + 4 + 4 + 3(3commas))
#define INPUT_FILE_NAME "data3.csv"
#endif //  DYNAMICHASH_H
