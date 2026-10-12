#include "WaitingQueue.h"
#include <iostream>
using namespace std;

WaitingQueue::WaitingQueue() {
    front = nullptr;
    rear = nullptr;
}

WaitingQueue::~WaitingQueue() {
    StudentNode* current = front;
    while (current != nullptr) {
        StudentNode* temp = current;
        current = current->next;
        delete temp;
    }
    front = nullptr;
    rear = nullptr;
}

void WaitingQueue::addStudent(int studentID, const std::string& resourceID) {
    StudentNode* newNode = new StudentNode;
    newNode->studentID = studentID;
    newNode->resourceID = resourceID;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

bool WaitingQueue::removeStudent(int& studentID, std::string& resourceID) {
    if (front == nullptr) return false;

    StudentNode* temp = front;
    studentID = front->studentID;
    resourceID = front->resourceID;
    front = front->next;

    if (front == nullptr) rear = nullptr;
    delete temp;
    return true;
}

bool WaitingQueue::hasStudentWaitingFor(const std::string& resourceID) const {
    StudentNode* current = front;
    while (current != nullptr) {
        if (current->resourceID == resourceID) return true;
        current = current->next;
    }
    return false;
}

bool WaitingQueue::popNextStudentForResource(const std::string& resourceID, int& studentID) {
    if (front == nullptr) return false;

    if (front->resourceID == resourceID) {
        studentID = front->studentID;
        StudentNode* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return true;
    }

    StudentNode* cur = front;
    while (cur->next != nullptr) {
        if (cur->next->resourceID == resourceID) {
            studentID = cur->next->studentID;
            StudentNode* temp = cur->next;
            cur->next = cur->next->next;
            if (cur->next == nullptr) rear = cur;
            delete temp;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void WaitingQueue::displayWaitingList() const {
    if (front == nullptr) {
        cout << "Waiting list is empty." << endl;
        return;
    }
    StudentNode* current = front;
    int pos = 1;
    while (current != nullptr) {
        cout << pos << ". Student ID: " << current->studentID 
             << " | Requested Resource: " << current->resourceID << endl;
        current = current->next;
        pos++;
    }
}

int WaitingQueue::getWaitingCount() const {
    int count = 0;
    StudentNode* current = front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}