#include <iostream>
#include <winsock.h>

using namespace std;
#define PORT 55555
#ifndef Handle
    #define Handle
class Handl
{
public:
    
    int nSocket;
    int nClientSocket[1500] = {
        0,
    };
    struct sockaddr_in srv;
    fd_set fr;
    fd_set fw;
    fd_set fe;
    int nMaxFd = 0;

    Handl()
    {
    }
    void HandleNewConnection()

    {
        int nNewClient = accept(nSocket, NULL, NULL);
        if (nNewClient < 0)
        {
            cout << endl
                 << "Not able to get a new client socket";
        }
        else
        {
            int nIndex;
            for (nIndex = 0; nIndex < 1500; nIndex++)
            {
                if (nClientSocket[nIndex] == 0)
                {
                    nClientSocket[nIndex] = nNewClient;
                    if (nNewClient > nMaxFd)
                    {
                        nMaxFd = nNewClient + 1;
                    }
                    break;
                }
            }

            if (nIndex == 1500)
            {
                cout << endl
                     << "Server busy. Cannot accept anymore connections";
            }
        }
    }
};
#endif