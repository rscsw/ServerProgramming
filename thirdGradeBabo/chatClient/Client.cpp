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

//����(��ȭ���� ����)
vector<string> message;

//��ȭ ������ ȭ�鿡 ����ϴ� �Լ�
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

//�����κ��� �޼��� ���޹޾Ƽ� ���Ϳ� �����ϴ� �Լ�
void ClientRead(SOCKET socket)
{
    char buffer[PACKET_SIZE] = {};
    while (true)
    {
        ZeroMemory(&buffer, PACKET_SIZE);
        recv(socket, buffer, PACKET_SIZE, 0);
        if (strcmp(buffer, sendkey) == 0 && updatable)
        {
            cout << "\n'��'���� �Է����Դϴ�." << endl;
        }
        else if (strcmp(buffer, "/q") == 0)
        {
            system("cls");
            PrintMessage();
            cout << "'��'���� ��ȭ�� �����߽��ϴ�." << endl;
            //closesocket(socket);
            //WSACleanup();
            exit(0);
        }
        else if (!updatable && strcmp(buffer, sendkey) == 1)
        {
            message.push_back("[��] " + (string)buffer);
        }
        else if (updatable)
        {
            message.push_back("[��] " + (string)buffer);
            PrintMessage();
        }
    }
}

//�Է��� �޾� ������ �����ϴ� �Լ�
void ClientSend(char buffer[], SOCKET socket)
{
    cout << "\n'��'���� �Է����Դϴ�.\n\n[��] ";
    cin.getline(buffer, PACKET_SIZE, '\n');
    if (strcmp(buffer, "/q") == 0)
    {
        locker.lock();
        send(socket, buffer, strlen(buffer), 0);
        locker.unlock();
        cout << "��ȭ�� �����߽��ϴ�." << endl;
        //closesocket(socket);
        //WSACleanup();
        exit(0);
    }
    else
    {
        locker.lock();
        send(socket, buffer, strlen(buffer), 0);
        locker.unlock();
        message.push_back("[��] " + (string)buffer);
        PrintMessage();
    }
}

//Ŀ�ǵ� �Է��� �޾� ������ �����ϴ� �Լ�
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

    //sockaddr_in getip = { 0 }; //���� ������ �ּ�:��Ʈ
    //int addrsize = sizeof(sockaddr_in); //���� ������ �ּ�:��Ʈ�� ����

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
    cout << "���� ���� /c ip port : ";
    string c;
    string pnn;
    string psn;
    cin >> c >> pnn >> psn;
    system("cls");
    message.push_back((string)pnn + ":" + (string)psn + " ������...");
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

    message.push_back("������ �Ϸ�Ǿ����ϴ�.");
    PrintMessage();
    cout << "====================================================" << endl;
    cout << "�޼��� ���� : Enter" << endl;
    cout << "���� : / q" << endl;
    cout << "[���ǻ���]" << endl;
    cout << " - �ƹ��͵� �Է����� �ʰ� �����ϸ� ���濡�� �ƹ��͵� ���޵��� �ʽ��ϴ�." << endl;
    cout << " - ���ʷ� Enter �Է� �� ������ ��µǴ� ������ �ֽ��ϴ�." << endl;
    cout << "   �� ���� �Ͼ�� �����̴� �������ּ���." << endl;
    cout << " - �� �Ŵ����� �� ���� ��µ˴ϴ�." << endl;
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