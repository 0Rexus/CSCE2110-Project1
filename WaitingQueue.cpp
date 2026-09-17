#include "WaitingQueue.h"
#include <iostream>

using namespace std;

WaitingQueue::WaitingQueue()
{
    front = nullptr;
    rear = nullptr;
}

void WaitingQueue::addStudent(int studentID)
{
    StudentNode* newNode = new StudentNode;
    newNode->studentID = studentID;
    newNode->next = nullptr;

    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

bool WaitingQueue::removeStudent(int& studentID)
{
    if (front == nullptr)
    {
        return false;
    }

    StudentNode* temp = front;
    studentID = front->studentID;

    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;
    return true;
}

void WaitingQueue::displayWaitingList() const
{
    if (front == nullptr)
    {
        cout << "Waiting list is empty." << endl;
        return;
    }

    StudentNode* current = front;

    while (current != nullptr)
    {
        cout << "Student ID: " << current->studentID << endl;
        current = current->next;
    }
}