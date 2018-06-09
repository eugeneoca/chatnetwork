// Libraries
#pragma comment(lib, "ws2_32.lib");
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

using namespace std;

// Method Initialization
int welcome_screen();
string getIPAddress();
string getSubnet();
int create_server();
void process();

// Global Variables
string server_ip;
string server_subnet;
int port = 2000;

int main() {
    system("cls");
    if(welcome_screen()){
        return 0;
    }
    if(create_server()){
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
    server_ip      = getIPAddress();
    server_subnet  = getSubnet();
    cout << "Server IP:\t" << getIPAddress() << "\n";
    cout << "Server Subnet:\t" << getSubnet() << "\n";
    cout << "Testing Server connectivity...\n";
    system(("ping " + server_ip + " > test.db").c_str());
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

int create_server(){
    // Start creating the server

    // Start winsock
    WSADATA wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if(WSAStartup(DllVersion, &wsaData) != 0){
        // To fix error, add -lwsock32 at the end of compile commind

    }

    //thread server_instance(process);
    //server_instance.join();
    return 0;
}

// State variable
int started = 0;

void process(){
    // Process of the server
    while(1){
        if(!started){
            cout << "Server has been started and listening at " << server_ip << ":" << port << "\n";
            started = 1;
        }
    }
}