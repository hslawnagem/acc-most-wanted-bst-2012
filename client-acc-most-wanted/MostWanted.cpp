/**********************************************************************************************
FILE NAME: MostWanted.cpp
AUTHOR: Megalotroid Clark Walsh
DATE: December 19, 2012
PURPOSE: 
            The MostWanted.cpp will run a database interface program updated by user input. The 
            database holds the names of criminals and their known attributes. The initial menu
            interface allows the user to add a criminal to this data base, perform an inquiry,
            or terminate the program. Once program is terminated the CRIME_DATA_FILE will be 
            updated with information added during the execution of the program.

            Upon choosing inquiry the user will be directed to a sub menu of the program which
            will provide the following functionality: 
            
                            Tip    -- To round down suspects based on a tip
                            Check  -- Allows user to search database for a suspect
                            Print  -- prints the contents of the inquiry to the screen and file
                            Quit   -- Quit the sub menu

            The Inquiry will automatically terminate once a single suspect has been identified 
            based on tip information.

            All database choices and relevant output will be echoed to PROGRAM_FILE with. Each
            execution of the program will rewrite this file.
            

ASSUMPTIONS:   
             The bstclass.h already includes the fstream library.
             Criminals can not be deleted from the database! Do not tamper with file! 
          
INPUT:      Upon starting the program the CRIME_DATA_FILE information will be loaded into the 
            database. 

            The database will be updated upon user input under the ADD command. Though this
            information will not be saved the the CRIME_DATA_FILE until program termination.


OUTPUT:     All user interactions: menu choices, console input, and printing request will be 
            echoed to the PROGRAM_FILE. Each execution of the program will rewrite this file.

            Upon termination of the program the CRIME_DATA_FILE will be updated if new
            criminals were added to the database.

SUMMARY OF FUNCTIONS:

    void UploadCriminalFile(BstClass<ItemType>& databaseUp);
    -- Upload criminal file to database

    void PrintMenu();
    -- Print the Main Menu to display options

    char MainMenuOption();
    -- Prompts, retrieves, and returns the menu option selected by user

    char InquiryMenuOption();
    --Prompts, retrieves, and returns the inquiry option selected by user

    void PrintDatabaseToFile( ItemType& item, ofstream& crimeFile);
    -- Print the contents of the database to the database input file 

    void PrintInquiryMenu();
    -- print the Inquiry Menu to display options

    char YesNoOption(string heading);
    -- Prompt, retrieves, and returns a yes or no selection from user

    void PrintSuspects(ItemType& item);
    -- prints a list of suspects to the console

    void PrintSuspectsEcho(ItemType& item, ofstream& echo);
    -- prints a list of suspects to the echo file

    void RoundDownSuspects(ItemType& item , DynListClass& suspectList,string& tip);
    -- creates a list of suspect names based on a tip entered by user
**********************************************************************************************/
//LIBRARIES___________________________________________________________________________________
#include "ItemType.h"     //Defines a criminal record
#include "bstclass.h"     //The criminal data structure
#include <iostream>       //For output to the system
using namespace std;

//CONSTANTS___________________________________________________________________________________
//I/O CONSTANTS
const string CRIME_DATA_FILE = "Criminal.dat"; //Database file name
const string PROGRAM_FILE = "Criminal.out";    //User program echo file name

//COMMAND CONSTANTS
//For output and echo output
const string ADD = "ADD";
const string INQUIRY = "INQUIRY";
const string TIP = "TIP";
const string CHECK = "CHECK";
const string PRINT = "PRINT";
const string QUIT = "QUIT";

//For selecting menu choice
const char M_ADD = 'A';
const char M_INQUIRY = 'I';
const char M_TIP = 'T';
const char M_CHECK = 'C';
const char M_PRINT = 'P';
const char M_QUIT = 'Q';
const char YES = 'Y';
const char NO =  'N';

//FUNCTION PROTOTYPES_________________________________________________________________________
void UploadCriminalFile(/*in out*/BstClass<ItemType>& databaseUp);
void PrintMenu();
char MainMenuOption();
char InquiryMenuOption();
void PrintDatabaseToFile( /*in*/ItemType& item, /*in out*/ofstream& crimeFile);
void PrintInquiryMenu();
char YesNoOption(/*in*/string heading);
void PrintSuspects(/*in*/ItemType& item);
void PrintSuspectsEcho(/*in*/ItemType& item, /*in out*/ofstream& echo);
void RoundDownSuspects(/*in out*/ItemType& item , /*in out*/DynListClass& suspectList,
    /*in*/string& tip);
//__________________________________________________________________________________________
void main()
    {
    //Local Variables
    BstClass<ItemType> database;         //Holds all criminal information
    BstClass<ItemType> inquiryDatabase;  //Database to be manipulated during inquiry
    BstClass<ItemType> suspectDatabase;  //Suspect database for rounding down the perp
    ofstream dout;                       //For output to CRIME_DATA_FILE
    ofstream echo;                       //For outputting user processes
    int initialDatabaseSize;             //Database size upon uploading data
    string consoleInput;                 //Holds a line of input from the console
    DynListClass suspectIDs;             //Holds a list of suspects found base don a tip
    ItemType crimer;                     //Criminal rec being processed
    char yesNo;                          //Hold yes or no menu option
    char mainOption;                     //Hold option for main menu
    char inquiryOpt;                     //Hold option for inquiry menu                     

    //Load values from CRIME_DATA_FILE
    UploadCriminalFile(database);                  

    //Initial length of database
    initialDatabaseSize = database.ReturnLength();  

    //Copy data base values to inquiry database
    inquiryDatabase = database; 

    //Open the echo file to output user choices
    echo.open(PROGRAM_FILE);

    do      /*                   Main Menu Loop                             */
        {
        system("cls");
        PrintMenu(); //Print the main menu

        mainOption = MainMenuOption();
        
        switch(mainOption)   //Main menu option
            {

        case M_ADD:  /*   Add a criminal to the database   */
            echo<<endl<<ADD<<endl;

            cout<< ADD <<endl<<"Name: "; //prompt
            echo <<"Name: ";

            getline(cin, consoleInput);  //Get criminals name

            echo <<consoleInput<<endl;; //Echo the user input

            crimer.key = consoleInput;  //Insert the input into a key

            //If the criminal is not found in the data base --OKAY to add
            if(!database.Find(crimer.key))
                {
                echo<<"Attributes: "<<endl;

                //Prompt user for an attribute
                yesNo = YesNoOption("Enter attribute? [Y/N] ");

                //While loop iterates until user enters blank line
                while(yesNo == YES)
                    {
                    cout<<endl;
                    echo<<endl;

                    //Prompt for an attribute
                    cout <<"Attribute: ";
                    getline(cin, consoleInput); //Get user input

                    crimer.attributes.Insert(consoleInput); //Insert into the criminal rec
                    echo << consoleInput<<endl; //echo the user input

                    //Prompt user for another attribute
                    yesNo = YesNoOption("Enter attribute? [Y/N] ");
                    }// end while

                database.Insert(crimer);   //Insert the criminal generated by user input
                crimer.attributes.Clear(); //Clear the attributes of the variable crimer
                }

            //Else the criminal is already in the database
            else
                {
                cout<< "The criminal already exist in the database" <<endl;
                echo<< "The criminal already exist in the database" <<endl;
                }// end else

            break; //######################################################################

        case M_INQUIRY:              
            echo<<endl<<INQUIRY<<endl;           
            /*
            Inquiry menu will appear on screen allowing user to make choices only
            available under the inquiry option. A user can check if a perp is in
            the data base, round down suspects based on a tip, or print the current
            list of possible suspects to the console and file.

            All output is echo printed.

            If a perp is found form a tip the Inquiry will automatically terminate
            */

            do      /*                    Inquiry menu Loop                             */
                {
                system("cls"); //Clear screen to display new Inquiry menu
                PrintInquiryMenu(); //Display the inquiry menu

                inquiryOpt= InquiryMenuOption(); //Get the inquiry menu option

                //Based on user input perform a function of Inquiry Menu
                switch(inquiryOpt) 
                    { 
                case M_TIP:       // Using a tip reduce the # of suspects
                    echo <<endl<< TIP <<endl;

                    //Get the inquiry name
                    cout<<endl<<"Enter an inquiry code name: "<<endl<<endl;
                    echo<<endl<<"Enter an inquiry code name: "<<endl<<endl;

                    getline(cin,consoleInput); //Get the inquiry code name
                    echo <<consoleInput<<endl; //Echo the name to the file

                    //User is asked if they would like to enter a tip to initialize loop
                    yesNo= YesNoOption("Enter Tip? [Y/N] ");

                    //While loop iterates until user selects NO or the suspect list is 
                    //less == or less than 1
                    while(yesNo == YES && inquiryDatabase.ReturnLength() > 1)
                        {
                        //Prompt user for the tip
                        cout<<endl<<"Enter a tip to search for a suspect." <<endl<<endl;
                        echo<<endl<<"Enter a tip to search for a suspect." <<endl<<endl;

                        getline(cin,consoleInput);  //Get tip entered by user

                        echo << consoleInput<<endl; //Echo the tip

                        //Create a list of suspects who correspond to the tip
                        inquiryDatabase.PreOrder(RoundDownSuspects,suspectIDs,consoleInput);

                        suspectIDs.FirstPosition(); //Go to first position in id list

                        //Insert all found IDs into the suspectDatabase
                        while(!suspectIDs.EndOfList())
                            {
                            //Assign all records of the perp to crimer
                            crimer = inquiryDatabase.Retrieve(suspectIDs.Retrieve());

                            suspectDatabase.Insert(crimer);// Insert the crimer as a suspect

                            suspectIDs.NextPosition();//Go the next perp
                            }// end while

                        inquiryDatabase = suspectDatabase; //Assign the suspects to inquiry

                        suspectDatabase.Clear(); //Clear the suspect database for

                        suspectIDs.Clear(); //Clear the suspects list generated by the tip

                        //User is asked if they would like to enter a tip 
                        yesNo= YesNoOption("Enter Tip? [Y/N] ");

                        }// end while

                    //If there were no matches to the tip
                    if(inquiryDatabase.ReturnLength() == 0)
                        {
                        cout<<endl<< "Bad Tip. No suspects exist."<<endl;
                        echo<<endl<< "Bad Tip. No suspects exist."<<endl;
                        }// end if

                    //Else if one suspect remains
                    else if (inquiryDatabase.ReturnLength() == 1)
                        {
                        cout<<endl<<"Perp found! Good job detective!" <<endl;
                        echo<<endl<<"Perp found! Good job detective!" <<endl;

                        //Prints suspects to console
                        inquiryDatabase.PreOrder(PrintSuspects); 
                        //Prints suspects to file
                        inquiryDatabase.PreOrder(PrintSuspectsEcho, echo); 

                        inquiryOpt = M_QUIT; //Terminates the current inquiry
                        }// end else if

                    inquiryDatabase = database; //Reinitialize the database with all perps
                    system("pause"); //Pause screen for review
                    break; //===============================================================

                case M_CHECK:   //Search for criminal by name in the database
                    echo <<endl<<CHECK<<endl;

                    cout <<"Enter Criminal Name: ";  //Prompt
                    getline(cin, crimer.key);        //Get user input

                    //If the criminal exists
                    if(database.Find(crimer.key))
                        {
                        cout<< crimer.key <<" is in the criminal database"<<endl;
                        echo<< crimer.key <<" is in the criminal database"<<endl;
                        }// end if

                    //Else the criminal was not found in the database
                    else
                        {
                        cout << crimer.key<<" is not a criminal...yet"<<endl;
                        echo << crimer.key<<" is not a criminal...yet"<<endl;
                        }// end else

                    system("pause"); //Pause screen to reflect on this information
                    break; //==============================================================

                case M_PRINT:    //Print the suspects currently in the inquiry database
                    echo<<PRINT<<endl;

                    //Prints suspects to console
                    inquiryDatabase.PreOrder(PrintSuspects); 
                    //Prints suspects to file
                    inquiryDatabase.PreOrder(PrintSuspectsEcho, echo); 

                    system("pause"); //pause so user can review console
                    break;//==============================================================
 
                case M_QUIT:
                    echo<<endl<<QUIT<< " inquiry menu"<<endl; // Quit the inquiry menu
                    break;//==============================================================

                    }// end inquiry switch
                }while(inquiryOpt != M_QUIT);

                break; //#################################################################

        case M_QUIT: 
            echo<<endl<<QUIT << " main menu"<<endl;
            break;//######################################################################

            }// end Main Menu Switch
        }while(mainOption != M_QUIT); //end main Menu

        //Termination Details...

        
        dout.open(CRIME_DATA_FILE); //Open the database file to overwrite

        //Print the data to the file
        database.PreOrder(PrintDatabaseToFile, dout); 

        dout.close(); //Close the output stream
 
        echo.close(); //Close the PROGRAM_FILE
    }// end main

//                           Function Definitions
/****************************************************************************
Purpose: Display main Menu Options
Pre: N/A
Post: Menu is displayed to console
****************************************************************************/
void PrintMenu()
    {
    cout<<"???????????????????????????????????????????????????????"<<endl;
    cout<<"?                   CRIMINAL DATABASE                 ?"<<endl;
    cout<<"?                                                     ?"<<endl;
    cout<<"?                      Menu Options                   ?"<<endl;
    cout<<"?      (I)nquiry -- Perform inquiry on database       ?"<<endl;
    cout<<"?      (A)dd     -- Add a new criminal to database    ?"<<endl;
    cout<<"?      (Q)uit    -- Exit the Criminal Database        ?"<<endl;
    cout<<"???????????????????????????????????????????????????????"<<endl; 
    }// end PrintMenu
/****************************************************************************
Purpose: Display Inquiry Options
Pre: N/A
Post: Inquiry menu is displayed to console
****************************************************************************/
void PrintInquiryMenu()
    {
    cout<<"???????????????????????????????????????????????????????"<<endl;
    cout<<"?                     INQUIRY MENU                    ?"<<endl;
    cout<<"?                                                     ?"<<endl;
    cout<<"?                     Menu Options                    ?"<<endl;
    cout<<"?   (T)ip   -- Find the suspects based on a great tip ?"<<endl;
    cout<<"?   (C)heck -- Look up suspects criminal record       ?"<<endl;
    cout<<"?   (P)rint -- Print the list of suspected evil doers ?"<<endl;
    cout<<"?   (Q)uit  -- Quit the inquiry                       ?" <<endl;
    cout<<"???????????????????????????????????????????????????????"<<endl;   
    }// end PrintInquiryMenu
/****************************************************************************
Purpose: Get the menu option from the user
Pre:  User should be able to see options, strings are valid input if first 
      character is a valid menu option.
Post: A menu option will be returned based on input
****************************************************************************/
char MainMenuOption()
    {
    char menuOpt;         // menuOpt to return
    string consoleInput;  //Input string from console
    bool goodOpt = false; //Assume the menu pick is bad
     
    //While the input is not valid
    while(!goodOpt)
        {
        cout<< "Enter Menu Option: "; //Prompt
        getline(cin, consoleInput);   

        menuOpt = consoleInput[0]; //Assign menuOpt first character

        menuOpt= toupper(menuOpt); //Convert option to uppercase

        //If the menu option is one of the valid options
        if(menuOpt == M_ADD || menuOpt== M_INQUIRY || menuOpt == M_QUIT)
            goodOpt = true;

        //If they didn't get it right
        if(!goodOpt)
            {
            cout << "Please enter a valid character for your menu choice";
            cout <<endl<<endl<< "EXAMPLE:"<<endl;
            cout<< "Enter Inquiry Option: P"<<endl <<endl;
            }// end if

        cin.clear();
        }//end while  

    return menuOpt;
    }// end MainMenuOption
/****************************************************************************
Purpose: Get the inquiry menu option from the user
Pre:  User should be able to see options, strings are valid input if first 
      character is a valid menu option.
Post: A menu option will be returned based on input
****************************************************************************/
char InquiryMenuOption()
    {
    char menuOpt;          // menuOpt to return
    string consoleInput;   //Input string from console
    bool goodOpt = false;  //Assume the menu pick is bad

    //While the input is not valid
    while(!goodOpt)
        {
        cout<< "Enter Inquiry Option: "; //Prompt
        getline(cin, consoleInput);

        menuOpt = consoleInput[0]; //Assign menuOpt first character

        menuOpt= toupper(menuOpt); //Convert input to uppercase

        //If the menu option is one of the valid options
        if(menuOpt == M_TIP || menuOpt== M_PRINT || menuOpt == M_CHECK||
            menuOpt == M_QUIT )
            goodOpt = true;

        //If they didn't get it right
        if(!goodOpt)
            {
            cout << "Please enter a valid character for your menu choice";
            cout <<endl<<endl<< "EXAMPLE:"<<endl;
            cout<< "Enter Inquiry Option: A"<<endl <<endl;
            }// end if

        cin.clear();
        }//end while   
    return menuOpt;
    }//end InquiryMenuOption
/****************************************************************************
Purpose: Get a yes or no choice from user.
Pre:  User should be able to see options, strings are valid input if first 
      character is a valid menu option.
Post: A menu option will be returned based on input
****************************************************************************/
char YesNoOption(/*in*/string heading) //Yes or No question to prompt user
    {
    char opt;             // menuOpt to return
    string consoleInput;  //Input string from console
    bool goodOpt = false; //Assume the menu pick is bad

    //While the input is not valid
    while(!goodOpt)
        {
        cout<< heading;   //cout the question to ask user
        getline(cin, consoleInput);

        opt = consoleInput[0]; //Assign opt the first character

        opt= toupper(opt); //Convert input to uppercase

        //If the menu option is one of the valid options
        if(opt == YES || opt == NO )
            goodOpt = true;

        //If they didn't get it right
        if(!goodOpt)
            cout << "Please enter Y for YES or N for NO" <<endl;
    
        }//end while   

    cin.clear();
    return opt;
    }//end YesNoOption
/****************************************************************************
Purpose: Populate the DynListClass suspectList with key fields of suspected
         criminals based on a tip --user input 
Pre:     suspectList must be empty 
Post:    the suspectList will be populated with the keys of possible perps
****************************************************************************/
void RoundDownSuspects(/*in out*/ItemType& item, // item to search
    /*in out*/DynListClass& suspectList, //list to add suspect too if ==tip
    /*in out*/string& tip) //tip to compare suspect attributes to
    {
    item.attributes.FirstPosition(); //Go to first position of list
    string perpID = item.key; //string to hold perp ID for inserting into list

    //While loop iterates through all of a suspects attributes
    while(!item.attributes.EndOfList())
        {
        //If the attribute is the same as the tip --add them to the list!
        if(item.attributes.Retrieve() == tip)
            {
            suspectList.Insert(perpID);
            break;
            }// end if

        item.attributes.NextPosition(); //go to next attribute
        }// end while
    }// end Round DownSuspects
/****************************************************************************
Purpose: Output the the database to an output file
Pre: For use with a recursive bst data structure, needs function pointer
Post: The database will be output to the PROGRAM_FILE
****************************************************************************/
void PrintSuspectsEcho(/*in out*/ItemType& item, // Item to echo
    /*in out*/ofstream& echo)//output stream to send output to
    {
    echo<<item.key<<endl; //print suspect id

    item.attributes.FirstPosition(); //first position of attribute list

    //while not at the end of the attribute list
    while(!item.attributes.EndOfList())
        {
        echo << item.attributes.Retrieve()<<endl;  //print attribute
        item.attributes.NextPosition();  //go to next position
        }// end while
    echo<<endl;
    }// end PrintSuspectsEcho
/****************************************************************************
Purpose: Output database to the console
Pre: For use with a recursive bst data structure, needs function pointer
Post: The database will be output to the screen
****************************************************************************/
void PrintSuspects(/*in*/ItemType& item) //item to output to console
    {
    cout<<item.key<<endl; //print suspect id

    item.attributes.FirstPosition(); //first position of attribute list

    //while not at the end of the attribute list
    while(!item.attributes.EndOfList())
        {
        cout << item.attributes.Retrieve()<<endl; //print attribute
        item.attributes.NextPosition();     //go to next position
        }// end while
    cout<<endl;
    }//End PrintSuspects
/****************************************************************************
Purpose: Upload data from the CRIME_DATA_FILE into database

Pre: This function assumes the first name is the first field of input
     All following fields are attributes until a blank line in encountered.
     Blank lines are skipped, function repeats until eof is encountered.

Post: The database will be populated with values from an input file
****************************************************************************/
void UploadCriminalFile(/*in out*/BstClass<ItemType>& databaseUp)//database 
    {
    ifstream crimeFile (CRIME_DATA_FILE);    //For crime data base input   
    string input;                            //input string from file
    ItemType ttlCrimer;                      //criminal file to build&insert

    getline(crimeFile, input); //get input

    //While loop iterates until the end of the file
    while(!crimeFile.eof())
        {
        //First line of input is assumed to be the criminals name
        ttlCrimer.key = input;

        getline(crimeFile, input); //get line of input 

        //While input is not assign "" add the following lines as
        //criminal attributes
        while(input != "")
            {   
            ttlCrimer.attributes.Insert(input); //Insert the input
            getline(crimeFile, input);                 
            }// end while

        databaseUp.Insert(ttlCrimer); //Insert the criminal

        ttlCrimer.attributes.Clear(); //Clear the attributes to be re written

        getline(crimeFile, input);//Get the next criminals name
        }// end while    

    crimeFile.close(); // Case Closed!
    }// end UploadCriminalFile
/****************************************************************************
Purpose: Output the values of the database to an output file
Pre: ofstream must be opened and associated with file in main
     ofstream must also be closed in main proceeding the function call
Post: The database will be sent to the specified output file in the same 
      format that it was read in
****************************************************************************/
void PrintDatabaseToFile(/*in out*/ ItemType& item, // item to print to file
    /*in out*/ofstream& crimeFile)// output stream to send output
    {
    crimeFile << item.key<<endl; //Output the key value

    item.attributes.FirstPosition(); //Go to the position of the first attribute

    //Print attributes until end of list is reached
    while(!item.attributes.EndOfList())
        {
        crimeFile <<item.attributes.Retrieve()<<endl;
        item.attributes.NextPosition();
        }//end while
    crimeFile <<endl; //output blank line to separate data
    }//Update CriminalFile

