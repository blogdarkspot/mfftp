#ifndef WIN32_LEAN_AND_MEAN //https://docs.microsoft.com/en-us/windows/desktop/winsock/creating-a-basic-winsock-application
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main()
{

    WSADATA wsaData;

    {
        int iResult;

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (iResult != 0) {
            printf("WSAStartup failed: %d \n", iResult);
            return 1;
        }
    }

    struct addrinfo* result = NULL;
    {
        struct addrinfo hints;
        int iResult;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        iResult = getaddrinfo(NULL, "21", &hints, &result);

        if (iResult != 0) {
            printf("getaddrinfo failed: %d\n", iResult);
            WSACleanup();
            return 1;
        }
    }

    SOCKET ListenSocket = INVALID_SOCKET;

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    {
        if (ListenSocket == INVALID_SOCKET) {
            printf("Error socket(): %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

        int iResult;

        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
            printf("Listen failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
    }

    SOCKET ClientSocket = INVALID_SOCKET;

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    while (1) //communication
    {
        char buffer[21] = "\x32\x32\x30\x20\x28\x76\x73\x46\x54\x50\x64\x20\x33\x2e\x30\x2e\x33\x29\x0d\x0a";
        int iResult;

        printf("sending %s", buffer);
        iResult = send(ClientSocket, buffer, 21, 0);
        if (iResult == SOCKET_ERROR) {
            printf("Send failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
        }
        iResult = recv(ClientSocket, buffer, 21, 0);
        if (iResult > 0) {
            printf("%s\n", buffer);
        } else if (iResult == 0) {
            printf("Clossing connection ...\n");
        }
    }
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}