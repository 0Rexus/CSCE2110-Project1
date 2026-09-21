#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include "Reservation.h"
#include <stack>

class CancellationHistory {
private:
    std::stack<Reservation> cancelledReservations;

public:
    void addCancelledReservation(const Reservation& reservation);
    bool restoreLastCancellation(Reservation& restored);
    void displayHistory();
};

#endif