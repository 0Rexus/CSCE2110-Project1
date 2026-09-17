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

    void insertReservation(const Reservation& reservation);
    bool removeReservation(int reservationID);
    void displayReservations() const;
};

#endif