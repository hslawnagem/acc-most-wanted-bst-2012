/*******************************************************************************
FILE NAME:ItemType.h
AUTHOR: Megan Walsh
DATE: November 15, 2012
PURPOSE: Define a ItemType object
*******************************************************************************/
#ifndef itemtype_h
#define itemtype_h
#include "DynListClass.h"
#include <string>
using std::string;

//DEFINE KEYTYPE : Necessary for ordering of class
typedef string KeyType;

//#include "DynListClass.h" //For including a criminal attribute list
struct ItemType		
{					
	//KeyType key; //Key for order keeping
    KeyType  key;
    DynListClass attributes;
}; // end ItemType

#endif
