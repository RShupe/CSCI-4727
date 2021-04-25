#include <iostream>

// client code
#include "UDP.h"

int BUFFER_SIZE;

int main(int argc, char*argv[])
{
    UDP tmp;
    int sd = tmp.UDP_Open(20000);
    struct sockaddr_in addrSnd, addrRcv;
    int rc = tmp.UDP_FillSockAddr(&addrSnd, "cs.wisc.edu", 10000);
    char message[BUFFER_SIZE];
    sprintf(message, "hello world");
    rc = tmp.UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);
    if (rc > 0)
        int rc = tmp.UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
    return 0;
}
