/*********************************************************************************************
FILE NAME: BstTestClient.cpp
DATE: Dec 17, 2012
AUTHOR: Megan Walsh
PURPOSE: Test class methods of the BstClass objects

ERROR HANDLING:   None

SUMMARY OF FUNCTIONS:
void PopulateTree(BstClass<ItemType>& tree, int numItems);
--Populate the class object

void PrintTree(BstClass<ItemType>& bstPrint);
--Print the entire class object

void PrintKey(const ItemType& item);
--For testing Recursive traversal methods of bst

void PrintToFile(const ItemType& item, ofstream& dout);
--For testing traversal function pointer that allows file output
*********************************************************************************************/
//Libraries___________________________________________________________________________________
#include "ItemType.h"     //Define item used by class template
#include "bstclass.h"     //Class to test
#include <iostream>       //For output to console
#include <string>         //For output to console
//using namespace std;

//Constants
const int MAX_KEY_VAL = 54;              //Max value of key in list
const string OUT_FILE ="outputTest.dat"; //Output file name

//Function Prototypes_________________________________________________________________________
void PopulateTree(/*in out*/BstClass<ItemType>& tree, /*in*/int numItems);
void PrintTree(/*in*/BstClass<ItemType>& bstPrint);
void PrintKey(/*in*/const ItemType& item);
void PrintToFile(/*in*/const ItemType& item, /*in out*/ofstream& dout);
/***********************************************************************************************
TESTING FLAGS                       Descriptions                        Date            Result
***********************************************************************************************/
//#define _TEST_CONSTRUCT_          // Test default constructor         Dec 13          Done
//#define _TEST_INSERT_             // Test EnQ method                  Dec 13          Done
//#define _TEST_COPY_CON_           // Test class copy constructor      Dec 16          Done
//#define _TEST_DESTRUCT_           // Test class destructor            Dec 14          Done
//#define _TEST_RETRIEVE_           // Test Retrieve method             Dec 17          Done 
//#define _TEST_FIND_               // Test Find method                 Dec 17          Done
//#define _TEST_DELETE_             // Test Delete method               Dec 17          Done
//#define _TEST_CLEAR_              // Test Clear method                Dec 14          Done
//#define _TEST_RETURN_LENGTH_      // Test ReturnLength method         Dec 14          Done
//#define _TEST_ISEMPTY_            // Test IsEmpty method              Dec 14          Done 
//#define _TEST_ISFULL_             // Test IsFull method               Dec 14          Done
//#define _TEST_IN_ORDER_           // Test InOrder method              Dec 19          Done 
//#define _TEST_PRE_ORDER_          // Test IsEmpty method              Dec 19          Done 
//#define _TEST_IN_ORDER_REVERSE_   // Test IsEmpty method              Dec 19          Done
//#define _TEST_PRE_ORDER_2_        // Test printing to file            Dec 19          Done
//#define _TEST_OP_ASS_             // Test operator =                  Dec 16          Done
//#define _TEST_OP_EQUALITY_        // Test operator ==                 Dec 16          Done
//#define _TEST_OP_PLUS_            // Test operator +                  Dec 16          Done
//#define _TEST_OP_ASTER_           // Test operator *                  Dec 16          Done
/**********************************************************************************************
**********************************************************************************************/
void main()
    {
#ifdef _TEST_CONSTRUCT_
    BstClass<ItemType> bst1;
#endif //======================================================================================

#ifdef _TEST_INSERT_ 
    BstClass<ItemType> bstInsert1; //Class object to test
    bool inserted;
    ItemType item;
    
    item.key = 9;

    //Insert one item
    //-------------------------------------------------
    inserted = bstInsert1.Insert(item);
    if(inserted)
        cout<< "The item was inserted" <<endl;
    else
        cout<< "The item was NOT inserted" <<endl;

    //Insert duplicate item
    //-------------------------------------------------
    inserted = bstInsert1.Insert(item);
    if(inserted)
        cout<< "The item was inserted" <<endl;
    else
        cout<< "The item was NOT inserted" <<endl;

    //Insert multiple items into tree
    //-------------------------------------------------
    for(int i = 0; i <30; i++)
        {
        item.key = rand() % MAX_KEY_VAL;
        inserted = bstInsert1.Insert(item);
        if(inserted)
        cout<< item.key <<" was inserted" <<endl;
        else
        cout<< item.key <<" was NOT inserted" <<endl;
        }// end for

    //Test helper function
    //-------------------------------------------------
    PopulateTree(bstInsert1, 15);
#endif //======================================================================================
    
#ifdef _TEST_COPY_CON_
    BstClass<ItemType> bstCop1; //Object to hold copied data

    PopulateTree(bstCop1, 10); //Populate the bst

    BstClass<ItemType> bstCop2(bstCop1); //Instantiate an object with data 

    PrintTree(bstCop2); //Print the instantiated object

    //Iterate and delete all values of first object
    for(int i = 0; i < MAX_KEY_VAL; i++)
        {
        bstCop1.Delete(i);
        }//end for

    //Print second object to make sure values were not affected
    PrintTree(bstCop1); //Print the first obj
    PrintTree(bstCop2); //Print the instantiated object
#endif //======================================================================================
    
#ifdef _TEST_DESTRUCT_
    BstClass<ItemType> bstDest1;
#endif //======================================================================================
    
#ifdef _TEST_RETRIEVE_ 
    BstClass<ItemType> bstRetrieve1; //object to test

    PopulateTree(bstRetrieve1, 10);

    //Test Retrieve one defined item
    //-------------------------------------------------
    cout<<bstRetrieve1.Retrieve(10).key<<endl <<endl;

    //Test continuously retrieving values
    //-------------------------------------------------
    //iterate through all possible key values --print key if it is in the list
    for(int i = 0; i < MAX_KEY_VAL ; i++)
        {
        if(bstRetrieve1.Retrieve(i).key != SENTINEL_VALUE)
            cout<<bstRetrieve1.Retrieve(i).key<<endl;
        }// end for

    //Test helper function
    //-------------------------------------------------
    PrintTree(bstRetrieve1);
#endif //======================================================================================  
    
#ifdef _TEST_FIND_ 
    BstClass<ItemType> bstFind1;  //object to test
    ItemType itemFind1;

    //Populate the bst with values
    PopulateTree(bstFind1, 10);

    //Attempt to find all values possibly in the structure

    for(int i = 0; i < MAX_KEY_VAL; i++)
       {
        itemFind1.key = i;
        if(bstFind1.Find(itemFind1.key))  ///Weird error here
            cout<< i << " is a value in the tree." <<endl;
       /* else
            cout<< i << " is NOT a value in the tree." <<endl;*/
            
       }//end for
#endif //======================================================================================  
#ifdef _TEST_DELETE_  
    BstClass<ItemType> bstDel1;
    bool deleted;

    PopulateTree(bstDel1, 10);

    //Delete First item
    //-------------------------------------------------
    deleted = bstDel1.Delete(41);
    if(deleted)
        cout<< "Value was deleted"<<endl;
    else
        cout<< "Value was NOT deleted" <<endl;

    PrintTree(bstDel1);

    //Delete an ancestor node embedded in tree
    //-------------------------------------------------
    deleted = bstDel1.Delete(16);
    if(deleted)
        cout<< "Value was deleted"<<endl;
    else
        cout<< "Value was NOT deleted" <<endl;

     PrintTree(bstDel1);

    //Delete entire tree
    //-------------------------------------------------
     for(int i = 0; i < MAX_KEY_VAL; i++)
         {
         deleted= bstDel1.Delete(i);
         if(deleted)
             cout << i << " was deleted." <<endl;
         /*else
             cout <<i << " not deleted."<<endl;*/
         }//end for

     PrintTree(bstDel1);

    //Delete entire tree...in reverse key order
    //-------------------------------------------------
     PopulateTree(bstDel1, 10); //repopulate the tree

     for(int i = MAX_KEY_VAL; i > -5; i--)
         {
         deleted= bstDel1.Delete(i);
         if(deleted)
             cout << i << " was deleted." <<endl;
         /*else
             cout <<i << " not deleted."<<endl;*/
         }//end for
#endif //======================================================================================
    
#ifdef _TEST_CLEAR_   
     BstClass<ItemType> bstClr1;  //object to test

     bstClr1.Clear();    //Attempt clear on empty object

     PopulateTree(bstClr1, 10);  //populate the object

     bstClr1.Clear();   //Clear the populated bst

     PrintTree(bstClr1);   //print the bst --should be no values

     PopulateTree(bstClr1, 15); //repopulate bst to check clear wasn't funky
#endif //====================================================================================== 
    
#ifdef _TEST_RETURN_LENGTH_ 

     BstClass<ItemType> bstLeng1; //object to test

     //Test length on empty list
     cout<<"Length: " << bstLeng1.ReturnLength()<<endl;

     PopulateTree(bstLeng1, 20);

     //Test length on list with values
     cout<<"Length: " << bstLeng1.ReturnLength()<<endl;
#endif //====================================================================================== 

#ifdef _TEST_ISEMPTY_    
    BstClass<ItemType> bstEmptyTrue;  //object to test
    BstClass<ItemType> bstEmptyFalse; //object to test

    PopulateTree(bstEmptyFalse, 1); //Insert one item into the tree that is not empty

    //Test the populated tree
    //-------------------------------------------------
    if(bstEmptyFalse.IsEmpty())
        cout << "The structure is empty"<<endl;
    else
        cout << "The structure is not empty"<<endl;

    //Test an empty tree
    //-------------------------------------------------
    if(bstEmptyTrue.IsEmpty())
        cout << "The structure is empty"<<endl;
    else
        cout << "The structure is not empty"<<endl;
#endif //======================================================================================

#ifdef _TEST_ISFULL_    
    BstClass<ItemType> bstFull1; //object to test

     //Test an empty tree
    //-------------------------------------------------
    if(bstFull1.IsFull())
        cout << "The structure is full"<<endl;
    else
        cout << "The structure is not full"<<endl;  

    //Test the populated tree
    //-------------------------------------------------

    PopulateTree(bstFull1, 10); //Insert many items into 

    if(bstFull1.IsFull())
        cout << "The structure is full"<<endl;
    else
       cout << "The structure is not full"<<endl;
#endif //====================================================================================== 

#ifdef _TEST_IN_ORDER_    
    BstClass<ItemType> bstInOrder1;

    PopulateTree(bstInOrder1, 10); //Populate with some values

    bstInOrder1.InOrder(PrintKey);
    
#endif //====================================================================================== 

#ifdef _TEST_PRE_ORDER_    

    BstClass<ItemType> bstPreOrder1;

    PopulateTree(bstPreOrder1, 10); //Populate with some values

    bstPreOrder1.PreOrder(PrintKey);
#endif //======================================================================================  
  
#ifdef _TEST_PRE_ORDER_2_    
    BstClass<ItemType> postToFile1;  //object to test
    ofstream dout; // create output stream variable
    dout.open(OUT_FILE); //Associate an output name with the output file

    PopulateTree(postToFile1, 12); //Populate the little tree

    //Test overloaded PostOrder
    postToFile1.PreOrder(PrintToFile, dout);
#endif //======================================================================================

#ifdef _TEST_IN_ORDER_REVERSE_   
    BstClass<ItemType> bstRevOrder1;

    PopulateTree(bstRevOrder1, 10); //Populate with some values

    bstRevOrder1.PreOrder(PrintKey);
#endif //======================================================================================  

#ifdef _TEST_OP_ASS_   
    BstClass<ItemType> bstAss1;  //object to test
    BstClass<ItemType> bstAss2;  //object to test

    bstAss1= bstAss2;   //Test assigning empty object to another empty object

    //Populate object with data
    PopulateTree(bstAss1, 3);
    PopulateTree(bstAss2, 9);

    //Assign larger bst to smaller bst
    bstAss1 = bstAss2;

    PrintTree(bstAss1);  //Verify

    bstAss2.Clear();     //Clear object

    bstAss2 = bstAss1;   //Assign empty object data

    PrintTree(bstAss2);  //Verify

    bstAss2.Clear();     //Clear object

    bstAss1 = bstAss2;   //Assign empty object to an object with data

    PrintTree(bstAss2);  //Verify
#endif //======================================================================================  

#ifdef _TEST_OP_EQUALITY_   
    BstClass<ItemType> bstEq1; //object to test
    BstClass<ItemType> bstEq2; //object to test

    //Test the un-populated trees for inequality
    //-------------------------------------------------
    if(bstEq1 == bstEq2)
        cout<< "Equal bsts"<<endl;
    else
        cout<< "These ain't no stinking equal bsts" <<endl;

    //Populate bsts with different values
    PopulateTree(bstEq1, 10);
    PopulateTree(bstEq2, 17);

    //Test the populated trees for inequality
    //-------------------------------------------------
    if(bstEq1 == bstEq2)
        cout<< "Equal bsts"<<endl;
    else
        cout<< "These ain't no stinking equal bsts" <<endl;

    //Test the populated trees for equality
    //-------------------------------------------------
    bstEq1 = bstEq2;

    if(bstEq1 == bstEq2)
        cout<< "Equal bsts"<<endl;
    else
        cout<< "These ain't no stinking equal bsts" <<endl;
#endif //======================================================================================

#ifdef _TEST_OP_PLUS_  

    BstClass<ItemType> bstPlus1;
    BstClass<ItemType> bstPlus2;
    BstClass<ItemType> bstPlus3;

    //Test empty left operator assignment to empty bst
    //-------------------------------------------------
    PopulateTree(bstPlus2, 7); //Populate rt op
    bstPlus3 = bstPlus1 + bstPlus2;
    PrintTree(bstPlus3);

   //Test empty right operator assignment to empty bst
   //-------------------------------------------------
    bstPlus2.Clear();
    bstPlus3.Clear();
    PopulateTree(bstPlus1, 9);
    bstPlus3 = bstPlus1 + bstPlus2;
    PrintTree(bstPlus3);

   //Test empty right operator assignment to non empty bst
   //-------------------------------------------------
    bstPlus3.Clear();
    PopulateTree(bstPlus3, 15);
    bstPlus3 = bstPlus1 + bstPlus2;
    PrintTree(bstPlus3);

    //Test + op on objects with data
   //-------------------------------------------------
    bstPlus3.Clear();
    bstPlus1.Clear();
    bstPlus2.Clear();
    PopulateTree(bstPlus1, 10);
    PopulateTree(bstPlus2, 19);

    bstPlus3 = bstPlus1 + bstPlus2;

    PrintTree(bstPlus3);
#endif //======================================================================================  
    
#ifdef _TEST_OP_ASTER_   

    BstClass<ItemType> bstAster1;
    BstClass<ItemType> bstAster2;
    BstClass<ItemType> bstAster3;

    //Test empty left operator asterisk to empty bst
    //-------------------------------------------------
    PopulateTree(bstAster2, 7); //Populate rt op
    bstAster3 = bstAster1 * bstAster2;
    PrintTree(bstAster3);

   //Test empty right operator asterisk to empty bst
   //-------------------------------------------------
    bstAster2.Clear();
    bstAster3.Clear();
    PopulateTree(bstAster1, 9);
    bstAster3 = bstAster1 * bstAster2;
    PrintTree(bstAster3);

   //Test empty right operator asterisk to non empty bst
   //-------------------------------------------------
    bstAster3.Clear();
    PopulateTree(bstAster3, 15);
    bstAster3 = bstAster1 * bstAster2;
    PrintTree(bstAster3);

   //Test * op on objects with data
   //-------------------------------------------------
    bstAster3.Clear();
    bstAster1.Clear();
    bstAster2.Clear();
    PopulateTree(bstAster1, 10);
    PopulateTree(bstAster2, 19);

    bstAster3 = bstAster1 * bstAster2;

    PrintTree(bstAster3);

    //Test * op on objects with data assigned to obj with data
   //-------------------------------------------------
    bstAster3.Clear();
    bstAster1.Clear();
    bstAster2.Clear();
    PopulateTree(bstAster1, 10);
    PopulateTree(bstAster2, 19);
    PopulateTree(bstAster3, 50);

    bstAster3 = bstAster1 * bstAster2;

    PrintTree(bstAster3);
#endif //======================================================================================  
    }// end main
//                                   FUNCTION DEFINITIONS

    /******************************************************************************************
    Purpose: Print the class object being tested
    Pre:     Object must exist and Insert must work
    Post:    Object will be populated with random key values
    *******************************************************************************************/
void PopulateTree(/*in out*/BstClass<ItemType>& tree, // Tree to populate with random values
    /*in*/int numItems) //Number of items to insert into the tree
    {
    bool inserted;
    ItemType item;

    //Populate heading
    cout<< "=============="<<endl;
    cout<< "POPULATED TREE" <<endl;
    cout<< "=============="<<endl;
    
    //Insert the # of items into the tree
    for(int i = 0; i <numItems; i++)
        {
        item.key = rand() % MAX_KEY_VAL;
        inserted = tree.Insert(item);
        if(inserted)
            cout << item.key<<endl;
        }// nd for
    cout<< "=============="<<endl;
    }//end PopulateTree
    /******************************************************************************************
    Purpose: Print the class object contents
    Pre:     Object must exist and Retrieve must work
    Post:    Object contents will be printed
    *******************************************************************************************/
void PrintTree(/*in*/BstClass<ItemType>& bstPrint) //Object to print to screen (iterative)
    {
    cout<<"========" <<endl;
    cout<<"Bst Tree" <<endl;
    cout<<"========" <<endl;
     
    //if the object to print is not empty
    if(!bstPrint.IsEmpty())
        {
     //Iterate through all possible ID's in list and print value if it exist in the structure
    for(int i = 0; i < MAX_KEY_VAL ; i++)
        {
        if(bstPrint.Retrieve(i).key != SENTINEL_VALUE)
            cout<<bstPrint.Retrieve(i).key<<endl;
        }//end for

        }// end if

    //Else if the object is empty --print empty
    else
        cout<< "Empty BST"<<endl;
    cout<<"========" <<endl<<endl;
    }// end PrintItem
    /******************************************************************************************
    Purpose: Test transversal method
    Pre:     Object must exist and contain appropriate function pointer
    Post:    Contents of object will be printed to screen
    *******************************************************************************************/
void PrintKey(/*in*/const ItemType& item) //Object to print key (recursive)
    {
     cout <<item.key<<endl; //print to screen  
    }
    /******************************************************************************************
    Purpose: Test transversal method
    Pre:     Object must exist and contain appropriate function pointer, 
             dout must be initialized
    Post:    Contents of object will be printed to file
    *******************************************************************************************/
void PrintToFile(/*in*/const ItemType& item, //object to print
   /*in out*/ ofstream& dout) //output stream to send output
    {
    dout << item.key<<endl; //Print to file
    }// end PrintToFile

