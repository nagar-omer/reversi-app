
#include <fstream>
#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;
int main() {

    ifstream myfile ("input.txt");
    string port;
    if (myfile.is_open()) {
        getline(myfile, port);
    }
    myfile.close();

    int port_as_int = atoi(port.c_str());
    Server server(port_as_int);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}