/*****************************************************************************************************
FILE NAME: bstclass.h
AUTHOR: Megan Walsh
DATE: Dec 7 2012
PURPOSE:           BstClass provides the specifications of a binary search tree data structure. 
                   The specification defines a class template that can be used in conjunction 
                   with multiple data types though to have access to the full functionality of
                   this specification an object must defined as an ItemType containing a KeyType
                   field. This Binary Search tree is ordered and does not allow for any duplicate 
                   keys to be inserted. 

                       The specification provides:

                       15 Public Methods
                        5 Overloaded Operators
                            =  ...Assignment
                            +  ...Combination
                            == ...Equality
                            != ...Inequality
                            *  ...Union

                       15 Protected Methods 
                       1 Private Data Member
                    
                   The pdm of this class is a pointer the first item in the Binary Search Tree thus
                   access to this pdm is concealed by wrapping any method requiring the pdm as input
                   into a "wrapper" function. Wrapper functions are all Public and can be accessed
                   by the client.

                   Two function pointers are provided in this specification

                       typedef void(*FunctionType) (const ItemType&)
                       --Allows client to access data for such purposes as displaying contents to
                         console.

                       typedef void(*FunctionType2) (const ItemType&, ofstream& dout)
                       --Allows client to access data for purposes such us displaying to console
                         or printing data to an output file                

ASSUMPTIONS:
				(1) IMPORTANT: PLEASE NOTE:  THIS IS A CLASS TEMPLATE,  THEREFORE: 
					a) THE STRUCT ItemType DECLARATION MUST BE SUPPLIED BY CLIENT AND 
						APPEAR/be included  ABOVE THE CLIENT MAIN. 
					b) ItemType SHOULD CONTAIN A FIELD OF KeyType CALLED key.
						This will be used to order the Binary Search Tree.
					c) KeyType SHOULD APPEAR AS A typedef ABOVE THE ItemType DECLARATION.

                (2) The specification provides a forward declaration of a node. The node must contain
                    a right and left internal node pointer in order for the class to fully function.
							
EXCEPTIONS THROWN:
				OutofMemory is thrown when 			 
	                Public member functions that throw an OutOfMemory Exception are:
					a) node<ItemType>* Allocate();
			 
				Use of each method above should be enclosed in a try catch block to handle 
                possibility of an exception being thrown.

SUMMARY OF METHODS:

 PUBLIC:
    BstClass();
    -- Constructor

    ~BstClass();
    --Destructor

    BstClass(const BstClass<ItemType>& orig);
    -- Copy Constructor

    bool  IsEmpty() const;		
    -- Determines if object is empty
    
    bool  IsFull() const;   
    --Determines if object is full [returns false]
    
    void InOrder(FunctionType visit);           [wrapper]
    --Iterate through the object LNR
   
   void PreOrder(FunctionType visit);           [wrapper]
    --Iterate through the object in LRN
   
   void InOrderReverse(FunctionType visit);     [wrapper] 
    --Iterate through object in RNL

    void rPreOrder(FunctionType2 visit, ofstream& dout);
    --Iterates through bst in LRN order allows file out access to client
    
    ItemType Retrieve(KeyType key) const;	    [wrapper]
    --Retrieve an item based on key if it exist in the bst
    
    int ReturnLength()const;                    [wrapper]
    --Traverses and counts number of nodes
    
    bool Find(KeyType key) const ;              [wrapper]
    --Finds if an item based on key exists in the bst
    
    bool Insert(ItemType newItem);              [wrapper]
     --Inserts an item in the bst based on newItem key
    
    bool Delete(KeyType key);	                [wrapper]			
    --Deletes an item based on key
    
    void Clear();                               [wrapper]						
    --Returns data to the system and sets pdms to default value
    
    virtual void operator = (const BstClass<ItemType>& orig); 
    --Overloaded operate assigns objects --used in copy constructor
   
    virtual bool operator==(const BstClass<ItemType>& rtOp) const;
    --Overloaded == operator tests if two bsts contain the same keys
    
    virtual bool operator!=(const BstClass<ItemType>& rtOp) const;
    --Overloaded operator != tests if two bsts do not contain the same keys
   
    virtual BstClass<ItemType> operator+(const BstClass<ItemType>& rtOp)const;
    --Overloaded operator + adds combines the data of two bsts without allowing 
      duplication of data
    
    virtual BstClass<ItemType> operator*(const BstClass<ItemType>& rtOp)const;
    --Overloaded operator * combines data fields if both are present in two bsts

 PROTECTED:      
    ItemType rRetrieve(node<ItemType>* trav, KeyType key) const;
    --Inner workings of Retrieve. Iterates though a bst based on root value provided
       
    int rReturnLength(node<ItemType>* trav) const;
    --Inner workings of RetrunLength. Iterates though a bst based on root value provided
       
    bool rFind(node<ItemType>* trav, KeyType key) const ;
    --Inner workings of Find. Iterates though a bst based on root value provided.
       
    bool rInsert(node<ItemType>*& trav, ItemType newItem);
    --Inner workings of Insert. Iterates though a bst based on root value provided
        
    bool rDelete(node<ItemType>*& trav,KeyType key);
    --Inner working sof delete. Iterates though a bst based on root value provided
                 
    void rPostOrder(node<ItemType>*& trav);
    --Iterates through bst and deletes every node in LRN order
    --Used in Clear and Destructor
               
    void rInOrder(node<ItemType>*& trav,FunctionType visit);
    --Iterates through performing visit of FunctionType on each node
       
    void rPreOrder(node<ItemType>*& trav,FunctionType visit);
    --Iterates through performing visit of FunctionType on each node

    void rPreOrder(node<ItemType>*& trav,FunctionType2 visit, ofstream& dout);
    --Iterates through performing visit of FunctionType2 [output stream access] to each node
     
    void rInOrderReverse(node<ItemType>*& trav,FunctionType visit);
    --Iterates through and performs visit of FunctionType on each node
    
    void rCopyHelper(node<ItemType>*& trav);        [helper of op = and +]
    --Recursive method performs Inserts as trav iterates through another object 
       
    bool rEqualHelper(node<ItemType>*& trav) const; [helper of op ==]
    --Recursive method will return bool if a value of trav is/ is not found in this bst

    void rPlusHelper(node<ItemType>*& trav);       [helper of op +]
    --Recursive method performs Inserts based on finds of values of trav->data
     
    void rAsterHelper(node<ItemType>*& trav, const BstClass<ItemType> bst);   [helper of op *]
    --Recursive method will Insert or Delete based on the existence of a key value in the bst
      accessed by trav or the bst object provided to method
       
    node<ItemType>* Allocate();
    --Initialize a node<ItemType>
******************************************************************************************************/
#include <cstdlib>              //For NULL
#include <fstream>              //For PostOrder to perform output if directed by function call
#include "BSTClassExceptions.h" //Define exceptions thrown by class implementation
using namespace std;
 
//Template for sentinel value to be determined by ItemType -- must be an out of range ID
const int SENTINEL_VALUE = -100;

//Function pointers for client to access list
typedef void(*FunctionType) (/*in*/const ItemType&); //For access to node 
typedef void(*FunctionType2) (/*in*/const ItemType&, /*in out*/ofstream& dout); //access & file output

//Template for node struct (forward declaration) to be defined by implementation 
template<class ItemType> 
struct node;

template<class ItemType>
class BstClass
    {
    public:	
        /*     CONSTRUCTOR    */
        BstClass();		       					
        /*
        PURPOSE: Instantiate an ordered list object 
        PRE:     N/A
        POST:    Empty object will be instantiated
        */
       
        /*     DESTRUCTOR    */
        ~BstClass();	
         /*
        PURPOSE: Destroy a BstClass object
        PRE:     Object must exist
        POST:    BstClass object memory will be returned to the system
        */
      
        /*     COPY-CONSTRUCTOR    */
        BstClass(/*in*/const BstClass<ItemType>& orig);		
        /*
        PURPOSE: Instantiate a BstClass object with data of another BstObject
        PRE:     Copied object should contain data --else an empty object is instantiated
        POST:    Object will be instantiated with data
        */
        
        bool  IsEmpty() const;		
        /*
        PURPOSE: Determines if object is empty 
        PRE:     Object exists.
        POST:    Returns true if empty --else false
        */
        
        bool  IsFull() const;   
        /*
        PURPOSE: Determines if the list is full
        PRE:     Object exists.
        POST:    Returns true if the object is full --else false
        */
        
        void InOrder(/*in*/FunctionType visit);
        /*
        PURPOSE: Allows client function to traverse object in LNR order [left, process, right]
        PRE: Function must have a parameter of const ItemType& 
        POST: Control will given to client defined function
        */
        
        void PreOrder(/*in*/FunctionType visit);
        /*
        PURPOSE: Allows client function to traverse object in NLR order [process, left, right]
        PRE: Function must have a parameter of const ItemType& 
        POST: Control will given to client defined function
        */
        
        void InOrderReverse(/*in*/FunctionType visit);
        /*
        PURPOSE: Allows client function to traverse object in RNL order [right, process, left]
        PRE: Function must have a parameter of const ItemType& 
        POST: Control will given to client defined function
        */
         
        void PreOrder(/*in*/FunctionType2 visit, /*in out*/ofstream& dout);
       /*
        PURPOSE: Allows client function to traverse bst and output data to a file
        PRE:  dout must be initialized and associated with a file name in main
        POST: Control will be given to the client defined function
        */

        ItemType Retrieve(/*in*/KeyType key) const;	
        /*
        PURPOSE: Returns a record (ItemType) specified by key. If the key does not appear within 
                 the tree, the method returns a record whose key field contains a SENTINEL_VALUE.
                 SENTINEL VALUE is defined as a value that would be normally outside the range of 
                 valid keys assigned by the program and would be defined within the ItemType.h file
        PRE:     Object exists. For successful retrieve --item must be in list.
        POST:    An object is returned. 
                 --If item was found object with corresponding key is returned
                 --Else the object was not found, a record with an out of range key is returned
        */
        
        int ReturnLength()const; 
        /*
        PURPOSE: Returns the number of items in list.
        PRE:     Object exists.
        POST:    Returns the number of items in the object.
        */
        
        bool Find(KeyType key) const ;
        /*
        PURPOSE: Determine if a value exists in the list.
        PRE:     Object exists.
        POST:    Returns true if the key is found within the tree, false otherwise.
        */
    
        bool Insert(ItemType newItem); 
        /*
        PURPOSE: Insert an item into the list.
        PRE:     ItemType must have a KeyType called key defined with struct in order for method to work
        POST:    If new item is not a duplicate --newItem will be inserted and method will return true.
                 Else if new item is a duplicate it will not be inserted and method will return false.
        */
        
        bool Delete(KeyType key);				
        /*
        PURPOSE: Deletes a list entry specified by key.
        PRE:     Object exists.
        POST:    If it does not appear within the tree nothing is changed and false is returned, otherwise 
                 the element is removed and true is returned
        */
       
        void Clear();   						
        /*
        PURPOSE: Clear the list of values.
        PRE:     Object exists.
        POST:    Return nodes back to system memory and set object to default values --empty
        */

        virtual void operator = (/*in*/const BstClass<ItemType>& orig); 
        /*
        PURPOSE: Perform a deep copy to assign values of one list to another.
        PRE:     Both objects exist.
        POST:    The values of orig/right object are assigned to this/left object
        */

        
        virtual bool operator==(/*in*/const BstClass<ItemType>& rtOp) const;
        /*
        PURPOSE: Compare lists for equality.
        PRE:     Both lists exist.
        POST:    Returns true if lists contain the exact same keys -- false otherwise.
        */

        virtual bool operator!=(/*in*/const BstClass<ItemType>& rtOp) const;
        /*
        PURPOSE: Compare lists for inequality.
        PRE:     Both lists exist.
        POST:    Returns false if lists don't contain the exact same keys.
        */
        
        virtual BstClass<ItemType> operator+(/*in*/const BstClass<ItemType>& rtOp)const;
        /*
        PURPOSE: Combine the values of two list without data duplication.
        PRE:     Objects exist.
        POST:    Adds the elements of two lists together. If a duplicate key exists the second key
                 is not inserted into the tree.
        */

        virtual BstClass<ItemType> operator*(/*in*/const BstClass<ItemType>& rtOp)const;
        /*
        PURPOSE: Provide the disjoint of two list.
        PRE:     Objects exist.
        POST:    Returns a BstClass object contained values that existed in both list.
        */

    protected:
        
        ItemType rRetrieve(/*in*/node<ItemType>* trav,/*in*/ KeyType key) const;
        /*
        PURPOSE: Protected method used in Retrieve to initialize recursive call.
        PRE:     N/A
        POST:    Method will traverse the structure 
                 --If item was found object with corresponding key is returned
                 --Else the object was not found, a record with an out of range key is returned
        */
        
        int rReturnLength(/*in*/node<ItemType>* trav) const;
        /*
        PURPOSE: Protected method used in ReturnLength to initialize recursive call.
        PRE:     N/A
        POST:    Returns the number of items in the object.
        */
        
        bool rFind(/*in*/node<ItemType>* trav,/*in*/ KeyType key) const ;
        /*
        PURPOSE: Protected wrapper method used in Find to initialize recursive call.
        PRE:     N/A
        POST:    Returns true if the key is found within the tree, false otherwise.
        */
        
        bool rInsert(/*in*/node<ItemType>*& trav, /*in*/ItemType newItem);
        /*
        PURPOSE: Protected method used in Insert to initialize recursive call.
        PRE:     N/A
        POST:    If new item is not a duplicate --newItem will be inserted and method will return true.
                 Else if new item is a duplicate it will not be inserted and method will return false.
        */
         
        bool rDelete(/*in*/node<ItemType>*& trav,/*in*/KeyType key);
        /*
        PURPOSE: Protected method used in Delete to initialize recursive call.
        PRE:     N/A
        POST:    If it does not appear within the tree nothing is changed and false is returned, otherwise 
                 the element is removed and true is returned
        */
        
        void rInOrder(/*in*/node<ItemType>*& trav,/*in*/FunctionType visit);
        /*
        PURPOSE: Protected method traverses tree and gives control to visit
        PRE:     trav must be initialized in a wrapper method with the tree root 
        POST:    The tree will be traversed and visit will perform at every node in LNR order
        */      
        
        void rPreOrder(/*in*/node<ItemType>*& trav,/*in*/FunctionType visit);
        /*
        PURPOSE: Protected method traverses tree and gives control to visit
        PRE:     trav must be initialized in a wrapper method with the tree root 
        POST:    The tree will be traversed and visit will perform at every node in NLR order
        */

          void rInOrderReverse(/*in*/node<ItemType>*& trav,/*in*/FunctionType visit);
        /*
        PURPOSE: Protected method traverses tree and gives control to visit
        PRE:     trav must be initialized in a wrapper method with the tree root 
        POST:    The tree will be traversed and visit will perform at every node in RNL order
        */
        
        void rPostOrder(/*in*/node<ItemType>*& trav);
        /*
        PURPOSE: Protected method traverses tree and returns each node to system.
        PRE:     trav must be initialized in a wrapper method with the tree root 
        POST:    The tree will be traversed and every node will be returned to system.
        */
        
       void rPreOrder(/*in*/node<ItemType>*& trav,/*in*/FunctionType2 visit, /*in*/ofstream& dout);
       /*
        PURPOSE: Protected method traverses tree and gives control to visit
        PRE:     trav must be initialized in a wrapper method with the tree root 
                 dout must be initialized and associated with a file name in client 
        POST:    The tree will be traversed and visit will perform at every node in NLR order
        */
               
        void rCopyHelper(/*in*/node<ItemType>*& trav) ;
        /*
        PURPOSE: Protected method used in the assignment operator to traverse and insert objects from
                 another object.
        PRE:     N/A
        POST:    Object will be traversed and values found at trav nodes will be inserted into the list
        */
        
        bool rEqualHelper(/*in*/node<ItemType>*& trav) const;
        /*
        PURPOSE: Protected method used in equality operated to compare values of list to another
        PRE:     N/A
        POST:    Returns true if lists contain the exact same keys -- false otherwise.
        */
         
        void rPlusHelper(/*in*/node<ItemType>*& trav) ;
        /*
        PURPOSE: Protected method performs Inserts based on finds of values of trav
        PRE:     trav must be initialized to the root of another tree
        POST:    Items that don't yet exist in this tree will be inserted
        */
        
        void rAsterHelper(/*in*/node<ItemType>*& trav,/*in*/ const BstClass<ItemType> bst) ;
        /*
        PURPOSE: Protected method will Insert or Delete based on the existence of a key value in the bst
                 accessed by trav or the bst object provided to method
        PRE:     trav must be initialized to the root of another tree
        POST:    The object this is called on will contain the union of the tree of root and the bst
        */
        
        node<ItemType>* Allocate();
        /*
        PURPOSE: Allocates a node for tree with both a left and right pointers set to NULL.
        PRE:     N/A
        POST:    If memory exists the node is returned. If memory does not exist, an OutofMemory
                 exception is thrown.

        Exceptions:
            OutOfMemory()
            --If system can not allocate memory to new nodes
        */
    private:
        node<ItemType>* root; //Pointer to the top of the tree
    }; //end class

#include "bstClass.cpp" //Include the implementation file

