/**********************************************************************************************
FILE NAME: DynListClass.cpp
AUTHOR: Megan Walsh
DATE: December 17, 2012
PURPOSE: This file contains the definition of methods contained in DynListClass.h
**********************************************************************************************/

#include "DynListClass.h"  //Header file 

/*********************************************************************************************/
DynListClass::DynListClass() 
    {
    // Set pointers to default values
    head = NULL;
    currPos = head; 
    }// end DynListClass Construct.
/*********************************************************************************************/
DynListClass::~DynListClass() 
    {
    Clear(); //Clear list
    delete head;
    delete currPos;
    }// end DynListClass Destruct.
/*********************************************************************************************/
DynListClass::DynListClass(/*in*/const DynListClass& orig) 
    {
    //Set pointers to default values
    head = NULL;
    currPos=head;

    //Copy values of orig into class object
    operator=(orig);
    }// end DynListClass Copy Construct.
/*********************************************************************************************/
bool DynListClass::IsEmpty() const
    {
    //If the head points to the tail --return true list is empty
    if(head == NULL)
        return true;

    //Else the head does point to an object --return false
    else
        return false;
    }// end IsEmpty
/*********************************************************************************************/
bool DynListClass::IsFull() const
    {
    return false; // List will expand
    }// end IsFull
/*********************************************************************************************/
void DynListClass::FirstPosition()
    {
    currPos = head; //Set currPos to address of head
    }// end FirstPositions
/*********************************************************************************************/
void DynListClass::NextPosition()
    {
    //If the currPos is not at the end of the list
    if(!EndOfList())
        currPos = currPos->next; //Set currPos to the address of next element

    //Else throw an error as to prevent silly use of the NextPositition
    else
        throw CurrentPositionNotInListException();
    }//end NextPosition
/*********************************************************************************************/
void DynListClass::LastPosition()
    {
    while(currPos->next != NULL)
        currPos = currPos->next;
    }//end NextPosition
/*********************************************************************************************/
bool DynListClass::BeginningOfList() const
    {
    //If currPos is equal to the head --return true
    if(currPos == head)
        return true;

    //If currPos is not equal to the head -- return false
    else
        return false;
    }// end BeginningOfList
/*********************************************************************************************/
bool DynListClass::EndOfList() const
    {
    //If currPos is equal to the tail --return true
    if(currPos== NULL)
        return true;

    //If currPos is not equal to the tail -- return false
    else
        return false;
    }// end EndOfList
/*********************************************************************************************/
string DynListClass::Retrieve() const
    {
    if(currPos != NULL)
        return (currPos -> attribute); // Return the attribute currPos points to
    }// end Retrieve
/*********************************************************************************************/
void DynListClass::Insert(/*in*/string item) //itemType record to insert
    {
    node1* newNode = new node1;   // Node to insert into the list
    newNode->attribute = item;       // Assign the input attribute 

    // If new node1 is the first to be inserted
    if(IsEmpty())
        {
        head =  newNode;      // Assign head to the new node1
        newNode->next = NULL; // Null terminate the newNodes next pointer
        currPos = newNode;    // Assign the currPos to the newNode
        }//end if
    else
        {
        LastPosition();                // Move to the end of the list
        currPos->next = newNode;       // Insert the node1 into the last position 
        currPos->next->next = NULL;    // Null terminate the list
        }// end else
    }// end Insert
/*********************************************************************************************/
void DynListClass::Clear()
    {
    node1* temp;  //Holds node1 to delete

    // If the list is not empty
    if(!IsEmpty())
        {
        FirstPosition(); // set currPos to first item in list

        //while loop --iterate through and clear all node1s in list
        while(!EndOfList())
            {
            temp = currPos; //assign temp the node1 to delete
            NextPosition(); // Assign currPos to the next node1
            delete temp;    //delete temp
            }// end while
        }// end if

    // Set pointers to default values
    head = NULL;
    currPos = head; 
    }// end Class
/*********************************************************************************************/
void DynListClass::operator=(/*in*/const DynListClass& rtOp)// right hand class object
    {
    node1* rtCurrPos = rtOp.head; // Initialize to head of rtOp

    string itemCopy; // Hold a copy of the ItemType rtOp node1 contains

    Clear(); //Delete current values and set pdms to default values

    FirstPosition(); //Set currPos to the head

    //If the rtOp object is not empty
    if(!rtOp.IsEmpty())
        {
        // while loop -- iterate through rtOp until end of list is reached
        while(rtCurrPos !=NULL)
            {
            //Insert new item
            itemCopy = rtCurrPos->attribute; // Copy the attribute of rtCurrPos
            Insert(itemCopy); //Insert item 


            rtCurrPos = rtCurrPos->next; // Move local pointer to point to next node1 in rtOp

            }// end while

        //Set pointers to beginning of the list
        rtCurrPos = rtOp.head;
        FirstPosition();

        // Loop through list until the currPos points to the equivalent value of rtOp
        while(rtCurrPos != rtOp.currPos)
            {
            NextPosition(); //Move to the next node1
            rtCurrPos = rtCurrPos ->next; //Point rtCurrPos to next node1 memory address
            }// end while
        }// end if
    }// end operator =