#include "ReservationManager.h"
#include <iostream>
#include <limits>

using namespace std;

static int getValidInt() {
    int num;
    while (true) {
        if (cin >> num) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num;
        }
        if (cin.eof()) return -1;
        cout << "Invalid number. Enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static string getValidLine() {
    string str;
    getline(cin, str);
    return str;
}

ReservationManager::ReservationManager(ResourceManager* manager, ReservationList* list,
                                       WaitingQueue* queue, CancellationHistory* history) {
    resourceManager = manager;
    reservationList = list;
    waitingQueue = queue;
    cancellationHistory = history;
}

bool ReservationManager::isValidDate(const string& date) const {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    return true;
}

bool ReservationManager::isValidTime(const string& time) const {
    if (time.length() < 4) return false;
    if (time.find(':') == string::npos) return false;
    return true;
}

bool ReservationManager::isDoubleBooked(const string& resourceID, const string& date, const string& time) const {
    const Node* current = reservationList->getHead();
    while (current != nullptr) {
        if (current->data.resourceID == resourceID &&
            current->data.date == date &&
            current->data.time == time) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void ReservationManager::createReservation() {
    Reservation newRes;
    cout << "\n===== Create Reservation =====\n";

    cout << "Enter Reservation ID: ";
    newRes.reservationID = getValidInt();
    if (newRes.reservationID <= 0) {
        cout << "Error: Reservation ID must be a positive integer.\n";
        return;
    }

    Reservation existing;
    if (reservationList->searchReservationByID(newRes.reservationID, existing)) {
        cout << "Error: Reservation ID " << newRes.reservationID << " already exists! Duplicate rejected.\n";
        return;
    }

    cout << "Enter Student ID: ";
    newRes.studentID = getValidInt();
    if (newRes.studentID <= 0) {
        cout << "Error: Student ID must be a positive integer.\n";
        return;
    }

    cout << "Enter Resource ID: ";
    newRes.resourceID = getValidLine();

    if (!resourceManager->resourceExists(newRes.resourceID)) {
        cout << "Error: Resource \"" << newRes.resourceID << "\" does not exist.\n";
        return;
    }

    if (!resourceManager->isAvailable(newRes.resourceID)) {
        cout << "Error: Resource \"" << newRes.resourceID << "\" is currently UNAVAILABLE.\n";
        cout << "Would you like to add Student " << newRes.studentID 
             << " to the waiting list for this resource? (y/n): ";
        char ans;
        cin >> ans;
        cin.ignore(1000, '\n');
        if (ans == 'y' || ans == 'Y') {
            waitingQueue->addStudent(newRes.studentID, newRes.resourceID);
            cout << "Student " << newRes.studentID << " added to waiting list for " << newRes.resourceID << ".\n";
        }
        return;
    }

    cout << "Enter Date (YYYY-MM-DD): ";
    newRes.date = getValidLine();
    if (!isValidDate(newRes.date)) {
        cout << "Error: Invalid date format. Please use YYYY-MM-DD (e.g. 2026-10-15).\n";
        return;
    }

    cout << "Enter Time (e.g. 10:00 AM): ";
    newRes.time = getValidLine();
    if (!isValidTime(newRes.time)) {
        cout << "Error: Invalid time format. Please include minutes (e.g. 10:00 AM).\n";
        return;
    }

    if (isDoubleBooked(newRes.resourceID, newRes.date, newRes.time)) {
        cout << "Error: Double booking collision! Resource " << newRes.resourceID 
             << " is already booked on " << newRes.date << " at " << newRes.time << ".\n";
        return;
    }

    reservationList->insertReservation(newRes);
    resourceManager->setAvailability(newRes.resourceID, false);
    cout << "Reservation #" << newRes.reservationID << " created successfully!\n";
    cout << "Resource " << newRes.resourceID << " is now marked UNAVAILABLE.\n";
}

void ReservationManager::cancelReservation() {
    cout << "\n===== Cancel Reservation =====\n";
    cout << "Enter Reservation ID to cancel: ";
    int reservationID = getValidInt();

    Reservation cancelled;
    if (reservationList->removeReservation(reservationID, cancelled)) {
        cancellationHistory->addCancelledReservation(cancelled);
        cout << "Reservation #" << reservationID << " cancelled and saved to cancellation stack.\n";

        if (waitingQueue->hasStudentWaitingFor(cancelled.resourceID)) {
            int waitingStudentID;
            cout << "\n>>> WAITING LIST ALERT: A student is waiting for resource " 
                 << cancelled.resourceID << "!\n";
            cout << "Assign this newly freed slot to the next waiting student? (y/n): ";
            char ans;
            cin >> ans;
            cin.ignore(1000, '\n');
            if (ans == 'y' || ans == 'Y') {
                waitingQueue->popNextStudentForResource(cancelled.resourceID, waitingStudentID);
                Reservation waitRes = cancelled;
                waitRes.studentID = waitingStudentID;
                reservationList->insertReservation(waitRes);
                cout << "Success: Slot immediately reassigned to waiting Student " << waitingStudentID << "!\n";
                return;
            }
        }

        resourceManager->setAvailability(cancelled.resourceID, true);
        cout << "Resource " << cancelled.resourceID << " is now available again.\n";
    } else {
        cout << "Error: Reservation #" << reservationID << " not found in active list.\n";
    }
}

void ReservationManager::restoreCancellation() {
    cout << "\n===== Restore Most Recent Cancellation =====\n";
    Reservation restored;

    if (!cancellationHistory->restoreLastCancellation(restored)) {
        cout << "No cancellations in history to restore.\n";
        return;
    }

    Reservation existing;
    if (reservationList->searchReservationByID(restored.reservationID, existing)) {
        cout << "Error: Cannot restore! Reservation ID " << restored.reservationID 
             << " is currently in active use by Student " << existing.studentID << ".\n";
        cancellationHistory->addCancelledReservation(restored);
        return;
    }

    if (isDoubleBooked(restored.resourceID, restored.date, restored.time)) {
        cout << "Error: Cannot restore! Resource " << restored.resourceID 
             << " has since been booked by someone else on " << restored.date << " at " << restored.time << ".\n";
        cancellationHistory->addCancelledReservation(restored);
        return;
    }

    reservationList->insertReservation(restored);
    resourceManager->setAvailability(restored.resourceID, false);
    cout << "Restored Reservation #" << restored.reservationID << " for Student " 
         << restored.studentID << " on resource " << restored.resourceID << ".\n";
}

void ReservationManager::addStudentToWaitingList() {
    cout << "\n===== Add Student to Waiting List =====\n";
    cout << "Enter Student ID: ";
    int studentID = getValidInt();
    if (studentID <= 0) {
        cout << "Error: Student ID must be positive.\n";
        return;
    }

    cout << "Enter Resource ID requested: ";
    string resID = getValidLine();
    if (!resourceManager->resourceExists(resID)) {
        cout << "Error: Resource \"" << resID << "\" does not exist.\n";
        return;
    }

    waitingQueue->addStudent(studentID, resID);
    cout << "Student " << studentID << " added to waiting list for resource " << resID << " successfully!\n";
}

void ReservationManager::processWaitingList() {
    cout << "\n===== Process Waiting List =====\n";
    int studentID;
    string resourceID;
    if (waitingQueue->removeStudent(studentID, resourceID)) {
        cout << "Processed Student ID: " << studentID 
             << " (Waiting for resource: " << resourceID << ").\n";
        cout << "Student removed from front of waiting list.\n";
    } else {
        cout << "Waiting list is empty.\n";
    }
}