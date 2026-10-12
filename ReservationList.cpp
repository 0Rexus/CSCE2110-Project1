#include "ReservationList.h"
#include <iostream>

using namespace std;

ReservationList::ReservationList()
{
    head = nullptr;
}

ReservationList::~ReservationList()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

void ReservationList::insertReservation(const Reservation& reservation)
{
    Node* newNode = new Node;
    newNode->data = reservation;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }
}

bool ReservationList::removeReservation(int reservationID, Reservation& cancelledReservation)
{
    if (head == nullptr)
    {
        return false;
    }

    if (head->data.reservationID == reservationID)
    {
        cancelledReservation = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr)
    {
        if (current->next->data.reservationID == reservationID)
        {
            cancelledReservation = current->next->data;
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }

        current = current->next;
    }

    return false;
}

void ReservationList::displayReservations() const
{
    if (head == nullptr)
    {
        cout << "No active reservations." << endl;
        return;
    }

    Node* current = head;

    while (current != nullptr)
    {
        cout << "Reservation ID: " << current->data.reservationID << endl;
        cout << "Student ID: " << current->data.studentID << endl;
        cout << "Resource ID: " << current->data.resourceID << endl;
        cout << "Date: " << current->data.date << endl;
        cout << "Time: " << current->data.time << endl;
        cout << "------------------------" << endl;

        current = current->next;
    }
}

bool ReservationList::searchReservationByID(int reservationID, Reservation& foundReservation) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data.reservationID == reservationID)
        {
            foundReservation = current->data;
            return true;
        }
        current = current->next;
    }

    return false;
}

int ReservationList::searchReservationsByStudentID(int studentID) const
{
    Node* current = head;
    int count = 0;

    cout << "\n--- Reservations for Student ID: " << studentID << " ---\n";

    while (current != nullptr)
    {
        if (current->data.studentID == studentID)
        {
            count++;
            cout << "Reservation ID: " << current->data.reservationID << endl;
            cout << "Resource ID:    " << current->data.resourceID << endl;
            cout << "Date:           " << current->data.date << endl;
            cout << "Time:           " << current->data.time << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    if (count == 0)
    {
        cout << "No reservations found for Student ID: " << studentID << endl;
    } else {
        cout << "Total reservations found: " << count << endl;
    }

    return count;
}