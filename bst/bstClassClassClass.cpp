
/**********************************************************************************************************
FILE NAME: bstClass.cpp
AUTHOR: Megan Walsh
DATE: Dec 7 2012
PURPOSE: LAST DAMN PROJECT
**********************************************************************************************************/
#include "bstclass.h"


///*template <class ItemType>*/ 
//struct node
//    {
//    ItemType data;
//    node* left;
//    node* right;
//    };
//============================================================================================
/*template <class ItemType>*/
BstClass/*<ItemType>*/::BstClass()
    {
    
     root = NULL;
     
    }// end Default Con.
//////============================================================================================
///////*template <class ItemType>*/
//////~BstClass()   
//////============================================================================================
/////*template <class ItemType>*/
////BstClass/*<ItemType>*/::BstClass(const BstClass& orig)  
////    {
////    root = NULL;
////    operator=(orig);
////    }// end Copy Con
//============================================================================================
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::IsEmpty() const
    {
    return (root == NULL);
    }// End IsEmpty

//============================================================================================
///*template <class ItemType>*/
bool BstClass/*<ItemType>*/::IsFull() const
    {
    return false;
    }// End IsFull

//============================================================================================
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::InOrder(FunctionType visit)
    {
    //Traverse stucture in LNR order
    rInOrder(root, visit);
    
    }// end rInOrder

//============================================================================================
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::PreOrder(FunctionType visit)
    {
    
    //Traverse structure in NLR order
    rPreOrder(root, visit);

    }// end rPreOrder

//============================================================================================
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::InOrderReverse(FunctionType visit)
    {
    //Traverse structure in RLN order
        rInOrderReverse(root, visit);
    
    }// end rInOrderReverse


//============================================================================================
/*template <class ItemType>*/
ItemType BstClass/*<ItemType>*/::Retrieve(KeyType key) const
    {
    return rRetrieve(root, key);
    }// end Retrieve
//============================================================================================
/////*template <class ItemType>*/
////int ReturnLength() const
////    {
////   
////    
////    }// end return length
//============================================================================================
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::Find(KeyType key) const
    {
    return rFind(root, key);
    }

//============================================================================================
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::Insert(ItemType newItem)
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
        node/*<ItemType>*/ *trav = root;
        return rInsert(root,newItem);
        }// end else
    //Do I have to worry about not all paths retrun value warning?
    }// end Insert

//============================================================================================
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::Delete(KeyType key)
    {
     if(root != NULL )
        return rDelete(root, key);
     else
         return false;
       
    
    }// end Delete
////============================================================================================
///*template <class ItemType>*/
//void BstClass/*<ItemType>*/::Clear()
//    {}//end Clear
//
////============================================================================================
///*template <class ItemType>*/
//virtual void operator = (const BstClass& orig)
//    {}// end op =
//
////============================================================================================
///*template <class ItemType>*/
//virtual bool operator ==(const BstClass& rtOp) const
//    {}
////============================================================================================
///*template <class ItemType>*/
//virtual BstClass/*<ItemType>*/ operator + (const BstClass& rtOp) const
//    {}
////============================================================================================
///*template <class ItemType>*/
//virtual BstClass/*<ItemType>*/ operator * (const BstClass& rtOp) const
//    {}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//============================================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
ItemType BstClass/*<ItemType>*/::rRetrieve(node/*<ItemType>*/* trav, KeyType key) const
    {
     
    if(trav != NULL)
        {
         if(key == trav->data.key)
            return trav->data;

        //Else if the key is less than the node --move left
        else if( key < trav->data.key)
            return rRetrieve(trav->left , key);

        //Else the key is greater than the node --move right
        else if( key > trav->data.key)
            return rRetrieve(trav->right, key);

        }//end if

    //Else the value is not in the structure --return a record with a sentinel value
    else
        {
        node/*<ItemType>*/* sentVal= new node/*<ItemType>*/;
        

        sentVal->data.key = SENT_RETRIEVE_VAL;

        return sentVal->data; //Return an Item with a sentinel value
        }// end else
     
    }// end rRetrieve


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::rFind(node/*<ItemType>*/* trav, KeyType key) const
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
        else if( key > trav->data.key)
            return rFind(trav->right, key);

        }// end if

    //Else a null node has been reached indicating the value was not found -- return false
    else
        return false;
    }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
bool BstClass/*<ItemType>*/::rInsert(node/*<ItemType>*/*& trav, ItemType newItem)
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
        trav = Allocate();
        trav->data = newItem;
        return true; // The item was succesfully inserted
        }// end else
    }// end InsertR

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            /*template <class ItemType>*/
            bool BstClass/*<ItemType>*/::rDelete(node/*<ItemType>*/*& trav, KeyType key)
                {
                //If the node is not null -- end of branch
                if(trav != NULL)
                    {

                    node/*<ItemType>*/* temp ; // temporary node holds old val

                    if(trav->data.key == key)
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
                            temp = trav; // asign val of trav to temp

                            trav= trav->left;
                            temp->data = trav->data; //copy data from left node to the node to delete

                            //Delete copied node
                            rDelete(temp ->left, trav->data.key); 
                            }//end else if

                        //Else if one right child
                        else if(trav->left == NULL && trav->right != NULL) 
                            {
                            temp = trav;
                            trav= trav->right;
                            temp->data = trav->data; //copy data from left node to the node to delete

                            //Delete copied node
                            rDelete(temp->right, trav->data.key); 
                            }// end else if

                        //Else if two children
                        else if(trav->left != NULL && trav->right != NULL) 
                            {
                            temp = trav; //temp val hold node to copy succesor data to

                            //    Find Successor

                            trav = trav->right; //Go to right node

                                //While loop --iterates until trav is at the end of the left branch
                            if(trav->left != NULL)
                                {
                                while(trav != NULL)
                                    trav = trav->left;
                                }
 

                            temp->data = trav ->data; //Copy the successor data into the deleted key node

                            //Delete the successor from the structure
                            rDelete(temp->right, trav->data.key);

                            return true;
                            }
                        }// end if trav->data == key

                    else if(trav->data.key > key)
                        rDelete(trav->left, key); 

                    else
                        rDelete(trav->right,key);
                    }// end if trav != NULL

                else
                    return false;

                }// end Delete

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::rInOrder(node/*<ItemType>*/*& trav,FunctionType visit)
    {
    //Traverse stucture in LNR order
    if(trav!=NULL)
        {
        rInOrder(trav->left, visit);
        visit(trav->data);
        rInOrder(trav->right, visit);
        }//end if
    
    }// end rInOrder

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::rPostOrder(node/*<ItemType>*/*& trav)
    {
    //If trav is not NULL traverse the stucture in LRN order 
    if(trav != NULL)
        {
        rPostOrder(trav->left);
        rPostOrder(trav->right);
        delete trav;
        }// end if
    }// end rPostOrder

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::rPreOrder(node/*<ItemType>*/*& trav,FunctionType visit)
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
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::rPreOrder(node/*<ItemType>*/*& trav,FunctionType visit, ofstream& dout)
    {
    //If trav is not NULL traverse the stucture in LRN order 
    if(trav != NULL)
        {
        visit(trav->data);
        rPreOrder(trav->left, visit);
        rPreOrder(trav->right, visit);
        }// end if
    }// end rPostOrder
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
void BstClass/*<ItemType>*/::rInOrderReverse(node/*<ItemType>*/*& trav,FunctionType visit)
    {
    //Traverse structure in RLN order
        if(trav!=NULL)
        {
        rPreOrder(trav->right, visit);
        visit(trav->data);
        rPreOrder(trav->left, visit);
        }//end if
    
    }// end rInOrderReverse

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*template <class ItemType>*/
node/*<ItemType>*/* BstClass/*<ItemType>*/::Allocate()
    {
     node/*<ItemType>*/* temp = new node /*<ItemType>*/;
     temp->right = NULL;
     temp->left = NULL;
     return temp;
    }// end Allocate

