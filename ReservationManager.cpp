#include "ReservationManager.h"
#include "Reservation.h"
#include <iostream>

ReservationManager::ReservationManager(ResourceManager* manager, ReservationList* list)
{
    resourceManager = manager;
    reservationList = list;
}

void ReservationManager::createReservation()
{
   Reservation newReservation;
   
   std::cout << "===== Create Reservation =====" << std::endl;

   std::cout << "Enter Reservation ID: ";
   std::cin >> newReservation.reservationID;

   if (std::cin.fail() || newReservation.reservationID <= 0)
   {
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "Invalid Reservation ID.\n";
    return;
   }

   std::cout <<"Enter Student ID: ";
   std::cin >> newReservation.studentID;

   if (std::cin.fail() || newReservation.studentID <= 0)
   {
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "Invalid Student ID.\n";
    return;
   }

   std::cout <<"Enter Resource ID: ";
   std::cin >> newReservation.resourceID;

   if (!resourceManager->resourceExists(newReservation.resourceID))
   {
    std::cout << "Invalid Resource ID." << std::endl;
    return;
   }

   if (!resourceManager->isAvailable(newReservation.resourceID))
   {
    std::cout << "Resource is not available." << std::endl;
    return;
   }

   std::cout << "Enter Date: ";
   std::cin >> newReservation.date;


   std::cout << "Enter Time: ";
   std::cin >> newReservation.time;

   reservationList->insertReservation(newReservation);

   resourceManager->setAvailability(newReservation.resourceID, false);

   std::cout << "Reservation created successfully." << std::endl;
}