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
int settings();

// Global Variables
string client_ip;
string client_subnet;
int port = 2000;

string username;
string server_ip;
string server_password;

int main() {
    system("cls");
    if(welcome_screen()){
        return 0;
    }
    if(settings()){
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
    cout << "Testing client connectivity...\n";
    system(("ping " + client_ip + " > test.db").c_str());
    string container;
    ifstream Connectivity;
    int offset;
    string search = "Request timed out";
    Connectivity.open("test.db");
    if(Connectivity.is_open()){
        while(!Connectivity.eof()){
            getline(Connectivity, container);
            if(((offset = container.find(search)) != string::npos) || ((offset = container.find("Usage")) != string::npos) || ((offset = container.find("try again")) != string::npos)){
                cout << "Connection failed.\n";
                Connectivity.close();
                remove("test.db");
                return 1;
            }
        }
    }
    Connectivity.close();
    remove("test.db");
    cout << "Ready.\n";
    sleep(1);
    system("cls");
    return 0;
}

string getIPAddress(){
    // Get Client IP Address
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
    // Get Client Subnet Mask
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

int settings(){
    // Set communication paramters
    cout << "Username:\t";
    getline(cin, username);
    cout << "Server IP:\t";
    getline(cin, server_ip);
    cout << "Password:\t";
    getline(cin, server_password);
    cout << "Testing server connectivity...\n";
    system(("ping "+server_ip + " > test.db").c_str());
    string container;
    ifstream Connectivity;
    int offset;
    string search = "Request timed out";
    Connectivity.open("test.db");
    if(Connectivity.is_open()){
        while(!Connectivity.eof()){
            getline(Connectivity, container);
            if(((offset = container.find(search)) != string::npos) || ((offset = container.find("Usage")) != string::npos) || ((offset = container.find("try again")) != string::npos)){
                cout << "Connection failed.\n";
                Connectivity.close();
                remove("test.db");
                return 1;
            }
        }
    }
    Connectivity.close();
    remove("test.db");
    cout << "Connection success.\n";
    return 0;
}

