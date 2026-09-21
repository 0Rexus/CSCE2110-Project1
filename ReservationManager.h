#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "ResourceManager.h"
#include "ReservationList.h"

class ReservationManager
{
private:
    ResourceManager* resourceManager;
    ReservationList* reservationList;

public:
    ReservationManager(ResourceManager* manager, ReservationList* list);
    void createReservation();

};

#endif