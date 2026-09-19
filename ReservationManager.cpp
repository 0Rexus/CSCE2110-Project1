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
   int reservationID;
   int studentID;
   std::string resourceID;
   std::string date;
   std::string time;
   
   std::cout << "===== Create Reservation =====" << std::endl;

   std::cout << "Enter Reservation ID: ";
   std::cin >> reservationID;

   std::cout <<"Enter Student ID: ";
   std::cin >> studentID;
   
   if (reservationID <= 0 || studentID <= 0)
   {
    std::cout << "Invalid Reservation ID or Student ID." << std::endl;
    return;
   }

   std::cout <<"Enter Resource ID: ";
   std::cin >> resourceID;

   if (!resourceManager->resourceExists(resourceID))
   {
    std::cout << "Invalid Resource ID." << std::endl;
    return;
   }

   std::cout << "ENter Date: ";
   std::cin >> date;


   std::cout << "Enter Time: ";
   std::cin >> time;
   
   Reservation newReservation;

   newReservation.reservationID = reservationID;
   newReservation.studentID = studentID;
   newReservation.resourceID = resourceID;
   newReservation.date = date;
   newReservation.time = time;

   reservationList->insertReservation(newReservation);

   std::cout << "Reservation created successfully." << std::endl;
}

