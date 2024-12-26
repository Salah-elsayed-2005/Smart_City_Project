#include <iostream>

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

void printHeader(){
    cout << "Welcome to our Smart City Project. Please choose one of the following options:" << endl;
}

void printMainMenu(){
    cout<<"[1] Traffic Management : "<<endl
        <<"[2] Power Network : "<<endl
        <<"[3] DC Network : "<<endl
        <<"[4] View City map : "<<endl;
}

void printExit(){
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
    cout<<"[1] View shortest path : "<<endl
        <<"[2] View maximum flow : "<<endl
        <<"[3] View Minimum cost Graph : "<<endl
        <<"[4] Build Road Network"<<endl
        <<"[5] View map"<<endl;
}
void printPowerMenu(){
    cout<<"[1] View shortest path : "<<endl
        <<"[2] View maximum flow : "<<endl
        <<"[3] View Minimum cost Graph : "<<endl
        <<"[4] Build Power Network"<<endl
        <<"[5] View map"<<endl;
}
void printNetworkMenu(){
    cout<<"[1] View shortest path : "<<endl
        <<"[2] View maximum flow : "<<endl
        <<"[3] View Minimum cost Graph : "<<endl
        <<"[4] Build Network Network"<<endl
        <<"[5] View map"<<endl;
}


#endif //START_FUNCTIONALITIES_H
