#include <netinet/in.h>
#include <stdio.h>
#include <string.h>	//strlen
#include <unistd.h> // close
#include <sys/socket.h> 
#include <arpa/inet.h>	//inet_addr

int main (int argc, char *argv[]){

    int socket_desc;
    struct sockaddr_in server;


    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1){
        printf("Não foi possível criar o socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // escuta qualquer ip da maquina
    server.sin_port = htons(8888);

    if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) <0){
        printf("Erro ao fazer o bind\n");
        return 1;
    }
    printf("Bind efetuado\n");

    return 0;
}