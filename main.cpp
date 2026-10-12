#include "ResourceManager.h"
#include "ReservationList.h"
#include "WaitingQueue.h"
#include "CancellationHistory.h"
#include "ReservationManager.h"
#include "Reporting.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void printMenu() {
    cout << "\n========== Campus Resource Reservation System ==========\n"
         << " 1. Display all resources\n"
         << " 2. Sort resources by name (Merge Sort)\n"
         << " 3. Create reservation\n"
         << " 4. Cancel reservation\n"
         << " 5. Display active reservations\n"
         << " 6. Add student to waiting list\n"
         << " 7. Process waiting list\n"
         << " 8. Display waiting list\n"
         << " 9. Display cancellation history\n"
         << "10. Restore most recent cancellation\n"
         << "11. Search reservation by ID (Linear Search)\n"
         << "12. Search reservations by Student ID (Linear Search)\n"
         << "13. Search resource by ID (Binary Search)\n"
         << "14. Search resource by Name (Binary Search)\n"
         << "15. Generate system reports\n"
         << " 0. Exit\n"
         << "========================================================\n";
}

int intCheck() {
    int number;

    while (true) {
        if (cin >> number) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        if (cin.eof()) {
            return -1;
        }

        cout << "Invalid input. Enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    ReservationManager reservationManager(&resourceManager, &reservationList, &waitingQueue, &cancellationHistory);
    Reporting reporting;

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
                cout << "\nSorting resources by name using Merge Sort...\n";
                resourceManager.sortResourcesByName();
                cout << "Resources sorted successfully!\n";
                resourceManager.displayResources();
                break;
            }

            case 3: {
                reservationManager.createReservation();
                break;
            }

            case 4: {
                reservationManager.cancelReservation();
                break;
            }

            case 5: {
                cout << "\n===== Active Reservations =====\n";
                reservationList.displayReservations();
                break;
            }

            case 6: {
                reservationManager.addStudentToWaitingList();
                break;
            }

            case 7: {
                reservationManager.processWaitingList();
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
                reservationManager.restoreCancellation();
                break;
            }

            case 11: {
                cout << "\n===== Search Reservation by ID =====\n";
                cout << "Enter Reservation ID: ";
                int targetID = intCheck();

                Reservation found;
                if (reservationList.searchReservationByID(targetID, found)) {
                    cout << "\n[Match Found]\n";
                    cout << "Reservation ID: " << found.reservationID << endl;
                    cout << "Student ID:     " << found.studentID << endl;
                    cout << "Resource ID:    " << found.resourceID << endl;
                    cout << "Date:           " << found.date << endl;
                    cout << "Time:           " << found.time << endl;
                } else {
                    cout << "No reservation found with ID " << targetID << "." << endl;
                }
                break;
            }

            case 12: {
                cout << "\n===== Search Reservations by Student ID =====\n";
                cout << "Enter Student ID: ";
                int targetStudentID = intCheck();

                reservationList.searchReservationsByStudentID(targetStudentID);
                break;
            }

            case 13: {
                cout << "\n===== Search Resource by ID (Binary Search) =====\n";
                cout << "Enter Resource ID (e.g. R105): ";
                string targetID = stringCheck();

                // Sort resources by ID first to satisfy Binary Search precondition
                resourceManager.sortResourcesByID();

                int idx = resourceManager.binarySearchByID(targetID);
                if (idx != -1) {
                    Resource r = resourceManager.getResourceAt(idx);
                    cout << "\n[Match Found via Binary Search at index " << idx << "]\n";
                    cout << "Resource ID:   " << r.getResourceID() << endl;
                    cout << "Resource Name: " << r.getResourceName() << endl;
                    cout << "Type:          " << r.getResourceType() << endl;
                    cout << "Status:        " << (r.getAvailability() ? "Available" : "Unavailable") << endl;
                } else {
                    cout << "Resource ID \"" << targetID << "\" not found." << endl;
                }
                break;
            }

            case 14: {
                cout << "\n===== Search Resource by Name (Binary Search) =====\n";
                cout << "Enter exact Resource Name (e.g. Laptop 01): ";
                string targetName = stringCheck();

                // Sort resources by name first to satisfy Binary Search precondition
                resourceManager.sortResourcesByName();

                int idx = resourceManager.binarySearchByName(targetName);
                if (idx != -1) {
                    Resource r = resourceManager.getResourceAt(idx);
                    cout << "\n[Match Found via Binary Search at index " << idx << "]\n";
                    cout << "Resource ID:   " << r.getResourceID() << endl;
                    cout << "Resource Name: " << r.getResourceName() << endl;
                    cout << "Type:          " << r.getResourceType() << endl;
                    cout << "Status:        " << (r.getAvailability() ? "Available" : "Unavailable") << endl;
                } else {
                    cout << "Resource Name \"" << targetName << "\" not found." << endl;
                }
                break;
            }

            case 15: {
                cout << "\n===== System Reports Menu =====\n";
                cout << "1. Active Reservations Report\n";
                cout << "2. Resource Utilization Report\n";
                cout << "3. Most Requested Resources Report\n";
                cout << "4. Waiting List Statistics Report\n";
                cout << "Select report (1-4): ";
                int rChoice = intCheck();

                if (rChoice == 1) {
                    reporting.displayActiveReservations(reservationList);
                } else if (rChoice == 2) {
                    reporting.displayResourceUtilization(reservationList, resourceManager);
                } else if (rChoice == 3) {
                    reporting.displayMostRequestedResources(reservationList, resourceManager);
                } else if (rChoice == 4) {
                    reporting.displayWaitingListStatistics(waitingQueue);
                } else {
                    cout << "Invalid report choice.\n";
                }
                break;
            }

            case 0: {
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice. Please select an option from 0 to 15." << endl;
                break;
            }
        }

    } while (choice != 0);

    return 0;
}