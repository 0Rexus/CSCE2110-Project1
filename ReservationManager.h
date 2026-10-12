#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "ResourceManager.h"
#include "ReservationList.h"
#include "WaitingQueue.h"
#include "CancellationHistory.h"
#include <string>

class ReservationManager
{
private:
    ResourceManager* resourceManager;
    ReservationList* reservationList;
    WaitingQueue* waitingQueue;
    CancellationHistory* cancellationHistory;

    bool isValidDate(const std::string& date) const;
    bool isValidTime(const std::string& time) const;
    bool isDoubleBooked(const std::string& resourceID, const std::string& date, const std::string& time) const;

public:
    ReservationManager(ResourceManager* manager, ReservationList* list,
                       WaitingQueue* queue, CancellationHistory* history);

    void createReservation();
    void cancelReservation();
    void restoreCancellation();
    void addStudentToWaitingList();
    void processWaitingList();
};

#endif