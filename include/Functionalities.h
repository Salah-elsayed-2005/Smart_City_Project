#include <iostream>
#include <thread>
#include "FordFulkerson.h"
#include "MST.h"
using namespace std;
#ifndef START_FUNCTIONALITIES_H
#define START_FUNCTIONALITIES_H


bool endOfProgram= false;
bool backToTheMainMenu=false;


void checkBack(){
    backToTheMainMenu=false;
    short back;
    do {
        cout << "\n\n[1] Back to the last page\n"
            << "[2] Back to the main menu\n\n";
        cout << "Please Enter Your Choice : ";
        cin >> back;
        if (back == 2) backToTheMainMenu = true;
    }while(back!=1 && back!=2);
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
    //cout<<"The maximum flow to point "<<sink<<" from point "<<source<<" is :"<<ford_fulkerson(capacity,source,sink)<<endl;
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
    cout << "============================== Welcome To The Smart City ==================================\n" << endl;
}

void printMainMenu(){
    cout<<"[1] Traffic Management "<<endl
        <<"[2] Power Network "<<endl
        <<"[3] DC Network "<<endl
        <<"[4] View City map "<<endl
        <<"[5] Exit "<<endl;
}

void printExit(){
    system("cls");
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
        <<"[2] View Emergency route "<<endl // ford fulkerson
        <<"[3] View map "<<endl
        <<"[4] Back";
}

void printPowerMenu(){
    cout<<"[1] View Emergency route "<<endl // floyd warshall
        <<"[2] Build Power Network "<<endl
        <<"[3] View map "<<endl
        <<"[4] Back";
}

void printNetworkMenu(){
    cout<<"[1] View Emergency route "<<endl // floyd warshall
        <<"[2] Build Power Network "<<endl
        <<"[3] View map "<<endl
        <<"[4] Back";
}

void TrafficMenu(){
    short choice;
    do{
        system("cls");
        cout<<"========================= Traffic Management Menu ============================ "<<endl;
        printTrafficMenu();
        cout<<"\nEnter Your Choice : ";
        cin>>choice;
        if (choice<1 || choice > 4) {
            continue;
        }
        if (choice == 1) {
            //A*menu
        }
        else if (choice == 2) {
            //ViewEmergencyMenu;
        }
        else if (choice==3){
            //printMap
        }
        else if(choice==4){
            break;
        }
        if(choice>0 && choice<5)
            checkBack();    //check if the user want to back to the last menu

    }while(!backToTheMainMenu); //check if the user want to back to the main menu
}

void PowerMenu(){
    short choice;
    do{
        system("cls");
        cout<<"========================= Power Network Menu ============================ "<<endl;
        printPowerMenu();
        cout<<"\nEnter Your Choice : ";
        cin>>choice;
        if (choice<1 || choice > 4) {
            continue;
        }
        if (choice == 1) {
            //EmergencyMenu
        }
        else if (choice == 2) {
            //BuildMST;
        }
        else if (choice==3){
            //ViewMap;
        }
        else if(choice==4){
            break;
        }
        if(choice>0 && choice<5)
            checkBack();    //check if the user want to back to the last menu

    }while(!backToTheMainMenu); //check if the user want to back to the main menu
}

void DCNetworkMenu(){
    short choice;
    do{
        system("cls");
        cout<<"========================= DC Network Menu ============================ "<<endl;
        printNetworkMenu();
        cout<<"\nEnter Your Choice : ";
        cin>>choice;
        if (choice<1 || choice > 4) continue;

        if (choice == 1) {
            //EmergencyMenu
        }
        else if (choice == 2) {
            //BuildMST;
        }
        else if (choice==3){
            //ViewMap;
        }
        else if(choice==4){
            break;
        }
        if(choice>0 && choice<5)
            checkBack();    //check if the user want to back to the last menu

    }while(!backToTheMainMenu); //check if the user want to back to the main menu
}

void mainmenu(){
    printHeader();
    this_thread::sleep_for(chrono::seconds(1));
    short choice;
    do{
        system("cls");
        printMainMenu();
        cout<<"\nPlease Enter Your Choice : ";
        cin>>choice;

        if(choice<1 || choice>5) continue;

        if (choice==1)
            TrafficMenu();
        else if (choice==2)
            PowerMenu();
        else if (choice==3)
            DCNetworkMenu();
        if (choice==4)
            //ViewCityMap();

        if(backToTheMainMenu) { //check if the user want to back to the main menu
            backToTheMainMenu=false;
        }
        if(endOfProgram)    //if the user want to end the program
            break;
    }while(choice!=5);

    printExit();
    system("pause>0");
}


#endif //START_FUNCTIONALITIES_H
