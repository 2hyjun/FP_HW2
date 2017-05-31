#ifndef DBHELPER_H
#define DBHELPER_H

#include "DynamicHash.h"
#include "StudentInfo.h"

class DBHelper {
private:
	int mStudentSize;
	StudentInfo* mStudentData;
	HashMap* mHashMap;
	fstream mFileDB;
	

public:
	DBHelper();
	~DBHelper();
	void GetDataFromFile();
	void CreateHashFile();
	void CreateIndexFile();
	void CreateDBFile();
};

#endif // DBHELPER_H