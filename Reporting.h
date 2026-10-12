#ifndef REPORTING_H
#define REPORTING_H

class ReservationList;
class ResourceManager;
class WaitingQueue;

class Reporting {
public:
    void displayActiveReservations(
        const ReservationList& reservations);

    void displayResourceUtilization(
        const ReservationList& reservations,
        const ResourceManager& resources);

    void displayMostRequestedResources(
        const ReservationList& reservations,
        const ResourceManager& resources);

    void displayWaitingListStatistics(
        const WaitingQueue& waitingQueue);
};

#endif