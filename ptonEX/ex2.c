#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in sa;
    inet_pton(AF_INET, "192.4.8.231", &(sa.sin_addr));
    uint64_t val = ntohl(sa.sin_addr.s_addr);
    printf ("STR->INT: %ld\n",val);

    struct sockaddr_in sa2;
    sa2.sin_addr.s_addr = htonl(3221489895);
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sa2.sin_addr), str, INET_ADDRSTRLEN);
    printf("INT->STR: %s\n", str);

}
