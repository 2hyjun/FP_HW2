#include "DBHelper.h"

DBHelper::DBHelper()
	: mStudentSize(0)
	, mStudentData(nullptr) {
	mHashMap = new HashMap();
	mFileDB.open("Student.DB", ios::binary | ios::out);
}

void DBHelper::GetDataFromFile() {
	ifstream fin(INPUT_FILE_NAME);
	if (fin.fail()) {
		cout << "Could not find " << INPUT_FILE_NAME << endl;
		exit(0);
	}
	string sData;
	stringstream ss;

	getline(fin, sData);
	ss.str(sData);
	ss >> mStudentSize;
	mStudentData = new StudentInfo[mStudentSize];
	for (int i = 0; i < mStudentSize; i++) {
		string sData2;
		stringstream ss2;
		string split_by_comma[4];
		getline(fin, sData2);
		ss2.str(sData2);
		SplitByComma(sData2, split_by_comma);
		mHashMap->Insert(atoi(split_by_comma[1].c_str()));
		mStudentData[i] = StudentInfo(sData2);
	}
	//mHashMap->PrintHashTable();
}

void DBHelper::CreateDBFile() {
	int tableSize = mHashMap->mTableSize;
	int* countArr = new int[tableSize];
	fill_n(countArr, tableSize, 0);

	mFileDB.seekp(0);
	for (int i = 0; i < mStudentSize; i++) {
		StudentInfo std = mStudentData[i];
		int blockNum = mHashMap->GetBlockNumber(std.mStudentID);
		int pos = blockNum * 4096 + countArr[blockNum] * (NAMELENGTH + 12);
		mFileDB.seekp(pos);

		mFileDB.write((char*)&std.mName, sizeof(std.mName));
		mFileDB.write((char*)&std.mStudentID, sizeof(std.mStudentID));
		mFileDB.write((char*)&std.mScore, sizeof(std.mScore));
		mFileDB.write((char*)&std.mAdvisorID, sizeof(std.mAdvisorID));
		countArr[blockNum]++;
	}
	
	delete[] countArr;
}
void DBHelper::CreateHashFile() {
	mHashMap->CreateHashFile();
}
void DBHelper::CreateIndexFile() {
	
}

DBHelper::~DBHelper() {
	delete mHashMap;
	delete[] mStudentData;
	mFileDB.close();
}