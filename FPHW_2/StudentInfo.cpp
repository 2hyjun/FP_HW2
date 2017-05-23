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

StudentInfo::StudentInfo(string sData) {
	stringstream ss;
	ss.str(sData);
	string temp, nameStr;
	unsigned stdID;
	double score;
	unsigned advID;
	char comma;

	while (ss >> temp) {
		//cout << name << endl;
		if (temp[temp.length() - 1] == ',') {
			nameStr += temp.substr(0, temp.length() - 1);
			break;

		}
		else 
			nameStr += temp + " ";
	}

	ss >> stdID >> comma
		>> score >> comma
		>> advID >> comma;
	strcpy(mName, nameStr.c_str());
	mStudentID = stdID;
	mScore = score;
	mAdvisorID = advID;

	//cout << mName << " " << mStudentID << " " << mScore << " " << mAdvisorID << endl;
	
}
