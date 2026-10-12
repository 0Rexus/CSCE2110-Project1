#include "Reporting.h"
#include "ReservationList.h"
#include "ResourceManager.h"
#include "WaitingQueue.h"

#include <iostream>
#include <iomanip>
using namespace std;
void Reporting::displayActiveReservations(
    const ReservationList& reservations)
{
    cout << "\n====================================\n";
    cout << "       ACTIVE RESERVATIONS REPORT\n";
    cout << "====================================\n";

    reservations.displayReservations();

    cout << "====================================\n";
}
void Reporting::displayResourceUtilization(
    const ReservationList& reservations,
    const ResourceManager& resources)
{
    cout << "\n====================================\n";
    cout << "      RESOURCE UTILIZATION REPORT\n";
    cout << "====================================\n";

    cout << left << setw(25) << "Resource"
         << "Reservations\n";
    cout << "----------------------------------------\n";

    const auto& allResources = resources.getResources();

    for (const auto& resource : allResources)
    {
        int count = 0;

        const Node* current = reservations.getHead();

        while (current != nullptr)
        {
            if (current->data.resourceID ==
                resource.getResourceID())
            {
                count++;
            }

            current = current->next;
        }

        cout << left << setw(25)
             << resource.getResourceName()
             << count << endl;
    }

    cout << "====================================\n";
}

void Reporting::displayMostRequestedResources(
    const ReservationList& reservations,
    const ResourceManager& resources)
{
    cout << "\n====================================\n";
    cout << "     MOST REQUESTED RESOURCES REPORT\n";
    cout << "====================================\n";

    const auto& allResources = resources.getResources();

    for (const auto& resource : allResources)
    {
        int count = 0;

        const Node* current = reservations.getHead();

        while (current != nullptr)
        {
            if (current->data.resourceID ==
                resource.getResourceID())
            {
                count++;
            }

            current = current->next;
        }

        cout << left << setw(25)
             << resource.getResourceName()
             << "Requests: " << count << endl;
    }

    cout << "====================================\n";
}

void Reporting::displayWaitingListStatistics(
    const WaitingQueue& waitingQueue)
{
    cout << "\n====================================\n";
    cout << "     WAITING LIST STATISTICS REPORT\n";
    cout << "====================================\n";

    cout << "Total Students Currently Waiting: " << waitingQueue.getWaitingCount() << endl;
    cout << "------------------------------------------------\n";
    waitingQueue.displayWaitingList();
    cout << "====================================\n";
}