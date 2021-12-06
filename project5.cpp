#include <iostream>
#include <string>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"

//Programmer: Andrew Morgan
//Date: November 2020
//Purpose: High-level main function to setup a simulation of traffic
//         flow through an intersection.  This is being written to
//         implement project 5 in EECS402.
int main(
     int argc,
     char *argv[]
     )
{
  bool success = true;
  string specifiedParamFname;
  IntersectionSimulationClass simObj;

  //Check that user specified the necessary command line arg(s)..
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <parameterFile>" << endl;
    success = false;
  }
  else
  {
    specifiedParamFname = string(argv[1]);
  }

  if (success)
  {
    //Read input parameters and print to screen for reference..
    cout << "Reading parameters from file: " << specifiedParamFname << endl;
    simObj.readParametersFromFile(specifiedParamFname);
    simObj.printParameters();

    if (!simObj.getIsSetupProperly())
    {
      cout << "Cannot run simulation as it is not setup properly!" << endl;
      success = false;
    }
  }

  if (success)
  {
    //Schedule the initial events that will "seed" the event-driven simulation
    cout << endl;
    cout << "Schedule simulation seed events" << endl;
    simObj.scheduleSeedEvents();

    //When the simulation recognizes it should stop handling events,
    //the call to "handleNextEvent" will return false.  This is
    //expected to occur when the next event's schedule time is 
    //after the end time of the simulation (an input parameter).
    cout << endl;
    cout << "Starting simulation!" << endl;

    bool doKeepRunning = true;
    while (doKeepRunning)
    {
      //Handle the next scheduled event now..
      doKeepRunning = simObj.handleNextEvent();
    }
  }

  //Indicate whether things went well or not, and, if so, print out the
  //simualtion statistics that were computed during the run.
  if (success)
  {
    cout << "Simulation ran successfully!" << endl;
    simObj.printStatistics();
  }
  else
  {
    cout << "Simulation did NOT run successfully..." << endl;
  }

  return 0;
}


/*
  Phase 1 test main
*/

// int main()
// {
//     //This is just a placeholder main function - it does exceptionally
//     //little actual testing, so you'll want to add your own tests here.
//     //Feel free to leave your tests in the version of this file you
//     //submit, but we will not be running your main function, so the
//     //output, etc., of your main doesn't need to match anything from
//     //a sample output, etc.
    
//     ///////////// Test the SortedList ////////////
    
//     // SortedListClass< int > testList;
//     // int outVal;
    
//     // testList.printForward();
//     // cout << endl;

//     // testList.removeFront(outVal);
//     // cout << "test remove Front at empty list: " << outVal << endl;

//     // testList.removeLast(outVal);
//     // cout << "test remove last at empty list: " << outVal << endl;
    
//     // testList.insertValue(42);
//     // testList.insertValue(-5);
//     // testList.insertValue(32);
//     // testList.insertValue(98);
//     // testList.insertValue(74);
//     // testList.insertValue(23);
//     // testList.insertValue(0);
    
//     // testList.printForward();
//     // cout << endl;
//     // testList.printBackward();
//     // cout << endl;

//     // cout << "number of elements: " << testList.getNumElems() << endl;
    
    
//     // testList.getElemAtIndex(20, outVal);
//     // cout << "element at index 20: " << outVal << endl;

//     // testList.getElemAtIndex(3, outVal);
//     // cout << "element at index 3: " << outVal << endl;

//     // cout << "Test remove forward and backward: " << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.printForward();

//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.printForward();

//     // cout << endl;
//     // cout << "Test the deep copy" << endl;

//     // SortedListClass< int > testListCopy = testList;
    
//     // testList.removeFront(outVal);
//     // testList.removeLast(outVal);

//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;

//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << endl;
//     // cout << "test the clear method in SortedListClass" << endl;
//     // testList.clear();
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();
    
//     // testList.insertValue(20);
//     // testList.insertValue(40);
//     // testList.insertValue(30);
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << "Test the remove front until empty" << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();

//     // cout << "Test the remove last until empty" << endl;
//     // testList.insertValue(20);
//     // testList.insertValue(40);
//     // testList.insertValue(30);
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
    
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();


//     // test the double type of SortedListClass
//     // SortedListClass< double > testList;
//     // double outVal;
    
//     // testList.printForward();
//     // cout << endl;

//     // testList.removeFront(outVal);
//     // cout << "test remove Front at empty list: " << outVal << endl;

//     // testList.removeLast(outVal);
//     // cout << "test remove last at empty list: " << outVal << endl;
    
//     // testList.insertValue(42.2);
//     // testList.insertValue(-5.2);
//     // testList.insertValue(32.1);
//     // testList.insertValue(98.9);
//     // testList.insertValue(74.3);
//     // testList.insertValue(23.1);
//     // testList.insertValue(0.0);
    
//     // testList.printForward();
//     // cout << endl;
//     // testList.printBackward();
//     // cout << endl;

//     // cout << "number of elements: " << testList.getNumElems() << endl;
    
    
//     // testList.getElemAtIndex(20, outVal);
//     // cout << "element at index 20: " << outVal << endl;

//     // testList.getElemAtIndex(3, outVal);
//     // cout << "element at index 3: " << outVal << endl;

//     // cout << "Test remove forward and backward: " << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.printForward();

//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.printForward();

//     // cout << endl;
//     // cout << "Test the deep copy" << endl;

//     // SortedListClass< double > testListCopy = testList;
    
//     // testList.removeFront(outVal);
//     // testList.removeLast(outVal);

//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;

//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << endl;
//     // cout << "test the clear method in SortedListClass" << endl;
//     // testList.clear();
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();
    
//     // testList.insertValue(20.1);
//     // testList.insertValue(40.2);
//     // testList.insertValue(30.3);
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << "Test the remove front until empty" << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();

//     // cout << "Test the remove last until empty" << endl;
//     // testList.insertValue(20.1);
//     // testList.insertValue(40.2);
//     // testList.insertValue(30.3);
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
    
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();

//     // test the char type of SortedListClass
//     // SortedListClass< char > testList;
//     // char outVal;
    
//     // testList.printForward();
//     // cout << endl;

//     // testList.removeFront(outVal);
//     // cout << "test remove Front at empty list: " << outVal << endl;

//     // testList.removeLast(outVal);
//     // cout << "test remove last at empty list: " << outVal << endl;
    
//     // testList.insertValue('a');
//     // testList.insertValue('c');
//     // testList.insertValue('L');
//     // testList.insertValue('e');
//     // testList.insertValue('o');
//     // testList.insertValue('6');
//     // testList.insertValue('6');
    
//     // testList.printForward();
//     // cout << endl;
//     // testList.printBackward();
//     // cout << endl;

//     // cout << "number of elements: " << testList.getNumElems() << endl;
    
    
//     // testList.getElemAtIndex(20, outVal);
//     // cout << "element at index 20: " << outVal << endl;

//     // testList.getElemAtIndex(3, outVal);
//     // cout << "element at index 3: " << outVal << endl;

//     // cout << "Test remove forward and backward: " << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.printForward();

//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.printForward();

//     // cout << endl;
//     // cout << "Test the deep copy" << endl;

//     // SortedListClass< char > testListCopy = testList;
    
//     // testList.removeFront(outVal);
//     // testList.removeLast(outVal);

//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;

//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << endl;
//     // cout << "test the clear method in SortedListClass" << endl;
//     // testList.clear();
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();
    
//     // testList.insertValue('L');
//     // testList.insertValue('e');
//     // testList.insertValue('o');
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
//     // cout << endl;
//     // cout << "contents in testListCopy:" << endl;
//     // testListCopy.printForward();

//     // cout << "Test the remove front until empty" << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // testList.removeFront(outVal);
//     // cout << "value that remove from front: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();

//     // cout << "Test the remove last until empty" << endl;
//     // testList.insertValue('L');
//     // testList.insertValue('e');
//     // testList.insertValue('o');
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();
    
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // testList.removeLast(outVal);
//     // cout << "value that remove from last: " << outVal << endl;
//     // cout << "contents in testList:" << endl;
//     // testList.printForward();


//     ///////////////////    end of test the SortedList    /////////////

//     //////////////////    Test the FIFO Quese    /////////////////////
//     cout << endl << endl;
//     // FIFOQueueClass< int > testQueue;
//     // int outItem;

//     // cout << "--------------- Test the empty queue --------------" << endl;
//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();

//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;
    
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "--------- Test the enqueue, dequeue, and clear ---------" << endl;
//     // testQueue.enqueue(0);
//     // testQueue.enqueue(9);
//     // testQueue.enqueue(5);
//     // testQueue.enqueue(2);
//     // testQueue.enqueue(7);
//     // testQueue.enqueue(123);
//     // testQueue.enqueue(123);

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;

//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;

//     // testQueue.clear();
//     // cout << "Contents in the queue after clear: " << endl;
//     // testQueue.print();

//     // cout << "Test the enque after clear and deque for a single element";
//     // cout << endl;
//     // testQueue.enqueue(5);
//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();

//     // test the double version of Queue
//     // FIFOQueueClass< double > testQueue;
//     // double outItem;

//     // cout << "--------------- Test the empty queue --------------" << endl;
//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();

//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;
    
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "--------- Test the enqueue, dequeue, and clear ---------" << endl;
//     // testQueue.enqueue(0.0);
//     // testQueue.enqueue(9.2);
//     // testQueue.enqueue(5.5);
//     // testQueue.enqueue(2.1);
//     // testQueue.enqueue(7.7);
//     // testQueue.enqueue(123.2);
//     // testQueue.enqueue(123.4);

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;

//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     // cout << endl;

//     // testQueue.clear();
//     // cout << "Contents in the queue after clear: " << endl;
//     // testQueue.print();

//     // cout << "Test the enque after clear and deque for a single element";
//     // cout << endl;
//     // testQueue.enqueue(5.1);
//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;
//     // testQueue.dequeue(outItem);
//     // cout << "The item that be removed: " << outItem << endl;

//     // cout << "Contents in the queue: " << endl;
//     // testQueue.print();


//     // test the char version of Queue
//     FIFOQueueClass< char > testQueue;
//     char outItem;

//     cout << "--------------- Test the empty queue --------------" << endl;
//     cout << "Contents in the queue: " << endl;
//     testQueue.print();

//     cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     cout << endl;
    
//     testQueue.dequeue(outItem);
//     cout << "The item that be removed: " << outItem << endl;

//     cout << "--------- Test the enqueue, dequeue, and clear ---------" << endl;
//     testQueue.enqueue('L');
//     testQueue.enqueue('e');
//     testQueue.enqueue('o');
//     testQueue.enqueue('2');
//     testQueue.enqueue('0');
//     testQueue.enqueue('2');
//     testQueue.enqueue('0');

//     cout << "Contents in the queue: " << endl;
//     testQueue.print();
//     cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     cout << endl;

//     testQueue.dequeue(outItem);
//     cout << "The item that be removed: " << outItem << endl;
//     testQueue.dequeue(outItem);
//     cout << "The item that be removed: " << outItem << endl;

//     cout << "Contents in the queue: " << endl;
//     testQueue.print();
//     cout << "nums of elements in the queue: " << testQueue.getNumElems();
//     cout << endl;

//     testQueue.clear();
//     cout << "Contents in the queue after clear: " << endl;
//     testQueue.print();

//     cout << "Test the enque after clear and deque for a single element";
//     cout << endl;
//     testQueue.enqueue('L');
//     cout << "Contents in the queue: " << endl;
//     testQueue.print();
//     testQueue.dequeue(outItem);
//     cout << "The item that be removed: " << outItem << endl;
//     testQueue.dequeue(outItem);
//     cout << "The item that be removed: " << outItem << endl;

//     cout << "Contents in the queue: " << endl;
//     testQueue.print();



//     cout << "------------- end of the queue test --------------------" << endl;
//     return 0;
// }
