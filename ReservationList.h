#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include "Reservation.h"

struct Node
{
    Reservation data;
    Node* next;
};

class ReservationList
{
private:
    Node* head;

public:
    ReservationList();
    ~ReservationList();

    const Node* getHead() const {
    return head;
}

    void insertReservation(const Reservation& reservation);
    bool removeReservation(int reservationID, Reservation& cancelledReservation);
    void displayReservations() const;

    bool searchReservationByID(int reservationID, Reservation& foundReservation) const;
    int searchReservationsByStudentID(int studentID) const;
};

#endif