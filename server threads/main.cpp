/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include <fstream>
#include "Server.h"

/*****************************************************************************
 * Function name: main
 * Operation: get the pert from txt file, creat a server with the port.
 ****************************************************************************/

using namespace std;
int main() {
    //int port_as_int = atoi(port.c_str());

    Server server(8000);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    return 0;
}
