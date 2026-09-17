#include "CancellationHistory.h"
#include <iostream>
using namespace std;

void CancellationHistory::addCancelledReservation(const Reservation& reservation) {
    cancelledReservations.push(reservation);
}

Reservation CancellationHistory::restoreLastCancellation() {

}

void CancellationHistory::displayHistory() {

}