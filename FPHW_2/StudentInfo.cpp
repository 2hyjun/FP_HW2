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