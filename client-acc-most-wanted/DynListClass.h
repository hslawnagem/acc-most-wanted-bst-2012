/*********************************************************************************************************
FILE NAME : DynListClass.h
AUTHOR : Megan Walsh
DATE : December 17, 2012

PURPOSE:       This specification contains the basis for an unordered list class. 
		       It allows for list insertions and that is about it.
               The class provides a simple list that values can be inserted 
               but never deleted from.

               The class provides:

               12 Public Methods
               2  Private PDMS
               1  Overloaded operator (=)
 
ASSUMPTIONS:
               1) The list is NOT ordered
	           2) Simple dynamic design requires the client to follow doc strictly
               3) Don't NextPosition without being in a while loop to ensure currPos
                   does not go beyond list boundaries.
               4) Values can not be deleted from the list.

INPUT:
               The class is designed to accept any defined ItemType structure.

OUTPUT:   
               The list can be printed in the order that items were inserted.
               
ERROR HANDLING:
                NextPosition()
                -- CurrentPositionNotInListException thrown to prevent moving currPos 
                   out of the list bounds.

SUMMARY OF METHODS:

	DynListClass() 
	 -- Initializes list object

	~DynListClass()
	-- Returns memory to the system

	DynListClass(const DynListClass& orig)
    -- Copy constructor

	IsEmpty()   
	 -- Indicates whether or not the list is empty

	IsFull()   
	 -- Indicates whether or not the list is full

	Insert(ItemType item) 
	 -- Inserts the specified item at the end of the list

	FirstPosition()
	 -- Moves currPos to the beginning of the list

	NextPosition()  
	 -- Moves currPos to the next position in the list

	EndOfList()    
	 -- Determines if currPos is at the end of the list

	BeginningOfList() 
	 -- Determines if CurrPos is at the beginning of the list

	Retrieve()      
	 -- Returns the list element specified by currPos

	operator =      
	 -- Allows aggregate assignment of list objects

	 Clear()
	 -- Clears the list
******************************************************************************************************/	
//	LIBRARIES
#include <cstdlib>          //For null
#include "ListExceptions.h" //Defines exceptions thrown by DynListClass

// Define a node1 object for utilizing pointers
struct node1
{
	string attribute;  //Data held by record
	node1* next;		//Address of next node1
}; // end node1

class DynListClass
{
  public:
	
    /*			CONSTRUCTOR			*/
	DynListClass();		
	/*
	Purpose: Initializes a list object to an empty list
	Pre:	 List has been instantiated
	Post:	 List has been initialized
	*/

	/*			DESTRUCTOR			*/
	~DynListClass();
	/*
	Purpose: To return memory assigned to a list object to the system
	Pre:     List has been instantiated
	Post:    Memory allocated to list has been returned to the system
	*/

	/*			COPY CONSTRUCTOR	 */
	DynListClass(/*in*/const DynListClass& orig); //List to deep copy
	/*
	Purpose: To perform a deep copy of a list object
	Pre:	 Object to be copied has been instantiated
	Post:	 An identical deep copy of the object has been made
	*/
	
	bool IsEmpty() const;			
	/*
	Purpose: Indicates whether or not the list is empty
	Pre:	 List has been instantiated
	Post:	 Returns true if list is empty and false, otherwise
	*/

	bool IsFull() const;			
	/*
	Purpose: Indicates whether or not the list is full
	Pre:	 List has been instantiated
	Post:	 Returns true if list is full and false, otherwise
	*/

	void FirstPosition();
	/*
	Purpose: Moves current position to the beginning of the list
	Pre:	 List has been instantiated
	Post:	 Current position is at the beginning of the list
	*/

	void NextPosition();
	/*
	Purpose: Moves current position to the next element in the list
	Pre:	 List has been instantiated
	Post:	 Current position moves to the next element
    Exceptions:
       CurrentPositionNotInListException if position moved beyond end of list
	*/
    
    void LastPosition();
        /*
	Purpose: Move to the end of list
	Pre:	 List has been instantiated
	Post:	Current position will be at the end of the list
	*/

	bool BeginningOfList() const;
	/*
	Purpose: Determines if current position is at the beginning of the list
	Pre:	 List has been instantiated
	Post:	 Returns true if at the end of the list, and false, otherwise
	*/

	bool EndOfList() const;
	/*
	Purpose: Determines if at the end of the list
	Pre:	 List has been instantiated
	Post:	 Returns true if at the end of the list, and false, otherwise
	*/

	string Retrieve() const;
	/*
	Purpose: Returns the current item in the list
	Pre:	 EndOfList is false
	Post:	 Returns the item at currPos
	*/

	void Insert(/*in*/string item);	//item to be added
	/*
	Purpose: Inserts item at the end of the list
	Pre:	 List is not full
	Post:	 Item has been inserted. Current Pos at item before inserted node1
	*/
	
	void Clear();
	/*
	Purpose: To clear the object
	Pre:	 Object has been instantiated
	Post:    Object has been cleared and reset to its original state
	*/

    void operator =(/*in*/const DynListClass& rtOp);// right hand class object

  private:
 	node1* head;          // First element in list
	node1* currPos; 		 // Position of current element
}; // end DynListClass
