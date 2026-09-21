#include "ResourceManager.h"
#include "ReservationList.h"
#include "WaitingQueue.h"
#include "CancellationHistory.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

void printMenu() {
    cout << "\n========== Campus Resource Reservation System ==========\n"
         << "1. Display all resources\n"
         << "2. Display resource availability\n"
         << "3. Create reservation\n"
         << "4. Cancel reservation\n"
         << "5. Display active reservations\n"
         << "6. Add student to waiting list\n"
         << "7. Process waiting list\n"
         << "8. Display waiting list\n"
         << "9. Display cancellation history\n"
         << "10. Restore most recent cancellation\n"
         << "0. Exit\n"
         << "========================================================\n";
}

int intCheck() {
    int number;

    while (true) {
        cin >> number;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}

string stringCheck() {
    string input;
    getline(cin, input);
    return input;
}

int main() {
    ResourceManager resourceManager;
    ReservationList reservationList;
    WaitingQueue waitingQueue;
    CancellationHistory cancellationHistory;

    resourceManager.loadResources("resources.txt");

    int choice = -1;
        
    do {
        printMenu();

        cout << "Enter your choice: ";
        choice = intCheck();

        switch (choice) {
            case 1: {
                resourceManager.displayResources();
                break;
            }
            case 2: {
                resourceManager.displayResources();
                break;
            }
            case 3: {
                Reservation reservation;

                cout << "\n===== Create Reservation =====\n";

                cout << "Enter Reservation ID: ";
                reservation.reservationID = intCheck();

                if (reservation.reservationID <= 0) {
                    cout << "Invalid Reservation ID." << endl;
                    break;
                }

                cout << "Enter Student ID: ";
                reservation.studentID = intCheck();

                if (reservation.studentID <= 0) {
                    cout << "Invalid Student ID." << endl;
                    break;
                }

                cout << "Enter Resource ID: ";
                reservation.resourceID = stringCheck();

                if (!resourceManager.resourceExists(reservation.resourceID)) {
                    cout << "Resource does not exist." << endl;
                    break;
                }

                cout << "Enter Date: ";
                reservation.date = stringCheck();

                cout << "Enter Time: ";
                reservation.time = stringCheck();

                reservationList.insertReservation(reservation);

                cout << "Reservation created successfully." << endl;

                break;
            }

            case 4: {
                cout << "\n===== Cancel Reservation =====\n";

                cout << "Enter Reservation ID to cancel: ";
                int reservationID = intCheck();

                Reservation cancelledReservation;

                if (reservationList.removeReservation(reservationID, cancelledReservation)) {
                    cancellationHistory.addCancelledReservation(cancelledReservation);
                    cout << "Reservation cancelled successfully." << endl;
                    cout << "Reservation added to cancellation history." << endl;
                } else {
                    cout << "Reservation not found." << endl;
                }

                break;
            }

            case 5: {
                cout << "\n===== Active Reservations =====\n";
                reservationList.displayReservations();
                break;
            }

            case 6: {
                cout << "\n===== Add Student to Waiting List =====\n";

                cout << "Enter Student ID: ";
                int studentID = intCheck();

                if (studentID <= 0) {
                    cout << "Invalid Student ID." << endl;
                    break;
                }

                waitingQueue.addStudent(studentID);

                cout << "Added student to waiting list" << endl;

                break;
            }

            case 7: {
                cout << "\n===== Process Waiting List =====\n";

                int studentID;
                if (waitingQueue.removeStudent(studentID)) {
                    cout << "Processed student with ID: " << studentID << endl;
                    cout << "Student has been removed from the waiting list." << endl;
                } else {
                    cout << "Waiting list is empty." << endl;
                }

                break;
            }

            case 8: {
                cout << "\n===== Waiting List =====\n";
                waitingQueue.displayWaitingList();
                break;
            }

            case 9: {
                cout << "\n===== Cancellation History =====\n";
                cancellationHistory.displayHistory();
                break;
            }

            case 10: {
                cout << "\n===== Restore Cancellation =====\n";

                Reservation restored;

                if (cancellationHistory.restoreLastCancellation(restored)) {
                    reservationList.insertReservation(restored);
                    cout << "Restored reservation with ID: " << restored.reservationID << endl;
                } else {
                    cout << "No cancellations to restore." << endl;
                }

                break;
            }

            case 0: {
                cout << "Exiting the program." << endl;
                break;
            }

            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}