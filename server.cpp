#include <iostream>
#include <winsock.h>
#include "Handle.h"
#include "HandleData.h"
using namespace std;


int nSocket;
int nClientSocket[1500] = {
    0,
};
struct sockaddr_in srv;
fd_set fr;
fd_set fw;
fd_set fe;
int nMaxFd = 0;

int main()
{
    Handl h;
    HandleDat hd;
    int nRet = 0;
    WSADATA wd;

    if (WSAStartup(MAKEWORD(2, 2), &wd) < 0)
    {
        cout << endl
             << "Not able to start the socket environment";
        return (EXIT_FAILURE);
    }

    nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0)
    {
        cout << endl
             << "The socket cannot be initialized";
        exit(EXIT_FAILURE);
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = INADDR_ANY;
    memset(&srv.sin_zero, 0, 8);

    nRet = bind(nSocket, (struct sockaddr *)&srv, sizeof(struct sockaddr));
    if (nRet < 0)
    {
        cout << endl
             << "The socket cannot be bind";
        exit(EXIT_FAILURE);
    }

    nRet = listen(nSocket, 1500);
    if (nRet < 0)
    {
        cout << endl
             << "The listen failed";
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    nMaxFd = nSocket + 1;

    while (1)
    {
        FD_ZERO(&fr);
        FD_SET(nSocket, &fr);
        for (int nIndex = 0; nIndex < 5; nIndex++)
        {
            if (nClientSocket[nIndex] > 0)
            {
                FD_SET(nClientSocket[nIndex], &fr);
            }
        }
        nRet = select(nMaxFd, &fr, NULL, NULL, &tv);
        if (nRet < 0)
        {
            cout << endl
                 << "select api call failed. Will exit";
            return (EXIT_FAILURE);
        }
        else if (nRet == 0)
        {
            cout << endl
                 << "No client at port waiting for an active connection/new message";
        }
        else
        {
            if (FD_ISSET(nSocket, &fr))
            {
                h.HandleNewConnection();
            }
            else
            {
                hd.HandleDataFromClient();
            }
        }
    }
}
