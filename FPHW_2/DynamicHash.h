#ifndef DYNAMICHASH_H
#define DYNAMICHASH_H

#include <iostream>

#define HASHBLOCKINGFACTOR 113

using namespace std;
class Hashing {
private:
	BucketAddressTable* mBucketAddressTable;
	Bucket* mBuckets;
public:
	void insert();
};
class BucketAddressTable {
private:
	unsigned int mHashPrefix;
	unsigned mKey; // Student ID
	Bucket** BucketPointer;
public:

};

class Bucket {
private:
	unsigned mBlockNum;	
	char mStudentName[20];
	unsigned mStudentID;
	float mScore;
	unsigned advisorID;
public:

};


#endif /*DYNAMICHASH_H*/

