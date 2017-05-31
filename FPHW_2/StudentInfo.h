#ifndef STUDENTINFO_H
#define STUDENTINFO_H


#include <cstring>
#include <cstring>
#include <sstream>
#include <iostream>
#define NAMELENGTH 30
using namespace std;

class StudentInfo{
public:
    char mName[NAMELENGTH];
    unsigned mStudentID;
    float mScore;
    unsigned mAdvisorID;
	StudentInfo() {};
    StudentInfo(char _name[NAMELENGTH], unsigned _studentID,
        float _score, unsigned _advisorID);
    StudentInfo(const StudentInfo& _std);
	StudentInfo(string sData);
	~StudentInfo();
	
};

#endif //  STUDENTINFO_H
