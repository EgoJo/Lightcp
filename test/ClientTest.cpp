#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <cstring>
using namespace std;

const char* IP = "127.0.0.1";
const int PORT = 12345;
const int BACKLOG = 5;
const int BUF_SIZE = 1024;

int main(){
	int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket\n");
        return -1;
    }

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &address.sin_addr);
	address.sin_port = htons(PORT);

	if(connect(sockfd, (struct sockaddr*) &address, sizeof(address)) < 0){
		perror("connect");
		return -1;
	}

	char buffer[BUF_SIZE];
	int len = 0;
	while(true) {
		memset(buffer, 0, sizeof(buffer));
	    scanf("%s", buffer);
	    len = strlen(buffer);
	    if(send(sockfd, buffer, len, 0) < 0){
	    	perror("send");
	    }
	    if(recv(sockfd, buffer, BUF_SIZE, 0) < 0){
	    	perror("recv");
	    }else{
	    	printf("%s\n", buffer);
	    }
	}
}