// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

// Method Initialization
int welcome_screen();
string getIPAddress();
string getSubnet();

// Global Variables
string client_ip;
string client_subnet;
int port = 2000;

int main() {
    system("cls");
    if(welcome_screen()){
        return 0;
    }
    return 0;
}

int welcome_screen(){
    cout << "ChatNetwork 1.0\n";
    cout << "Developed by Eugene Oca\n";
    sleep(1);
    cout << "Loading...\n";
    sleep(1);
    cout << "Gathering system information...\n";
    sleep(1);

    // Get OS Version
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

    // Get Client LAN Interface Properties
    client_ip      = getIPAddress();
    client_subnet  = getSubnet();
    cout << "Client IP:\t" << getIPAddress() << "\n";
    cout << "Client Subnet:\t" << getSubnet() << "\n";
    system(("ping "+client_ip).c_str());
    cout << "Ready.\n";
    sleep(1);
    system("cls");
    return 0;
}

string getIPAddress(){
    system("ipconfig > ip.db");
    string container;
    ifstream IPConfig;
    int offset;
    string search = "IPv4 Address";
    IPConfig.open("ip.db");
    if(IPConfig.is_open()){
        while(!IPConfig.eof()){
            getline(IPConfig, container);
            if((offset = container.find(search)) != string::npos){
                container.erase(0, container.find(":") + 2);
                return container; 
                IPConfig.close();
                remove("ip.db");
            }
        }
    }
    IPConfig.close();
    remove("ip.db");
    return "Not Assigned";
}

string getSubnet(){
    system("ipconfig > ip.db");
    string container;
    ifstream IPConfig;
    int offset;
    string search = "Subnet Mask";
    IPConfig.open("ip.db");
    if(IPConfig.is_open()){
        while(!IPConfig.eof()){
            getline(IPConfig, container);
            if((offset = container.find(search)) != string::npos){
                container.erase(0, container.find(":") + 2);
                IPConfig.close();
                remove("ip.db");
                return container; 
            }
        }
    }
    IPConfig.close();
    remove("ip.db");
    return "Not Assigned";
}