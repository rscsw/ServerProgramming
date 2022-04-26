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

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
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

//서버로부터 메세지 전달받아서 벡터에 저장하는 함수
void ClientRead(SOCKET socket)
{
    char buffer[PACKET_SIZE] = {};
    while (true)
    {
        ZeroMemory(&buffer, PACKET_SIZE);
        recv(socket, buffer, PACKET_SIZE, 0);
        if (strcmp(buffer, sendkey) == 0 && updatable)
        {
            cout << "\n'주'님이 입력중입니다." << endl;
        }
        else if (strcmp(buffer, "/q") == 0)
        {
            system("cls");
            PrintMessage();
            cout << "'주'님이 대화를 종료했습니다." << endl;
            //closesocket(socket);
            //WSACleanup();
            exit(0);
        }
        else if (!updatable && strcmp(buffer, sendkey) == 1)
        {
            message.push_back("[주] " + (string)buffer);
        }
        else if (updatable)
        {
            message.push_back("[주] " + (string)buffer);
            PrintMessage();
        }
    }
}

//입력을 받아 서버에 전달하는 함수
void ClientSend(char buffer[], SOCKET socket)
{
    cout << "\n'수'님이 입력중입니다.\n\n[수] ";
    cin.getline(buffer, PACKET_SIZE, '\n');
    if (strcmp(buffer, "/q") == 0)
    {
        locker.lock();
        send(socket, buffer, strlen(buffer), 0);
        locker.unlock();
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
        message.push_back("[수] " + (string)buffer);
        PrintMessage();
    }
}

//커맨드 입력을 받아 서버에 전달하는 함수
void ClientSendCommand(SOCKET socket)
{
    locker.lock();
    send(socket, sendkey, strlen(sendkey), 0);
    locker.unlock();
}

int main()
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    //sockaddr_in getip = { 0 }; //나의 아이피 주소:포트
    //int addrsize = sizeof(sockaddr_in); //나의 아이피 주소:포트의 길이

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Input server address and port
    cout << "서버 접속 /c ip port : ";
    string c;
    string pnn;
    string psn;
    cin >> c >> pnn >> psn;
    system("cls");
    message.push_back((string)pnn + ":" + (string)psn + " 접속중...");
    PrintMessage();

    // Resolve the server address and port
    iResult = getaddrinfo(pnn.c_str(), psn.c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    message.push_back("접속이 완료되었습니다.");
    PrintMessage();
    cout << "====================================================" << endl;
    cout << "메세지 전송 : Enter" << endl;
    cout << "종료 : / q" << endl;
    cout << "[주의사항]" << endl;
    cout << " - 아무것도 입력하지 않고 전송하면 상대방에게 아무것도 전달되지 않습니다." << endl;
    cout << " - 최초로 Enter 입력 시 공백이 출력되는 현상이 있습니다." << endl;
    cout << "   한 번만 일어나는 현상이니 무시해주세요." << endl;
    cout << " - 이 매뉴얼은 한 번만 출력됩니다." << endl;
    cout << "====================================================" << endl;

    char buffer[PACKET_SIZE] = { 0 };
    thread ClientReadth(ClientRead, ConnectSocket);

    while (true)
    {
        if (_kbhit())
        {
            int c = _getch();
            if (c == 13)
            {
                updatable = false;
                thread ClientSendCommandth(ClientSendCommand, ConnectSocket);
                ClientSendCommandth.join();
                thread ClientSendth(ClientSend, buffer, ConnectSocket);
                ClientSendth.join();
                updatable = true;
            }
        }
    }
    ClientReadth.join();
}