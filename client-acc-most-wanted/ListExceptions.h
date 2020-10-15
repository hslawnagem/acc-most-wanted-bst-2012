/*********************************************************************************
FILE NAME: ListExceptions.h
AUTHOR:Megan Walsh
DATE: October 15, 2012

PURPOSE:Define exceptions of an DynListClass. Each exception class
		includes a default constructor with the message pdm set to a default error 
		message pertaining to the type of error handled. A non-default constructor 
		allows the client to modify the message of the exception. 

EXCEPTIONS:
	 CurrentPositionNotInListException
		--Attempted to move currPos out of valid index bounds
*********************************************************************************/
// Libraries
#include <string>  // for error message pdm
using std::string; // for error message pdm

/*********************************************************************************/
// Exception: Attempted to move currPos to invalid position of list
// Pre:currPos is not within the index bounds of list
// Post:Error message is generated
	class CurrentPositionNotInListException
	{
	public :
		CurrentPositionNotInListException() 
			{message = "ERROR: Current position is invalid.";}
		CurrentPositionNotInListException(string theMessage):message(theMessage){}
		string GetMessage() const{return message;}
			
	private:
		string message;// error message
	}; //end CurrentPostionNotInListException
