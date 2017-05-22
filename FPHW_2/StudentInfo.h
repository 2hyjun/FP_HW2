#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <string.h>

class StudentInfo{
public:
    char mName[20];
    unsigned mStudentID;
    float mScore;
    unsigned mAdvisorID;
    
    StudentInfo(char _name[20], unsigned _studentID, 
        float _score, unsigned _advisorID);
    StudentInfo(const StudentInfo& _std);
};

#endif //  STUDENTINFO_H
