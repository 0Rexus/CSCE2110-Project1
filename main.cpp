#include <iostream>
#include <limits>
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

}

string stringCheck() {

}

int main() {
    int choice;
        
    do {
        printMenu();
    } while (choice != 0);

    return 0;
}