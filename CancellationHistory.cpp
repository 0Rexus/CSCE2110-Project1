#include "CancellationHistory.h"
#include <iostream>
using namespace std;

void CancellationHistory::addCancelledReservation(const Reservation& reservation) {
    cancelledReservations.push(reservation);
}

Reservation CancellationHistory::restoreLastCancellation() {
    if (cancelledReservations.empty()) {
        cout << "No cancelled reservations to restore." << endl;
        return Reservation();
    }

    Reservation restored = cancelledReservations.top();
    cancelledReservations.pop();
    return restored;
}

void CancellationHistory::displayHistory() {
    if (cancelledReservations.empty()) {
        cout << "No cancellation in history." << endl;
        return;
    }

    cout << "Cancellation History:" << endl;
    stack<Reservation> temp = cancelledReservations;

    while (!temp.empty()) {
        Reservation reservation = temp.top();
        cout << "Reservation ID: " << reservation.reservationID() << endl;
        cout << "Student ID: " << reservation.studentID() << endl;
        cout << "Resource ID: " << reservation.resourceID() << endl;
        cout << "Date: " << reservation.date() << endl;
        cout << "Time: " << reservation.time() << endl;
        cout << "------------------------" << endl;
        temp.pop();
    }
}