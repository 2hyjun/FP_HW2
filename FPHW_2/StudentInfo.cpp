#include "StudentInfo.h"

StudentInfo::StudentInfo(char _name[20], unsigned _studentID, 
                        float _score, unsigned _advisorID)
        : mStudentID(_studentID)
        , mScore(_score)
        , mAdvisorID(_advisorID) {
            strcpy(mName, _name);
}

StudentInfo::StudentInfo(const StudentInfo& _std) {
    strcpy(mName, _std.mName);
    mStudentID = _std.mStudentID;
    mScore = _std.mScore;
    mAdvisorID = _std.mAdvisorID;
}
string* SplitByComma(string sData, string split_by_comma[4]) {
	stringstream ss(sData);
	
	int cnt = 0;
	ss.str(sData);
	string temp;
	while (getline(ss, split_by_comma[cnt], ',')) {
		//cout << split_by_comma[cnt] << endl;
		cnt++;
	}
	
	
	return split_by_comma;
}

StudentInfo::StudentInfo(string sData) {
	stringstream ss;
	ss.str(sData);
	
	string split_by_comma[4];
	SplitByComma(sData, split_by_comma);

	strcpy(mName, split_by_comma[0].c_str());
	mStudentID = atoi(split_by_comma[1].c_str());
	mScore = atof(split_by_comma[2].c_str());
	mAdvisorID = atoi(split_by_comma[3].c_str());

	//cout << mName << " " << mStudentID << " " << mScore << " " << mAdvisorID << endl;
	
}
