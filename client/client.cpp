// client.cpp : This file contains the 'main' function. Program execution begins and ends there.
// kết nối server netcat , gửi cau chao
// sau đó nhận dữ liệu và in ra màn hình

#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret = SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("connect failed : %d \n", ret);
        return 1;


    }

    //gửi đến server
    char buf[256] = "hello server|||\n";
    send(client, buf, strlen(buf), 0);

    //lien tuc nhan du lieu tu server và in ra màn hình
    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret  <= 0 )
        {
            ret = WSAGetLastError();
            printf("connect closed : %d \n", ret);
            break;
        }


        //them ky tu ket thuc xau va in ra man hình
        if (ret < sizeof(buf))
        
            buf[ret] = 0;
            printf("receive: %s", buf);
        

        

    }

   
    closesocket(client);
    WSACleanup();

}

