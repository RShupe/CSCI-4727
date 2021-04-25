#include <iostream>
#include <netinet/in.h>
#include <cassert>
#include "UDP.h"
// server code
int main(int argc, char*argv[]) {
    UDP tmp;
    int sd = tmp.UDP_Open(10000);
    assert(sd > -1);
    while (1) {
        struct sockaddr_in addr;
        int BUFFER_SIZE;
        char message[BUFFER_SIZE];
        int rc = tmp.UDP_Read(sd, &addr, message, BUFFER_SIZE);
        if (rc > 0) {
            char reply[BUFFER_SIZE];
            sprintf(reply, "goodbye world");
            rc = tmp.UDP_Write(sd, &addr, reply, BUFFER_SIZE);
        }
    }
    return 0;
}