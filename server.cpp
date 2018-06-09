// Libraries
#pragma comment(lib, "ws2_32.lib");
#include <WinSock2.h>
#include <WS2tcpip.h>
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
    cout << "ChatNetwork Server 1.0\n";
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
        cout << "Failed to start winsock.";
        return 1;
    }

    SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener == INVALID_SOCKET){
        cout << "Can\'t create socket";
        return 1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    bind(listener, (sockaddr*)&address, sizeof(address));
    listen(listener, SOMAXCONN);
    
    sockaddr_in client;
    int clientsize = sizeof(client);
    SOCKET clientsocket = accept(listener, (sockaddr*)&client, &clientsize);

    char host[NI_MAXHOST];      // Remote name
    char service[NI_MAXHOST];   // Service Port
    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    // Having problem with this block
    /*if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
        cout << host << " is connected on port " << service << "\n";
    }else{
        //inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        //cout << host << " is connected on port " << ntohs(client.sin_port) << "\n";
    }*/

    closesocket(listener);

    char buff[4096];
    while(true){
        ZeroMemory(buff, 4096);
        int bytesReceived = recv(clientsocket, buff, 4096, 0);
        
    }

    closesocket(clientsocket);
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