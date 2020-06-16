#include <netinet/in.h>
#include <stdio.h>
#include <string.h>	//strlen
#include <unistd.h> // close
#include <sys/socket.h> 
#include <arpa/inet.h>	//inet_addr

int main (int argc, char *argv[]){

    int socket_desc, c, new_socket;
    struct sockaddr_in server, client;
    char message[2000], client_reply [2000];


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
    
    // escutar
    listen(socket_desc, 3);

    //aceitar conexão entrantes

    printf("Aguardando conexoes...\n");
    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
	
        if (new_socket<0)
	    {
		    perror("Erro ao aceitar conexão");
		    return 1;
	    }

        printf("Conexão aceita\n");

        char *client_ip = inet_ntoa(client.sin_addr);

        int client_port = ntohs(client.sin_port);

        printf("Conexão aceita do client %s:%d\n", client_ip, client_port);

    do{
        //limpa a variavel
        bzero(client_reply, sizeof(client_reply));
        // recebe dados do cliente
        if (recv(new_socket, client_reply,2000, 0) < 0){
            printf("Falha no recv\n");
            return 1;
        }
        printf("Resposta Recebida\n");
        printf("%s\n", client_reply);

        //envia dados
        printf("Digite uma mensagem:");

        //resposta ao cliente
        bzero(message, sizeof(message));

        int ch, n = 0;
        /* lê a entrada de dados do usuário via getchar */
        while ((ch = getchar()) != '\n' && n < 2000) {
            message[n] = ch;
            ++n;
        }

        //message = "Olá cliente!";
        write(new_socket, message, strlen(message));


    }  while (strcmp(client_reply, "exit") != 0);
    if (strcmp(client_reply, "exit") != 0){
        return 0;
    }
}
    return 0;
}