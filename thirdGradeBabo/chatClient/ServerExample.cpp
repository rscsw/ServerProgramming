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
//    WSADATA wsaData; //소켓에 관련된 데이터들을 다 들고 있다
//    int iResult; //문제 없을 때 0을 반환해주는 값
//
//    SOCKET ListenSocket = INVALID_SOCKET; //클라이언트가 연결 됐는지 안됐는지 체크하는 소켓
//    SOCKET ClientSocket = INVALID_SOCKET; //나에게 접속한 놈이 누군지 체크
//
//    struct addrinfo* result = NULL;
//    struct addrinfo hints;
//
//    int iSendResult;
//    char recvbuf[DEFAULT_BUFLEN];
//    int recvbuflen = DEFAULT_BUFLEN;
//
//    // Initialize Winsock
//    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //상위 2바이트, 하위 2바이트를 사용할 것이다 라는 선언, wsaDATA의 주소를 넘긴 것이다, 주소를 넘기면 그 주소에다가 값을 쓸 수 있다
//    if (iResult != 0) { //에러 메세지 출력하고 걍 끝내버리기
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//
//    ZeroMemory(&hints, sizeof(hints)); //TCP 통신을 할 때 필요한 것 디폴트
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;
//
//    // Resolve the server address and port
//    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result); //hints에서 주소를 받아온다, resault에 저장해달라고 요청한다
//    if (iResult != 0) { //마찬가지로 에러
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 1;
//    }
//
//    // Create a SOCKET for connecting to server
//    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); //소켓에다가 필요한 것을 모두 적어야한다
//    if (ListenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        WSACleanup();
//        return 1;
//    }
//
//    // Setup the TCP listening socket
//    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); //주소를 바인딩한다, 소켓이 연결이 돼있는지 안돼있는지 확인
//    if (iResult == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    freeaddrinfo(result); //쓸모없어서 버리는 과정, 동적으로 할당했기 때문에 직접 비워줘야한다
//
//    iResult = listen(ListenSocket, SOMAXCONN); //누군가 접속하기 전까지 대기
//    if (iResult == SOCKET_ERROR) {
//        printf("listen failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    // Accept a client socket
//    ClientSocket = accept(ListenSocket, NULL, NULL); //통신을 허가하는 과정, null 나의 아이피 주소:포트, null 나의 아이피 주소:포트의 길이
//    if (ClientSocket == INVALID_SOCKET) {
//        printf("accept failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    // No longer need server socket
//    closesocket(ListenSocket); //연결됐기 때문에 이제 필요없어서 버리는 것
//
//    // Receive until the peer shuts down the connection
//    do { //상대 클라이언트로부터 받아오는 로직
//
//        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0); //내가 설정한 recvbuf만큼 불러오라는 내용
//        if (iResult > 0) {
//            printf("Bytes received: %d\n", iResult); //받은 만큼 출력
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
//    iResult = shutdown(ClientSocket, SD_SEND); //받을 거 다 받았으니까 연결 종료
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