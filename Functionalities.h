#include <iostream>
#include "FordFulkerson.h"
#include "MST.h"
using namespace std;
#ifndef START_FUNCTIONALITIES_H
#define START_FUNCTIONALITIES_H
#if defined(_WIN32) || defined(_WIN64)
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif
bool endOfProgram= false;
bool backToTheMainMenu=false;


bool checkBack(){
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Back to the main menu\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            backToTheMainMenu = true;
    }while(back!=1 && back!=2);
    return (back==2);
}

/*
 Checkback() function is used all over the other options to check if the user wants to either go back to the previous menu or to go back to the main menu
 It's only used of there exists a previous menu not the main menu
 */
bool checkClose(){
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Close the program\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            endOfProgram = true;
    }while(back!=1 && back!=2);
    return (back==2);
}

/////////////////////////////////////////
///////// Ford Fulkerson functions //////
/////////////////////////////////////////
void ViewMaxFlow(vector<vector<int> >capacity){
    int source,sink;
    cout<<"Please enter the source index: ";
    cin>>source;
    cout<<"Please enter the sink index: ";
    cin>>sink;
    cout<<"The maximum flow to point "<<sink<<" from point "<<source<<" is :"<<ford_fulkerson(capacity,source,sink)<<endl;
}
/////////////////////////////////////////
///////// MST functions /////////////////
/////////////////////////////////////////
void BuildMst(){
    vector<vector<int>> graph;
    cout<<"Please enter the graph to build: ";
    cout<<"[1] Traffic Management "<<endl
        <<"[2] Power Network "<<endl
        <<"[3] DC Network "<<endl;
    //kruskalMST(n,graphtype);
}

void printHeader(){
    cout << "Welcome to our Smart City Project. Please choose one of the following options:" << endl;
}

void printMainMenu(){
    cout<<"[1] Traffic Management "<<endl
        <<"[2] Power Network "<<endl
        <<"[3] DC Network "<<endl
        <<"[4] View City map "<<endl
        <<"[5] Credits "<<endl;
}

void printExit(){
    system(CLEAR_COMMAND.c_str()); //clear screen
    cout<<"--------------------------------------------Thanks for using our program---------------------------------------------\n\n";
    cout<<"-------------------------------------------------------Credits-------------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Salah eldin Elsayed------------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Hussein Sayed---------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Abdulrahman Abogendia----------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Fouad Hashesh---------------------------------------------------\n\n";
    cout<<"-------------------------------------Under the Supervision of Dr. Hala Zayed------------------------------------\n\n";
    cout<<"---------------------------------------------------------&-----------------------------------------------------\n\n";
    cout<<"----------------------------------------------------Eng. Rameez------------------------------------------------\n\n";

}
void printTrafficMenu(){
    cout<<"[1] View shortest path "<<endl
        <<"[2] View maximum flow "<<endl
        <<"[3] View Emergency route "<<endl // ford fulkerson
        <<"[4] Build Road Network "<<endl
        <<"[5] View map "<<endl;
}
void printPowerMenu(){
    cout<<"[1] View shortest path "<<endl
        <<"[2] View maximum flow "<<endl
        <<"[3] View Emergency route "<<endl // floyd warshall
        <<"[4] Build Power Network "<<endl
        <<"[5] View map "<<endl;
}
void printNetworkMenu(){
    cout<<"[1] View shortest path "<<endl
        <<"[2] View maximum flow "<<endl
        <<"[3] View Emergency route "<<endl // floyd warshall
        <<"[4] Build Network Network "<<endl
        <<"[5] View map "<<endl;
}

void TrafficMenu(){
    short choice;
    do{
        system(CLEAR_COMMAND.c_str()); //clear screen
        cout<<"===Traffic Management menu=== "<<endl;
        printTrafficMenu();
        cout<<"Enter your choice : ";
        cin>>choice;
        if (choice<1 || choice > 5) {
            continue;
        }
        if (choice == 1) {
            //A*menu
        }
        else if (choice == 2) {
            //ViewMaxFlow();
        }
        else if (choice==3){
            //ViewEmergencyMenu;
        }
        else if (choice==4){
            //BuildMSTMenu
        }
        else if (choice==5){
            //printMap
        }
        if(choice>0 && choice<7)
            checkBack();    //check if the user want to back to the last menu

    }while(!backToTheMainMenu); //check if the user want to back to the main menu
}

void mainmenu(){
    printHeader();
    short choice=1;
    do{
        system(CLEAR_COMMAND.c_str()); //clear screen
        printMainMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice==1)
            TrafficMenu();
        if (choice==2)
            //DCmenu();
        if (choice==3)
            //Networkmenu();
        if (choice==4)
            //emergencymenu();
        system(CLEAR_COMMAND.c_str()); //clear screen
        if(backToTheMainMenu) { //check if the user want to back to the main menu
            choice = 1;
            backToTheMainMenu=false;
        }
        if(endOfProgram)    //if the user want to end the program
            break;
    }while(choice!=5);
    printExit();
    system("pause>0");

}


#endif //START_FUNCTIONALITIES_H
