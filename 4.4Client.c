
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char buf[100];
    int k;
    int sock_desc;
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    //Create socket
    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    if(sock_desc==-1)
    {
        printf("Error in socket creation");
        exit(1);
    }

    client.sin_family=AF_INET;
    client.sin_addr.s_addr= inet_addr("192.168.0.101");
    client.sin_port= htons( 8888 );

    //Connect to remote server
    if(k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client))<0)
    {
        printf("Error in connecting to server");
        exit(1);
    }

    while(1)
    {
        printf("\nEnter data to be send to server: ");
        fgets(buf,100,stdin);
	//Enter end to stop the chat
        if(strncmp(buf,"end",3)==0)
            break;

        k=send(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }

        k=recv(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Error in receiving");
            exit(1);
        }

        printf("Message got from server is : %s",buf);
    }
    exit(0);
    return 0;
}
