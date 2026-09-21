#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

struct Reservation
{
    int reservationID;
    int studentID;
    std::string resourceID;
    std::string date;
    std::string time;
};

#endif