#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

struct Reservation
{
    int reservationID;
    int studentID;
    int resourceID;
    string date;
    string time;
};

#endif

