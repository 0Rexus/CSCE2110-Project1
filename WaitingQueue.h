#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <string>
using namespace std;

struct StudentNode
{
    int studentID;
    string resourceID;
    StudentNode* next;
};

class WaitingQueue
{
private:
    StudentNode* front;
    StudentNode* rear;

public:
    WaitingQueue();
    ~WaitingQueue();

    void addStudent(int studentID, const string& resourceID);
    bool removeStudent(int& studentID, string& resourceID);

    bool popNextStudentForResource(const string& resourceID, int& studentID);
    bool hasStudentWaitingFor(const string& resourceID) const;

    void displayWaitingList() const;
    int getWaitingCount() const;
    int getWaitingCountForResource(const string& resourceID) const;
};

#endif