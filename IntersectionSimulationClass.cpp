#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "EventClass.h"
#include "CarClass.h"
#include "random.h"

/*
    Programmer: Leo Lee
    Date: Dec. 6, 2021
    Purpose: This program involves the implementations of the 
    IntersectionSimulationClass methods
*/

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
    cout << "Time: " << currentTime << " " << "Scheduled ";
    if (travelDir == EAST_DIRECTION)
    {
        int nextArriveOccurTime = currentTime + 
                                  getPositiveNormal(
                                    eastArrivalMean,
                                    eastArrivalStdDev
                                  );
        EventClass newEvent(nextArriveOccurTime, EVENT_ARRIVE_EAST);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (travelDir == WEST_DIRECTION)
    {
        int nextArriveOccurTime = currentTime + 
                                  getPositiveNormal(
                                    westArrivalMean,
                                    westArrivalStdDev
                                  );
        EventClass newEvent(nextArriveOccurTime, EVENT_ARRIVE_WEST);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (travelDir == NORTH_DIRECTION)
    {
        int nextArriveOccurTime = currentTime + 
                                  getPositiveNormal(
                                    northArrivalMean,
                                    northArrivalStdDev
                                  );
        EventClass newEvent(nextArriveOccurTime, EVENT_ARRIVE_NORTH);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (travelDir == SOUTH_DIRECTION)
    {
        int nextArriveOccurTime = currentTime + 
                                  getPositiveNormal(
                                    southArrivalMean,
                                    southArrivalStdDev
                                  );
        EventClass newEvent(nextArriveOccurTime, EVENT_ARRIVE_SOUTH);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else
    {
        cout << "The heading direction of the car is unknown" << endl;
    }
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
    int nextEventTime;

    cout << "Time: " << currentTime << " " << "Scheduled ";

    // The color state change base on the spec light change cycle
    if (currentLight == LIGHT_GREEN_EW)
    {
        nextEventTime = currentTime + eastWestGreenTime;
        EventClass newEvent(nextEventTime, EVENT_CHANGE_YELLOW_EW);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (currentLight == LIGHT_YELLOW_EW)
    {
        nextEventTime = currentTime + eastWestYellowTime;
        EventClass newEvent(nextEventTime, EVENT_CHANGE_GREEN_NS);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (currentLight == LIGHT_GREEN_NS)
    {
        nextEventTime = currentTime + northSouthGreenTime;
        EventClass newEvent(nextEventTime, EVENT_CHANGE_YELLOW_NS);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else if (currentLight == LIGHT_YELLOW_NS)
    {
        nextEventTime = currentTime + northSouthYellowTime;
        EventClass newEvent(nextEventTime, EVENT_CHANGE_GREEN_EW);
        eventList.insertValue(newEvent);
        cout << newEvent << endl;
    }
    else
    {
        cout << "Unknown light event!!" << endl;
    }
    
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
    cout << endl;
    EventClass nextEvent;

    if (!eventList.removeFront(nextEvent))
    {
        cout << "Error!!: The eventList is empty" << endl;
        return false;
    }

    int nextEventType = nextEvent.getType();
    int nextEventTime = nextEvent.getTimeOccurs();

    if (nextEventTime > timeToStopSim)
    {
        cout << "Next event occurs AFTER the simulation end time (";
        cout << nextEvent << ")!" << endl;
        return false;
    }


    if (nextEventType == EVENT_ARRIVE_EAST)
    {
        handleEventArriveEast(nextEvent);
    }
    else if (nextEventType == EVENT_ARRIVE_WEST)
    {
        handleEventArriveWest(nextEvent);
    }
    else if (nextEventType == EVENT_ARRIVE_NORTH)
    {
        handleEventArriveNorth(nextEvent);
    }
    else if (nextEventType == EVENT_ARRIVE_SOUTH)
    {
        handleEventArriveSouth(nextEvent);
    }
    else if (nextEventType == EVENT_CHANGE_GREEN_EW)
    {
        handleEventChangeGreenEw(nextEvent);
    }
    else if (nextEventType == EVENT_CHANGE_YELLOW_EW)
    {
        handleEventChangeYellowEw(nextEvent);
    }
    else if (nextEventType == EVENT_CHANGE_GREEN_NS)
    {
        handleEventChangeGreenNs(nextEvent);
    }
    else if (nextEventType == EVENT_CHANGE_YELLOW_NS)
    {
        handleEventChangeYellowNs(nextEvent);
    }
    else
    {
        cout << "The next event unkonown" << endl;
        return false;
    }

    return true;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}

// private methods

void IntersectionSimulationClass::handleEventArriveEast(
     const EventClass& event
     )
{
    cout << "Handling " << event << endl;

    // update the current time base on the event occurs
    currentTime = event.getTimeOccurs();

    CarClass newCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(newCar);
    int queueSize = eastQueue.getNumElems();
    
    // print the car arrive info
    newCar.printArrive();
    cout << " - queue length: " << queueSize << endl;

    // check if need to update the max queue length
    if (queueSize > maxEastQueueLength)
    {
        maxEastQueueLength = queueSize;
    }

    // schedule the next east arrival event
    scheduleArrival(EAST_DIRECTION);

}

void IntersectionSimulationClass::handleEventArriveWest(
     const EventClass& event
     )
{
    cout << "Handling " << event << endl;

    // update the current time base on the event occurs
    currentTime = event.getTimeOccurs();

    CarClass newCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(newCar);
    int queueSize = westQueue.getNumElems();

    // print the car arrive info
    newCar.printArrive();
    cout << " - queue length: " << queueSize << endl;

    // check if need to update the max queue length
    if (queueSize > maxWestQueueLength)
    {
        maxWestQueueLength = queueSize;
    }

    // schedule the next east arrival event
    scheduleArrival(WEST_DIRECTION);
}

void IntersectionSimulationClass::handleEventArriveNorth(
     const EventClass& event
     )
{
    cout << "Handling " << event << endl;

    // update the current time base on the event occurs
    currentTime = event.getTimeOccurs();

    CarClass newCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(newCar);
    int queueSize = northQueue.getNumElems();

    // print the car arrive info
    newCar.printArrive();
    cout << " - queue length: " << queueSize << endl;
    
    // check if need to update the max queue length
    
    if (queueSize > maxNorthQueueLength)
    {
        maxNorthQueueLength = queueSize;
    }

    // schedule the next east arrival event
    scheduleArrival(NORTH_DIRECTION);
}

void IntersectionSimulationClass::handleEventArriveSouth(
     const EventClass& event
     )
{
    cout << "Handling " << event << endl;

    // update the current time base on the event occurs
    currentTime = event.getTimeOccurs();

    CarClass newCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(newCar);
    int queueSize = southQueue.getNumElems();

    // print the car arrive info
    newCar.printArrive();
    cout << " - queue length: " << queueSize << endl;

    // check if need to update the max queue length
    if (queueSize > maxSouthQueueLength)
    {
        maxSouthQueueLength = queueSize;
    }

    // schedule the next east arrival event
    scheduleArrival(SOUTH_DIRECTION);
}

void IntersectionSimulationClass::handleEventChangeYellowEw(
     const EventClass& event
     )
{
    int eastQueueSize = eastQueue.getNumElems();
    int westQueueSize = westQueue.getNumElems();
    int numOfAdvancedEast = 0;
    int numOfAdvancedWest = 0;
    
    cout << "Handling " << event << endl;
    cout << "Advancing cars on east-west green" << endl;

    currentTime = event.getTimeOccurs();
    currentLight = LIGHT_YELLOW_EW;

    // deal with east-bound advancing
    for (int i = 0; i < eastWestGreenTime; i++)
    {
        if (eastQueueSize > 0)
        {
            CarClass advanceCar;
            eastQueue.dequeue(advanceCar);
            eastQueueSize -= 1;
            numOfAdvancedEast += 1;
            advanceCar.printAdvance();
        }
    }

    // deal with west-bound advancing
    for (int i = 0; i < eastWestGreenTime; i++)
    {
        if (westQueueSize > 0)
        {
            CarClass advanceCar;
            westQueue.dequeue(advanceCar);
            westQueueSize -= 1;
            numOfAdvancedWest += 1;
            advanceCar.printAdvance();
        }
    }

    // summary of this event
    cout << "East-bound cars advanced on green: " << numOfAdvancedEast;
    cout << " Remaining queue: " << eastQueueSize << endl;

    cout << "West-bound cars advanced on green: " << numOfAdvancedWest;
    cout << " Remaining queue: " << westQueueSize << endl;

    numTotalAdvancedEast += numOfAdvancedEast;
    numTotalAdvancedWest += numOfAdvancedWest;

    scheduleLightChange();

}

void IntersectionSimulationClass::handleEventChangeGreenNs(
     const EventClass& event
     )
{
    int eastQueueSize = eastQueue.getNumElems();
    int westQueueSize = westQueue.getNumElems();
    int numOfAdvancedEast = 0;
    int numOfAdvancedWest = 0;
    bool isAdvanceEast = true;
    bool isAdvanceWest = true;
    int eastTimeTics = 0;
    int westTimeTics = 0;

    cout << "Handling " << event << endl;
    cout << "Advancing cars on east-west yellow" << endl;

    currentTime = event.getTimeOccurs();
    currentLight = LIGHT_GREEN_NS;

    // deal with east-bound advancing
    while (
        eastTimeTics < eastWestYellowTime && 
        isAdvanceEast
        )
    {
        eastTimeTics += 1;
        if (eastQueueSize > 0)
        {
            int ranNum = getUniform(1, 100);
            if (ranNum <= percentCarsAdvanceOnYellow)
            {
                cout << "  Next east-bound car will advance on yellow" << endl;
                CarClass advanceCar;
                eastQueue.dequeue(advanceCar);
                eastQueueSize -= 1;
                numOfAdvancedEast += 1;
                advanceCar.printAdvance();
            }
            else
            {
                cout << "  Next east-bound car will NOT advance on yellow";
                cout << endl;
                isAdvanceEast = false;
            }
        }
        else
        {
            cout << "  No east-bound cars waiting to advance on yellow";
            cout << endl;
            isAdvanceEast = false;
        }
    }

    // deal with west-bound advancing
    while (
        westTimeTics < eastWestYellowTime &&
        isAdvanceWest
        )
    {
        westTimeTics += 1;
        if (westQueueSize > 0)
        {
            int ranNum = getUniform(1, 100);
            if (ranNum <= percentCarsAdvanceOnYellow)
            {
                cout << "  Next west-bound car will advance on yellow" << endl;
                CarClass advanceCar;
                westQueue.dequeue(advanceCar);
                westQueueSize -= 1;
                numOfAdvancedWest += 1;
                advanceCar.printAdvance();
            }
            else
            {
                cout << "  Next west-bound car will NOT advance on yellow";
                cout << endl;
                isAdvanceWest = false;
            }

        }
        else
        {
            cout << "  No west-bound cars waiting to advance on yellow";
            cout << endl;
            isAdvanceWest = false;
        }
    }

    // summary of this event
    cout << "East-bound cars advanced on yellow: " << numOfAdvancedEast;
    cout << " Remaining queue: " << eastQueueSize << endl;

    cout << "West-bound cars advanced on yellow: " << numOfAdvancedWest;
    cout << " Remaining queue: " << westQueueSize << endl;

    numTotalAdvancedEast += numOfAdvancedEast;
    numTotalAdvancedWest += numOfAdvancedWest;

    scheduleLightChange();
}

void IntersectionSimulationClass::handleEventChangeYellowNs(
     const EventClass& event
     )
{
    int northQueueSize = northQueue.getNumElems();
    int southQueueSize = southQueue.getNumElems();
    int numOfAdvancedNorth = 0;
    int numOfAdvancedSouth = 0;

    cout << "Handling " << event << endl;
    cout << "Advancing cars on north-south green" << endl;

    // update the current time and current light
    currentTime = event.getTimeOccurs();
    currentLight = LIGHT_YELLOW_NS;

    // deal with north-bound advancing
    for (int i = 0; i < northSouthGreenTime; i++)
    {
        if (northQueueSize > 0)
        {
            CarClass advanceCar;
            northQueue.dequeue(advanceCar);
            northQueueSize -= 1;
            numOfAdvancedNorth += 1;
            advanceCar.printAdvance();
        }
    }

    // deal with south-bound advancing
    for (int i = 0; i < northSouthGreenTime; i++)
    {
        if (southQueueSize > 0)
        {
            CarClass advanceCar;
            southQueue.dequeue(advanceCar);
            southQueueSize -= 1;
            numOfAdvancedSouth += 1;
            advanceCar.printAdvance();
        }
    }

    // summary of this event
    cout << "North-bound cars advanced on green: " << numOfAdvancedNorth;
    cout << " Remaining queue: " << northQueueSize << endl;

    cout << "South-bound cars advanced on green: " << numOfAdvancedSouth;
    cout << " Remaining queue: " << southQueueSize << endl;

    // update the statistics of total cars advancing
    numTotalAdvancedNorth += numOfAdvancedNorth;
    numTotalAdvancedSouth += numOfAdvancedSouth;

    // schedule the next light of change
    scheduleLightChange();
}

void IntersectionSimulationClass::handleEventChangeGreenEw(
     const EventClass& event
     )
{
    int northQueueSize = northQueue.getNumElems();
    int southQueueSize = southQueue.getNumElems();
    int numOfAdvancedNorth = 0;
    int numOfAdvancedSouth = 0;
    bool isAdvanceNorth = true;
    bool isAdvanceSouth = true;
    int northTimeTics = 0;
    int southTimeTics = 0;

    cout << "Handling " << event << endl;
    cout << "Advancing cars on north-south yellow" << endl;

    currentTime = event.getTimeOccurs();
    currentLight = LIGHT_GREEN_EW;

    // deal with north-bound advancing
    while (
        northTimeTics < northSouthYellowTime && 
        isAdvanceNorth
        )
    {
        northTimeTics += 1;
        if (northQueueSize > 0)
        {
            int ranNum = getUniform(1, 100);
            if (ranNum <= percentCarsAdvanceOnYellow)
            {
                cout << "  Next north-bound car will advance on yellow";
                cout << endl;
                CarClass advanceCar;
                northQueue.dequeue(advanceCar);
                northQueueSize -= 1;
                numOfAdvancedNorth += 1;
                advanceCar.printAdvance();
            }
            else
            {
                cout << "  Next north-bound car will NOT advance on yellow";
                cout << endl;
                isAdvanceNorth = false;
            }
        }
        else
        {
            cout << "  No north-bound cars waiting to advance on yellow";
            cout << endl;
            isAdvanceNorth = false;
        }
    }

    // deal with south-bound advancing
    while (
        southTimeTics < northSouthYellowTime && 
        isAdvanceSouth
        )
    {
        southTimeTics += 1;
        if (southQueueSize > 0)
        {
            int ranNum = getUniform(1, 100);
            if (ranNum <= percentCarsAdvanceOnYellow)
            {
                cout << "  Next south-bound car will advance on yellow";
                cout << endl;
                CarClass advanceCar;
                southQueue.dequeue(advanceCar);
                southQueueSize -= 1;
                numOfAdvancedSouth += 1;
                advanceCar.printAdvance();
            }

        }
        else
        {
            cout << "  No south-bound cars waiting to advance on yellow";
            cout << endl;
            isAdvanceSouth = false;
        }

    }

    // summary of this event
    cout << "North-bound cars advanced on yellow: " << numOfAdvancedNorth;
    cout << " Remaining queue: " << northQueueSize << endl;

    cout << "South-bound cars advanced on yellow: " << numOfAdvancedSouth;
    cout << " Remaining queue: " << southQueueSize << endl;

    // update the statistics of total cars advancing
    numTotalAdvancedNorth += numOfAdvancedNorth;
    numTotalAdvancedSouth += numOfAdvancedSouth;

    // schedule the next light of change
    scheduleLightChange();
}
