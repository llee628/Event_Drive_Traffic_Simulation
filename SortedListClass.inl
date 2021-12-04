/*
    Programmer: Leo Lee
    Date: Nov. 12, 2021
    Purpose: This code provides the implementation of the SortedListClass 
    methods
*/

#include <iostream>
#include "SortedListClass.h"
#include "LinkedNodeClass.h"

using namespace std;

///////////// public methods ///////////////
template< class T >
SortedListClass< T >::SortedListClass()
{
    head = NULL;
    tail = NULL;
}

template< class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T >& rhs)
{
    /*
        need to set head and tail to NULL first, because it will not enter the
        default ctor before enter the copy ctor
    */
    head = NULL;
    tail = NULL;
    
    if (rhs.head != NULL && rhs.tail != NULL)
    {
        
        LinkedNodeClass< T >* current = rhs.tail;
        
        while (current != NULL)
        {
            insertValue(current->getValue());
            current = current->getPrev();
        }
        
    }
    
}

template< class T >
SortedListClass< T >::~SortedListClass()
{
    clear();
}

template< class T >
void SortedListClass< T >::clear()
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

template< class T >
void SortedListClass< T >::insertValue(const T& valToInsert)
{
    // deal with the empty list case
    if (head == NULL || tail == NULL)
    {
        LinkedNodeClass< T >* insertNode = new LinkedNodeClass< T >(
                                            NULL, 
                                            valToInsert,
                                            NULL
                                            );
        head = insertNode;
        tail = insertNode;
    }
    else
    {
        LinkedNodeClass< T >* prev = NULL;
        LinkedNodeClass< T >* current = head;

        // find the position that the value should be inserted
        while (current != NULL && current->getValue() <= valToInsert)
        {
            prev = current;
            current = current->getNext();
        }

        // create a insertNode and make it link in the middle of prev and 
        // current
        if (current == head)
        {   // case1: insert at the beginning
            LinkedNodeClass< T >* insertNode = new LinkedNodeClass< T >(
                                                NULL,
                                                valToInsert,
                                                current
                                                );
            insertNode->setBeforeAndAfterPointers();
            head = insertNode;
        }
        else if (current == NULL)
        {   // case2: insert at the end
            LinkedNodeClass< T >* insertNode = new LinkedNodeClass< T >(
                                                prev,
                                                valToInsert,
                                                NULL
                                                );
            insertNode->setBeforeAndAfterPointers();
            tail = insertNode;

        }
        else
        {
            LinkedNodeClass< T >* insertNode = new LinkedNodeClass< T >(
                                                prev,
                                                valToInsert,
                                                current
                                                );
            insertNode->setBeforeAndAfterPointers();
        }

    }
}

template< class T >
void SortedListClass< T >::printForward() const
{
    LinkedNodeClass< T >* current = head;
    
    cout << "Forward List Contents Follow:" << endl;

    while (current != NULL)
    {
        cout << "  " << current->getValue() << endl;
        current = current->getNext();
    }

    cout << "End Of List Contents" << endl;

}

template< class T >
void SortedListClass< T >::printBackward() const
{
    LinkedNodeClass< T >* current = tail;

    cout << "Backward List Contents Follow:" << endl;

    while (current != NULL)
    {
        cout << "  " << current->getValue() << endl;
        current = current->getPrev();
    }

    cout << "End Of List Contents" << endl;
}

template< class T >
bool SortedListClass< T >::removeFront(T& theVal)
{
    if (head == NULL || tail == NULL)
    {
        return false;
    }

    LinkedNodeClass< T >* current = head;
    head = current->getNext();
    
    if (head == NULL)
    {   // the case that remove only one element in the list
        tail = NULL;
    }
    else
    {
        head->setPreviousPointerToNull();
    }
    
    theVal = current->getValue();

    // free the node
    delete current;
    current = NULL;

    return true;
    
}

template< class T >
bool SortedListClass< T >::removeLast(T& theVal)
{
    if (head == NULL || tail == NULL)
    {
        return false;
    }

    LinkedNodeClass< T >* current = tail;
    tail = current->getPrev();

    if (tail == NULL)
    {   // the case that remove only one element in the list
        head = NULL;
    }
    else
    {
        tail->setNextPointerToNull();
    }
    
    theVal = current->getValue();

    // free the node
    delete current;
    current = NULL;

    return true;
}

template< class T >
int SortedListClass< T >::getNumElems() const
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

template< class T >
bool SortedListClass< T >::getElemAtIndex(const int index, T& outVal) const
{
    int numElems = getNumElems();

    // handle the error case
    if (index < 0 || index >= numElems)
    {
        return false;
    }

    LinkedNodeClass< T >* current = head;
    for (int i = 0 ; i < index; i++)
    {
        current = current->getNext();
    }

    outVal = current->getValue();

    return true;
}




