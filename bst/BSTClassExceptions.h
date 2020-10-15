/***********************************************************************************************
FILE NAME:BstClassExceptions.h
AUTHOR: Megan Walsh
DATE: November 15 2012
PURPOSE: Define exceptions used by a dynamic binary search tree data structure

ASSUMPTIONS: None

EXCEPTIONS DEFINED:
	class OutOfMemory
        --If system can not allocate memory to new nodes
*********************************************************************************************/
// Libraries
#include <string>  // for error message pdm
using std::string; // for error message pdm

/******************************************************************************************
EXCEPTION: If system can not allocate memory to new nodes
PRE:   System is out of memory
POST: Error message is generated
*******************************************************************************************/
	class OutOfMemory
    {
    public :
		OutOfMemory() 
			{message = "ERROR: OUT OF MEMORY";}
		OutOfMemory(string theMessage):message(theMessage){}
		string GetMessage() const{return message;}	
	private:
		string message;// error message 
   }; // end class