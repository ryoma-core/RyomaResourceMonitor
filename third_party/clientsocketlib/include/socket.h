#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32")


class Socket 
{
    public:
        Socket();
        ~Socket();
        bool SocketStart();
        void SocketStop();
        void Settings(std::string ip, size_t port);
        void ChangeFlag(char f) { m_flag = f;};
        bool ConnectToServer();
        char m_flag = '0';
        double m_data = 0;
        bool m_starting = false;
        std::string m_serverIp;
        size_t m_server_Port;
    private:
    #pragma region Members
        WSADATA m_wsaData;
        SOCKET m_connectSocket;
        SOCKADDR_IN m_serverAddr = {};
        std::string m_acc;
    #pragma endregion
    #pragma region Methods
    bool RecvCall();
    bool SendCall();
    #pragma endregion

};