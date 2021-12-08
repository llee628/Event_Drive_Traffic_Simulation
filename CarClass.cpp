#include "CarClass.h"
#include "constants.h"

#include <iostream>
using namespace std;

/*
    Prgrammer: Leo Lee
    Date: Dec. 8, 2021
    Purpose: This programmer invloves the implementation of CarClass methods
*/

//Assign the static attribute used for auto-assigning unique ids
int CarClass::nextIdVal = 0;

ostream& operator<<(
     ostream& outStream,
     const CarClass &carToPrint
     )
{
  outStream << "Car id: " << carToPrint.uniqueId <<
               " traveling: " << carToPrint.travelDir <<
               " arrived: " << carToPrint.arrivalTime;

  return outStream;
}

// public methods
void CarClass::printArrive() const
{
    cout << "Time: " << arrivalTime << " Car #" << uniqueId << " arrives ";

    if (travelDir == EAST_DIRECTION)
    {
        cout << "east-bound";
    }
    else if (travelDir == WEST_DIRECTION)
    {
        cout << "west-bound";
    }
    else if (travelDir == NORTH_DIRECTION)
    {
        cout << "north-bound";
    }
    else if (travelDir == SOUTH_DIRECTION)
    {
        cout << "south-bound";
    }
    else
    {
        cout << "unknown direction bound" << endl;
    }
}

void CarClass::printAdvance() const
{
    cout << "  Car #" << uniqueId << " advances ";
    
    if (travelDir == EAST_DIRECTION)
    {
        cout << "east-bound";
    }
    else if (travelDir == WEST_DIRECTION)
    {
        cout << "west-bound";
    }
    else if (travelDir == NORTH_DIRECTION)
    {
        cout << "north-bound";
    }
    else if (travelDir == SOUTH_DIRECTION)
    {
        cout << "south-bound";
    }
    else
    {
        cout << "unknown direction bound";
    }

    cout << endl;
}

