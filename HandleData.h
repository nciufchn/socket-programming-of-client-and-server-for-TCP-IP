#include <iostream>
#include <winsock.h>
using namespace std;
#define PORT 55555
  #ifndef HandleData
#define HandleData

class HandleDat
{
 
int nSocket;
int nClientSocket[1500] = {
    0,
};
struct sockaddr_in srv;
fd_set fr;
fd_set fw;
fd_set fe;
int nMaxFd = 0;
public:
 HandleDat()
    {}
void HandleDataFromClient()
{
        for (int nIndex = 0; nIndex < 1500; nIndex++)
        {
            if (nClientSocket[nIndex] > 0)
            {
                if (FD_ISSET(nClientSocket[nIndex], &fr))
                {
                    char sBuff[255] = {
                        0,
                    };
                    int nRet = recv(nClientSocket[nIndex], sBuff, 255, 0);
                    if (nRet < 0)
                    {
                        cout << endl
                             << "Error at client socket";
                        closesocket(nClientSocket[nIndex]);
                        nClientSocket[nIndex] = 0;
                    }
                    else
                    {
                        cout << endl
                             << "Received data from:"
                             << nClientSocket[nIndex]
                             << "[Message:" << sBuff << "]";
                        break;
                    }
                }
            }
        }
    }

};
#endif