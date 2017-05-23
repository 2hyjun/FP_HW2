#ifndef STUDENTINFO_H
#define STUDENTINFO_H


#include <cstring>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

class StudentInfo{
public:
    char mName[20];
    unsigned mStudentID;
    float mScore;
    unsigned mAdvisorID;
    
    StudentInfo(char _name[20], unsigned _studentID, 
        float _score, unsigned _advisorID);
    StudentInfo(const StudentInfo& _std);
	StudentInfo(string sData);
	
};

#endif //  STUDENTINFO_H
