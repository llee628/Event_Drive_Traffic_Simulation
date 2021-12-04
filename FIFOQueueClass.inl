/*
    Programmer: Leo Lee
    Date: Dec. 4, 2021
    Purpose: This code provides the implementation of the self-implemented FIFO
    queue.
*/

#include <iostream>
#include "FIFOQueueClass.h"
#include "LinkedNodeClass.h"

using namespace std;

// public methods

template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
    head = NULL;
    tail = NULL;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
    clear();
}

template < class T >
void FIFOQueueClass< T >::enqueue(const T& newItem)
{
    LinkedNodeClass< T >* current = tail;
    LinkedNodeClass< T >* insertNode = new LinkedNodeClass< T >(
                                        current,
                                        newItem,
                                        NULL
                                        );
    
    if (head == NULL || tail == NULL)
    {   // deal with the empty queue case
        head = insertNode;
        tail = insertNode;
    }
    else
    {
        insertNode->setBeforeAndAfterPointers();
        tail = insertNode;
    }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T& outItem)
{
    if (head == NULL || tail == NULL)
    {
        return false;
    }

    LinkedNodeClass< T >* current = head;
    head = current->getNext();

    if (head == NULL)
    {   // the case that remove only one element in the queue
        tail = NULL;
    }
    else
    {
        head->setPreviousPointerToNull();
    }

    outItem = current->getValue();

    // free the node
    delete current;
    current = NULL;

    return true;
}

template < class T >
void FIFOQueueClass< T >::print() const
{
    LinkedNodeClass< T >* current = head;
    while (current != NULL)
    {
        cout << current->getValue() << " ";
        current = current->getNext();
    }

    cout << endl;
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const
{
    int numElems = 0;
    LinkedNodeClass< T >* current = head;

    while (current != NULL)
    {
        numElems += 1;
        current = current->getNext();
    }

    return numElems;
}

template < class T >
void FIFOQueueClass< T >::clear()
{
    LinkedNodeClass< T >* current = head;
    LinkedNodeClass< T >* prev = NULL;

    while (current != NULL)
    {
        delete prev;
        prev = current;
        current = current->getNext();
    }

    // now, current is NULL and prev is at the last node
    delete prev; // free the last node space

    head = NULL;
    tail = NULL;
}


