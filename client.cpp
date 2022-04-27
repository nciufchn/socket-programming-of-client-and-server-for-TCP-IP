#include <iostream>
#include <winsock.h>
#define PORT 55555
using namespace std;

int main()
{
    WSADATA w;
    int nRet = 0;
    sockaddr_in srv;
    nRet = WSAStartup(MAKEWORD(2, 2), &w);
    if (nRet < 0)
    {
        cout<<endl<<"Cannot Initialize socket lib:"<<endl;
        return -1;
    }
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0)
    {
        cout<<endl<<"Cannot Initialize listener socket:"<<endl;
        return -1;
    }
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv.sin_port = htons(PORT);
    memset(&(srv.sin_zero), 0, 8);
    nRet = connect(nSocket, (struct sockaddr*)&srv, sizeof(srv));
    if (nRet < 0)
    {
        cout<<endl<<"Cannot connect to server:"<<endl;
        return -1;
    }
    char sBuff[1024] = { 0, };
    while (1)
    {
        Sleep(2000);
        cout<<endl<<"What message you want to send..?"<<endl;
        fgets(sBuff, 1023, stdin);
        send(nSocket, sBuff, strlen(sBuff), 0);
    }
}