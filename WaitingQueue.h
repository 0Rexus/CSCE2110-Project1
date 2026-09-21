#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <string>
using namespace std;

struct StudentNode
{
    int studentID;
    StudentNode* next;
};

class WaitingQueue
{
private:
    StudentNode* front;
    StudentNode* rear;

public:
    WaitingQueue();

    void addStudent(int studentID);
    bool removeStudent(int& studentID);
    void displayWaitingList() const;
};

#endif