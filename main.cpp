// Libraries
#include <iostream>
#include <cmath>
#include <unistd.h>

using namespace std;

// Method Initialization
int welcome_screen();

int main() {
    system("cls");
    if(welcome_screen()){
        return 0;
    }
    return 0;
}

int welcome_screen(){
    cout << "ChatNetwork 1.0\n";
    cout << "Developed by Engr. Eugene Oca\n";
    sleep(1);
    cout << "Loading...\n";
    sleep(1);
    cout << "Gathering system information...\n";
    sleep(1);
    if(system("ver")){
        cout << system("ver\n");
    }else if(_WIN64 && _WIN32){
        cout << "64-bit WINDOWS\n";
    }else if(_WIN32){
        cout << "32-bit WINDOWS\n";
    }else{
        cout << "Please consider using WINDOWS Operating System.\n";
        return 1;
    }
    return 0;
}