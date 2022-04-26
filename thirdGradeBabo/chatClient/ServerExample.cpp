//#undef UNICODE
//
//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <thread>
//
//// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
//// #pragma comment (lib, "Mswsock.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"
//
//int main(void)
//{
//    WSADATA wsaData; //���Ͽ� ���õ� �����͵��� �� ��� �ִ�
//    int iResult; //���� ���� �� 0�� ��ȯ���ִ� ��
//
//    SOCKET ListenSocket = INVALID_SOCKET; //Ŭ���̾�Ʈ�� ���� �ƴ��� �ȵƴ��� üũ�ϴ� ����
//    SOCKET ClientSocket = INVALID_SOCKET; //������ ������ ���� ������ üũ
//
//    struct addrinfo* result = NULL;
//    struct addrinfo hints;
//
//    int iSendResult;
//    char recvbuf[DEFAULT_BUFLEN];
//    int recvbuflen = DEFAULT_BUFLEN;
//
//    // Initialize Winsock
//    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //���� 2����Ʈ, ���� 2����Ʈ�� ����� ���̴� ��� ����, wsaDATA�� �ּҸ� �ѱ� ���̴�, �ּҸ� �ѱ�� �� �ּҿ��ٰ� ���� �� �� �ִ�
//    if (iResult != 0) { //���� �޼��� ����ϰ� �� ����������
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//
//    ZeroMemory(&hints, sizeof(hints)); //TCP ����� �� �� �ʿ��� �� ����Ʈ
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;
//
//    // Resolve the server address and port
//    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result); //hints���� �ּҸ� �޾ƿ´�, resault�� �����ش޶�� ��û�Ѵ�
//    if (iResult != 0) { //���������� ����
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 1;
//    }
//
//    // Create a SOCKET for connecting to server
//    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); //���Ͽ��ٰ� �ʿ��� ���� ��� ������Ѵ�
//    if (ListenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        WSACleanup();
//        return 1;
//    }
//
//    // Setup the TCP listening socket
//    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); //�ּҸ� ���ε��Ѵ�, ������ ������ ���ִ��� �ȵ��ִ��� Ȯ��
//    if (iResult == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    freeaddrinfo(result); //������ ������ ����, �������� �Ҵ��߱� ������ ���� �������Ѵ�
//
//    iResult = listen(ListenSocket, SOMAXCONN); //������ �����ϱ� ������ ���
//    if (iResult == SOCKET_ERROR) {
//        printf("listen failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    // Accept a client socket
//    ClientSocket = accept(ListenSocket, NULL, NULL); //����� �㰡�ϴ� ����, null ���� ������ �ּ�:��Ʈ, null ���� ������ �ּ�:��Ʈ�� ����
//    if (ClientSocket == INVALID_SOCKET) {
//        printf("accept failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    // No longer need server socket
//    closesocket(ListenSocket); //����Ʊ� ������ ���� �ʿ��� ������ ��
//
//    // Receive until the peer shuts down the connection
//    do { //��� Ŭ���̾�Ʈ�κ��� �޾ƿ��� ����
//
//        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0); //���� ������ recvbuf��ŭ �ҷ������ ����
//        if (iResult > 0) {
//            printf("Bytes received: %d\n", iResult); //���� ��ŭ ���
//
//            // Echo the buffer back to the sender
//            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
//            if (iSendResult == SOCKET_ERROR) {
//                printf("send failed with error: %d\n", WSAGetLastError());
//                closesocket(ClientSocket);
//                WSACleanup();
//                return 1;
//            }
//            printf("Bytes sent: %d\n", iSendResult);
//        }
//        else if (iResult == 0)
//            printf("Connection closing...\n");
//        else {
//            printf("recv failed with error: %d\n", WSAGetLastError());
//            closesocket(ClientSocket);
//            WSACleanup();
//            return 1;
//        }
//
//    } while (iResult > 0);
//
//    // shutdown the connection since we're done
//    iResult = shutdown(ClientSocket, SD_SEND); //���� �� �� �޾����ϱ� ���� ����
//    if (iResult == SOCKET_ERROR) {
//        printf("shutdown failed with error: %d\n", WSAGetLastError());
//        closesocket(ClientSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    // cleanup
//    closesocket(ClientSocket);
//    WSACleanup();
//
//    return 0;
//}