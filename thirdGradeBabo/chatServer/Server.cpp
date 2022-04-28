#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define PACKET_SIZE 1024

mutex locker;
bool updatable = true;
char sendkey[PACKET_SIZE] = "^@^^_&se$^&*n#d%$";

//벡터(대화내역 저장)
vector<string> message;

//대화 내역을 화면에 출력하는 함수
void PrintMessage()
{
    system("cls");
    if (message.size() >= 10)
    {
        for (int i = message.size(); i > 10; i--)
        {
            message.erase(message.begin());
        }
    }
    for (int i = 0; i < message.size(); i++)
    {
        cout << message[i] << endl;
    }
}

//클라이언트로부터 메세지 전달받아서 벡터에 저장하는 함수
void ServerRead(SOCKET socket)
{
    char buffer[PACKET_SIZE] = {};
    while (true)
    {
        ZeroMemory(&buffer, PACKET_SIZE);
        recv(socket, buffer, PACKET_SIZE, 0);
        if (strcmp(buffer, sendkey) == 0 && updatable)
        {
            cout << "\n'수'님이 입력중입니다." << endl;
        }
        else if (strcmp(buffer, "/q") == 0)
        {
            PrintMessage();
            cout << "'수'님이 대화를 종료했습니다." << endl;
            //closesocket(socket);
            //WSACleanup();
            exit(0);
        }
        else if (!updatable && strcmp(buffer, sendkey) == 1)
        {
            message.push_back("[수] " + (string)buffer);
        }
        else if (updatable)
        {
            message.push_back("[수] " + (string)buffer);
            PrintMessage();
        }
    }
}

//입력을 받아 클라이언트에 전달하는 함수
void ServerSend(char buffer[], SOCKET socket)
{
    cout << "\n'주'님이 입력중입니다.\n\n[주] ";
    cin.getline(buffer, PACKET_SIZE, '\n');
    if (strcmp(buffer, "/q") == 0)
    {
        locker.lock();
        send(socket, buffer, strlen(buffer), 0);
        locker.unlock();
        PrintMessage();
        cout << "대화를 종료했습니다." << endl;
        //closesocket(socket);
        //WSACleanup();
        exit(0);
    }
    else
    {
        locker.lock();
        send(socket, buffer, strlen(buffer), 0);
        locker.unlock();
        message.push_back("[주] " + (string)buffer);
        PrintMessage();
    }
}

//커맨드 입력을 받아 클라이언트에 전달하는 함수
void ServerSendCommand(SOCKET socket)
{
    locker.lock();
    send(socket, sendkey, strlen(sendkey), 0);
    locker.unlock();
}

int main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    sockaddr_in getip = { 0 }; //나의 아이피 주소:포트
    int addrsize = sizeof(sockaddr_in); //나의 아이피 주소:포트의 길이

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    message.push_back("Waiting Connection...");
    PrintMessage();

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, (sockaddr*)&getip, &addrsize);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket);

    message.push_back("'수'님이 " + (string)inet_ntoa(getip.sin_addr) + "에서 접속하셨습니다.");
    PrintMessage();
    cout << "====================================================" << endl;
    cout << "메세지 전송 : Enter" << endl;
    cout << "종료 : /q" << endl;
    cout << " - 아무것도 입력하지 않고 전송하면 오류가 발생합니다. 보내지 마세요." << endl;
    cout << " - 이 메뉴얼은 한 번만 출력됩니다." << endl;
    cout << "====================================================" << endl;

    char buffer[PACKET_SIZE] = { 0 };
    thread ServerReadth(ServerRead, ClientSocket);

    while (true)
    {
        if (_kbhit())
        {
            int c = _getch();
            if (c == 13)
            {
                updatable = false;
                thread ServerSendCommandth(ServerSendCommand, ClientSocket);
                ServerSendCommandth.join();
                thread ServerSendth(ServerSend, buffer, ClientSocket);
                ServerSendth.join();
                updatable = true;
            }
        }
    }
    ServerReadth.join();
}