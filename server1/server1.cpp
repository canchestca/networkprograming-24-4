//tạo ứng dụng server theo giao thức TCP nhận câu chào từ client
//sau đó nhập dữu liệu từ bàn phím và gửi cho client

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib , "ws2_32.lib")

int main()

{
    //tạo server
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET6;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    printf("Dang cho du lieu\n");

    SOCKET client = accept(listener , NULL ,NULL);


    //nhận thông điệp từ client
    char buf[256];
    int r = recv(client, buf, sizeof(buf), 0);
    if (r<=0)
    {
        //ket noi da bi ngat
        closesocket(client);
        closesocket(listener);
        WSACleanup();
        return 0;

    }
    //neu co du lieu  thi them ky ket thuc xau
    buf[r] = 0;
    //in cau chao ra man hinh
    printf("From client : %s\n", buf);
    while (true)
    {
        //nhập dữ liệu từ bàn phím
        printf("nhap xau: ");
        gets_s(buf, sizeof(buf));
        
        //Gửi sang client 
        send(client, buf, strlen(buf), 0);
        //kí tự xuống dòng
        send(client, "\n", 1, 0);
        
        // thoát khỏi vòng lặp
        //nếu chuỗi nhập vào là "exit" thì thoát khỏi vòng lặp
        if (strcmp(buf, "exit") == 0)
            break;
           

    }
    closesocket(client);
    closesocket(listener);


    WSACleanup();
}

