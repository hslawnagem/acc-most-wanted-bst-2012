/**********************************************************************************************************
FILE NAME: bstClass.cpp
AUTHOR: Megan Walsh
DATE: Dec 7 2012
PURPOSE: Contains the implementation of methods defined in bstclass.h
**********************************************************************************************************/
template <class ItemType> 
struct node
    {
    ItemType data;   //Data to held by a node
    node* left;      //Left sub-tree 
    node* right;     //Right sub-tree
    };
//============================================================================================
template <class ItemType>
BstClass<ItemType>::BstClass()
    {
     root = NULL;  //Assign root to NULL
    }// end Default Con.
//============================================================================================
template <class ItemType>
BstClass<ItemType>::~BstClass() 
    {
     rPostOrder(root); // Call PostOrder to delete values of tree
    }// end Destructor
//============================================================================================
template <class ItemType>
BstClass<ItemType>::BstClass(/*in*/const BstClass& orig)  // Object to copy
    {
    root = NULL;     //Set root to default values
    operator=(orig); //Assign values of orig to the bst
    }// end Copy Con
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::IsEmpty() const
    {
    return (root == NULL); //Return if root is == or != to NULL
    }// End IsEmpty
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::IsFull() const
    {
    return false; //List can always expand
    }// End IsFull
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::InOrder(/*in*/FunctionType visit) //Function to give control
    {
    //Traverse structure in LNR order
    rInOrder(root, visit);  
    }// end rInOrder
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::PreOrder(/*in*/FunctionType visit) //Function to give control
    { 
    //Traverse structure in NLR order
    rPreOrder(root, visit);
    }// end rPreOrder
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::InOrderReverse(/*in*/FunctionType visit) //Function to give control
    {
    //Traverse structure in RLN order
        rInOrderReverse(root, visit);   
    }// end rInOrderReverse
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::PreOrder(/*in*/FunctionType2 visit, // Function to give control
    /*in out*/ ofstream& dout) //Output stream o send output to
    {
    //Traverse structure in RLN order
        rPreOrder(root, visit, dout);   
    }// end rInOrderReverse
//============================================================================================
template <class ItemType>
ItemType BstClass<ItemType>::Retrieve(/*in*/KeyType key) const //Key item to find in object
    {
    return rRetrieve(root, key); //return the ItemType
    }// end Retrieve
//============================================================================================
template <class ItemType>
int BstClass<ItemType>::ReturnLength() const
    {
    //If root is null
    if(root == NULL)
        return 0;   //Return 0 -- no items in the bst
    else
        return rReturnLength(root); //Traverse and count nodes   
    }// end return length
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::Find(/*in*/KeyType key) const //Key to find in object
    {
    return rFind(root, key); //Return result of traversal method
    }
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::Insert(/*in*/ItemType newItem) //Item to insert
    {
    //If the tree is empty allocate memory and insert the first item
    if(root == NULL)
        {
        root = Allocate();  //Allocate memory
        root->data=newItem; //Insert the item
        return true;
        }// end if

    //Else the structure is not empty -- call prot. method to traverse and insert the 
    else
        {
        return rInsert(root,newItem); //Return result of traversal method
        }// end else
    }// end Insert
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::Delete(/*in*/KeyType key) //Key to find and delete
    {
    //If the root is not null
     if(root != NULL )
        return rDelete(root, key); //Return result of traversal method
     else 
         return false; //Delete was not performed
    }// end Delete
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::Clear()
    {
    rPostOrder(root);  // Return all nodes to the system
    root = NULL;       //Set root back to NULL default value
    }//end Clear
//============================================================================================
template <class ItemType>
void BstClass<ItemType>::operator = 
    (/*in*/const BstClass<ItemType>& orig) //object to copy
    {
    node<ItemType>* tempNd = orig.root;
    
    //If the orig bst is empty and this bst is not empty --Just clear bst for assignment
    if(orig.IsEmpty() && !IsEmpty())
        Clear(); //Clear the list

    //Else if orig is not empty
    else 
        {
        //If this bst is not empty --clear it to remove original values
         if(!IsEmpty())
             Clear();
      
         //Copy helper function will iterate through orig starting at root
         //inserting values in the same order as they were inserted into orig
         rCopyHelper(tempNd);
        }// end else if
    }// end op =
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::operator ==
    (/*in*/const BstClass<ItemType>& rtOp) const //bst object
    {
    //If the bsts are of different lengths --return false not equal
    if(ReturnLength() != rtOp.ReturnLength())
        return false;

    //Else objects are of the same length --compare key values for equality
    else
        {
        node<ItemType>* tempNd = rtOp.root; 
        return rEqualHelper(tempNd);
       }// end else
    } // end op ==
//============================================================================================
template <class ItemType>
bool BstClass<ItemType>::operator!=
    (const BstClass<ItemType>& rtOp) const // bst object
    {
    return !(operator==(rtOp)); //Return the opposite value of the == operator result
    }//end op !=
//============================================================================================
template <class ItemType>
BstClass<ItemType> BstClass<ItemType>::operator + 
    (/*in*/const BstClass<ItemType>& rtOp)const //bst object to add values from
    {
    BstClass<ItemType> bstRet; //Object to return

    //If both list are empty --return an empty list
    if(IsEmpty() && rtOp.IsEmpty())
        return bstRet;

    //Else this leftOp is empty and rtOp is the only bst with values 
    else if(IsEmpty() && !rtOp.IsEmpty())
        {
        bstRet = rtOp; //copy values of bst into return obj
        return bstRet; //return object
        }//end else

    //Else this object is not empty
    else if(!IsEmpty() && rtOp.IsEmpty())
        {
        node<ItemType>* tempNd = root; //Hold this class objects root value
        bstRet.rCopyHelper(tempNd);  //Call copy helper to insert this class objects values
        return bstRet;
        }// end else if

    //Else both operands have data
    else
        { 
        node<ItemType>* tempNd = root;  // Hold this class object root value
        bstRet = rtOp; //Copy the values of rtOp into the bst

        //rPlusHelper will traverse this left op structure and insert values that are not 
        //found with the bstRet structure
        bstRet.rPlusHelper(tempNd);

        return bstRet; //Return the bst
        }//end else   
    }// end op +
//============================================================================================
template <class ItemType>
BstClass<ItemType> BstClass<ItemType>::operator * 
    (/*in*/const BstClass& rtOp) const // object to compare key vals to 
    {
    BstClass<ItemType> bstRet; //Object to return

    //If either list empty return the empty list --no vals in common
    if(IsEmpty() || rtOp.IsEmpty())
        return bstRet;

    //Else neither list is empty and values must be compared
    else
        {
        node<ItemType>* tempNd= root; // temp store root val of root
        bstRet.rPlusHelper(tempNd); //Copy all the values of this class 
        bstRet.rAsterHelper(tempNd, rtOp);
        return bstRet;
        } // end else
    }// end op *
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
ItemType BstClass<ItemType>::rRetrieve(/*in*/node<ItemType>* trav, //node to check
    /*in*/ KeyType key) const //key to find
    {
    //If the trav value is not null
    if(trav != NULL)
        {
        //If key value was found
         if(key == trav->data.key)
            return trav->data;

        //Else if the key is less than the node --move left
        else if( key < trav->data.key)
            return rRetrieve(trav->left , key);

        //Else the key is greater than the node --move right
        else //if( key > trav->data.key)
            return rRetrieve(trav->right, key);
        }//end if

    //Else the value is not in the structure --return a record with a sentinel value
    else
        {
        node<ItemType>* sentVal= new node<ItemType>;  //Create a new node
        sentVal->data.key = SENTINEL_VALUE;           //Assign the key data a sentinel value
        return sentVal->data;                         //Return an Item with a sentinel value
        }// end else
    }// end rRetrieve
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
int BstClass<ItemType>::rReturnLength(/*in*/node<ItemType>* trav ) const //node to count
    {
    //If trav is not equal to null
    if(trav != NULL)
        // Add the value of the results of all following recursive methods (both left and right)
        // plus this node (+1)
         return rReturnLength(trav ->left) + rReturnLength(trav->right) +1;
    else 
        return 0; // trav is null don't count a node
    }//end ReturnLength
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
bool BstClass<ItemType>::rFind(/*in*/node<ItemType>* trav, //node to check
    /*in*/ KeyType key) const  //Key to find
    {
    //If the node is not null
    if(trav != NULL)
        {
        //If the key was found in the structure -- return true
        if(key == trav->data.key)
            return true;

        //Else if the key is less than the node --move left
        else if( key < trav->data.key)
            return rFind(trav->left , key);

        //Else the key is greater than the node --move right
        else //if( key > trav->data.key)
            return rFind(trav->right, key);
        }// end if

    //Else a null node has been reached indicating the value was not found -- return false
    else
        return false;
    }// end rFind
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
bool BstClass<ItemType>::rInsert(/*in*/node<ItemType>*& trav, //pointer to node to check
    /*in*/ItemType newItem) //item to insert
    {
    //If the node is not empty
    if(trav!= NULL)
        {  
        //If the node key is equivalent to the newItem --return false [no duplicates]
        if(trav->data.key == newItem.key)
            return false; // The item already exist in the structure and was not inserted

        //Else if the key value is less than the current node
        else if (trav->data.key >newItem.key)
           return rInsert(trav->left, newItem);

        //Else if the key value is greater than the current node
        else
           return rInsert(trav->right,newItem);
        }// end if

    //Else the an empty node has been encountered-- allocate and insert the node
    else
        {
        trav = Allocate();    //Allocate memory to the new node to insert
        trav->data = newItem; //Assign the data
        return true;          // The item was successfully inserted
        }// end else
    }// end InsertR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
bool BstClass<ItemType>::rDelete(/*in out*/node<ItemType>*& trav,//Node to check or delete
    /*in*/ KeyType key) // key to find
    {
    //If the node is not null -- end of branch
    if(trav != NULL)
        {
        node<ItemType>* temp = new node<ItemType>; // temporary node holds current value
        node<ItemType>* prev = new node<ItemType>; //temporary node holds previous value

        // If the key is less than the current node
        if(key < trav->data.key )
            return rDelete(trav->left,key);

        //Else if the key is greater than the current node
        else if 
            (key >trav->data.key )
            return rDelete(trav->right, key); 

        //Else the keys are equal
        else 
            {
            //If the node has no children
            if(trav->left == NULL && trav->right ==NULL)
                {
                delete trav;
                trav = NULL;
                return true;
                }// end if

            //Else if one left child
            else if(trav->left != NULL && trav->right == NULL) 
                {
                temp = trav;
                trav = trav->left;
                delete temp;
                return true;
                }//end else if

            //Else if one right child
            else if(trav->left == NULL && trav->right != NULL) 
                {
                temp = trav;
                trav = trav->right;
                delete temp;
                return true;
                }// end else if

            //Else if two children
            else 
                {
                prev = trav; //hold value of trav
                temp = trav->right; //temp val hold node to copy successor data to

                /*    Find Successor       */
                //While loop --iterates until trav is at the end of the left branch
                while(temp->left != NULL)
                    {
                    prev = temp;
                    temp = temp->left;
                    }// end while

                trav->data = temp ->data;  //Copy the successor data into the deleted key node
                rDelete(temp, temp->data.key); //Delete the successor from the structure

                // If prev and trav point to same node
                if(prev == trav)
                    prev->right= temp; //assign the right sub tree the successor

                //Else assign the left sub tree the successor
                else
                    prev->left = temp;

                return true; // Node was deleted
                }// end else
            }// end if trav->data == key
        }// end if trav != NULL

    //Else trav is null and thus the value was not found -- can not delete
    else
        return false;
    }// end Delete
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rInOrder(/*in*/node<ItemType>*& trav, //node to visit
    /*in*/FunctionType visit) //function pointer
    {
    //Traverse structure in LNR order
    if(trav!=NULL)
        {
        rInOrder(trav->left, visit);
        visit(trav->data);
        rInOrder(trav->right, visit);
        }//end if
    }// end rInOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rPreOrder(/*in*/node<ItemType>*& trav,//node to visit
    /*in*/FunctionType visit) //function pointer
    {  
    //Traverse structure in NLR order
    if(trav!=NULL)
        {
        visit(trav->data);
        rPreOrder(trav->left, visit);
        rPreOrder(trav->right, visit);
        }//end if
    }// end rPreOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rPostOrder(/*in*/node<ItemType>*& trav)//node to delete
    {
    //If trav is not NULL traverse the structure in LRN order 
    if(trav != NULL)
        {
        rPostOrder(trav->left);
        rPostOrder(trav->right);
        delete trav;
        }// end if
    }// end rPostOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rPreOrder(/*in*/node<ItemType>*& trav, //node to visit
    /*in*/FunctionType2 visit, //function pointer (allows output to file)
    /*in*/ofstream& dout) //output stream
    {
    //If trav is not NULL traverse the structure in NLR order 
    if(trav != NULL)
        {
        visit(trav->data, dout);
        rPreOrder(trav->left, visit,dout);
        rPreOrder(trav->right, visit, dout);
        }// end if
    }// end rPreOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rInOrderReverse(/*in*/node<ItemType>*& trav,//node to visit
    /*in*/FunctionType visit)// function pointer
    {
    //Traverse structure in RLN order
        if(trav!=NULL)
        {
        rInOrderReverse(trav->right, visit);
        visit(trav->data);
        rInOrderReverse(trav->left, visit);
        }//end if
    }// end rInOrderReverse
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rCopyHelper(/*in*/ node<ItemType>*& trav)// node to insert into tree
    {  
    //Traverse structure in NLR order
    if(trav!=NULL)
        {
        Insert(trav->data);     //Insert the data in trav to this bst
        rCopyHelper(trav->left);
        rCopyHelper(trav->right);
        }//end if
    }// end rCopyHelper
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
bool BstClass<ItemType>::rEqualHelper( /*in*/node<ItemType>*& trav) const //node of other tree
    {
    //Traverse structure in NLR order
    if(trav!=NULL)
        {

        //If the data at trav is found in this bst
        if(Find(trav->data.key))
            {
            rEqualHelper(trav->left);  //Check left
            rEqualHelper(trav->right); //Check right
            return true;
            }
        else
            return false;  //Value was not found in bst return false
        }//end if
    }// end rEqualHelper
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rPlusHelper(/*in*/node<ItemType>*& trav) // node of other bst
    {
    //Traverse structure in NLR order
    if(trav!=NULL)
        {
        //If the value is found continue looking for values
        if(Find(trav->data.key))
            {
            rPlusHelper(trav->left);
            rPlusHelper(trav->right);
            }// end if
        //Else the value was not found and should be inserted into the list
        else
            {
            Insert(trav->data);      //Insert then continue traversing
            rPlusHelper(trav->left);  
            rPlusHelper(trav->right);
            }
        }//end if
    }// end rPlusHelper
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
void BstClass<ItemType>::rAsterHelper(/*in*/node<ItemType>*& trav, // node of other bst
    /*in*/const BstClass<ItemType> bst) //another bst
    {
    //Traverse structure in NLR order
    if(trav!=NULL)
        {
        //If the value is found in both bsts
        if(Find(trav->data.key) && bst.Find(trav->data.key))
            {
            Insert(trav->data);            //Insert value into this list
            rAsterHelper(trav->left,  bst);
            rAsterHelper(trav->right, bst);
            }// end if
        //Else the value was not found in both bsts and should be deleted
        else
            {
            Delete(trav->data.key);       //Delete value 
            rAsterHelper(trav->left, bst);  
            rAsterHelper(trav->right, bst);
            }
        }//end if
    }// end rPreOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PROTECTED PR
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class ItemType>
node<ItemType>* BstClass<ItemType>::Allocate()
    {
     node<ItemType>* temp = new node<ItemType>; //Create a new node
     temp->right = NULL;  //set to null
     temp->left = NULL;   //set to null
     return temp;
    }// end Allocate
