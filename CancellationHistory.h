#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include <stack>

class CancellationHistory {
    private:
        std::stack<Reservation> cancelledReservations;

    public:
        void addCancelledReservation(const Reservation& reservation);
        Reservation restoreLastCancellation();
        void displayHistory();
};

#endif