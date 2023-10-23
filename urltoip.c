#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char url[256]; // Assuming URLs can be up to 255 characters
    struct addrinfo hints, *result, *rp;
    char ip[INET6_ADDRSTRLEN];

    printf("Enter a URL: ");
    scanf("%s", url);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Use either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(url, NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        void *addr;
        if (rp->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        if (inet_ntop(rp->ai_family, addr, ip, sizeof(ip)) != NULL) {
            printf("IP address: %s\n", ip);
        }
    }

    freeaddrinfo(result);

    return 0;
}
