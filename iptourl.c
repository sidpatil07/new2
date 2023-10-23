#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char ip_address[16]; // Assuming IPv4, so the string length is 15 for xxx.xxx.xxx.xxx format
    char *url;

    printf("Enter an IP address: ");
    scanf("%s", ip_address);

    struct in_addr ip;
    if (inet_pton(AF_INET, ip_address, &ip) <= 0) {
        perror("inet_pton");
        return 1;
    }

    struct hostent *host = gethostbyaddr(&ip, sizeof(ip), AF_INET);

    if (host == NULL) {
        printf("Could not resolve the host.\n");
    } else {
        url = host->h_name;
        printf("URL: %s\n", url);
    }

    return 0;
}
