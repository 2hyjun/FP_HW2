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
	friend class HashMap;
	friend class Bucket;
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
	int mLocalDepth;
	LinkedHashEntry* mFirst;
public:
	Bucket(int _localdepth);
	LinkedHashEntry* GetFirst() const;

	void Append(LinkedHashEntry* _entry);
	void Delete(LinkedHashEntry* _entry);

	bool operator=(Bucket* _rhs);
	void SetFirst(LinkedHashEntry* _newfirst);
	void SetNumEntry(int _numentry);
	bool IsFull() const;
	int GetNumEntry() const;
	int GetBucketSize() const;
	int GetLocalDepth() const;
	void SetLocalDepth(int _depth);
	void IncreaseNum();
};

//************************************HashMap************************************
class HashMap {
private:
	int mTableSize;
	int mGlobalDepth;
	int mWholeNumEntry;
	
	fstream mFileDB;
	fstream mFileHash;

	void Resize();
	int HashFunc(unsigned _key);
	friend class LinkedHashEntry;
	
public:
	Bucket** mTable;
	HashMap();
	//StudentInfo GetInfoByKey(int _key);
	void Insert(unsigned _key);
	~HashMap();
	
	void IncreaseHashTable();
	void PrintHashTable();
	void GetDataFromFile();
	void PrintOutHashFile();
	void PrintOutDBFile(char _name[20], unsigned _stdID, float _score, unsigned _advID);
	void Destructor(int _tablenum);
	void RecursiveDestuctor(LinkedHashEntry* _entry);

	void HandleOverflow(int tableNum, unsigned _key);
	//void Redistriute(int _oldtablenum, Bucket* oldBucket, Bucket* newBucket);
	void Redistribute(int _oldtablenum, Bucket* bucket1, Bucket* bucket2);
	void RePointing1(int _oldtablenum, int _key, Bucket* _oldbucket, Bucket* _newbucket);
	void RePointing2(int _oldtablenum, int _key, Bucket* _oldbucket, Bucket* _newbucket);
};
//*********************************** Utils ************************************
void SplitByComma(string _data, string split_by_comma[4]);
#define DEFAULT_TABLE_SIZE 2
#define DEFAULT_BUCKET_SIZE 4
//(int)(4096 / 35)
							// block size / (20 + 4 + 4 + 4 + 3(3commas))
#define INPUT_FILE_NAME "data5.inp"
#endif //  DYNAMICHASH_H
