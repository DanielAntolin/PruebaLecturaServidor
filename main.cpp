#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>


int main()
{


    // Crear socket para recibir mensajes
    int recvSock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(recvSock, reinterpret_cast<sockaddr*>(&server), sizeof(server)) <= 0){
        std::cout << "Info: " << strerror(errno) << std::endl;
    }

    char buffer[1024];

    for (;;) {
        sockaddr_in client;
        socklen_t length = sizeof(client);

        int nRecv = recvfrom(recvSock, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&client), &length);
        std::string data(buffer, nRecv);
        std::cout << "Muestro: " << data << std::endl;


            // Crear socket para enviar mensaje a otro puerto
            int sendSock = socket(AF_INET, SOCK_DGRAM, 0);

            sockaddr_in sendAddr;
            sendAddr.sin_family = AF_INET;
            sendAddr.sin_port = htons(8083); // Cambiar al puerto deseado
            sendAddr.sin_addr.s_addr = client.sin_addr.s_addr;

            std::string message = "71A24AFA01F4";
            sendto(sendSock, message.data(), message.size(), 0, reinterpret_cast<sockaddr*>(&sendAddr), length);

            close(sendSock);

    }

    close(recvSock);

    return 0;
}
