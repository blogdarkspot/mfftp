#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>


int main(int argc, char** argv)
{
    WSADATA wsaData;
    {
        int iResult;
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAData startup failed %d\n", iResult);
        }
    }

    struct addrinfo* ptr = nullptr;

    {
        struct addrinfo *result = nullptr, hints;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        int iResult;

        iResult = getaddrinfo(argv[1], "21", &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed %d\n", iResult);
            WSACleanup();
            return 1;
        }
        ptr = result;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            freeaddrinfo(ptr);
            WSACleanup();
            return 1;
        }
    }
    //Connect
    {
        int iResult;
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("Unable connect to server!\n");
            closesocket(ConnectSocket);
            freeaddrinfo(ptr);
            WSACleanup();
            return 1;
        }
    }

    while (1) {
        char buffer[512];
        int iResult;

        iResult = recv(ConnectSocket, buffer, 512, 0);
        if (iResult > 0) {
            printf("%s\n", buffer);
        }

        char a;
        a = getchar();

        char user_command[] = "USER test\r\n";
        send(ConnectSocket, user_command, 11, 0);
    }
    closesocket(ConnectSocket);
    freeaddrinfo(ptr);
    WSACleanup();
    return 0;
}