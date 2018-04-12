#include <stdio.h> // printf
#include <string.h> // strcpy
#include <sys/socket.h>
#include <netdb.h> // hostent
#include <arpa/inet.h>

/* Description of data base entry for a single host.  */
//struct hostent {
//    char *h_name;         /* Official name of host.  */
//    char **h_aliases;     /* Alias list.  */
//    int h_addrtype;       /* Host address type.  */
//    int h_length;         /* Length of address.  */
//    char **h_addr_list;       /* List of addresses from name server.  */
//};

int main(int argc, char *argv[]) {
    char *hostname = "www.baidu.com";
    char ip[100] = {};
    struct hostent *he = NULL;
    struct in_addr **addr_list;
    int i = 0;

    if ((he = gethostbyname(hostname)) == NULL) {
        // gethostbyname failed
        herror("gethostbyname");
        return 1;
    }

    // Cast the h_addr_list to in_addr, since h_addr_list also has the ip address in long format only.
    addr_list = (struct in_addr **) he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++) {
        // Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]));
        printf("%s resolved to: %s\n", hostname, ip);
    }

//    printf("%s resolved to: %s\n", hostname, ip);

    return 0;
}
