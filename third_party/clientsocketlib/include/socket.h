#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32")


class Socket 
{
    public:
        Socket();
        ~Socket();
        bool socket_start();
        void socket_stop();
        void settings(std::string ip, size_t port);
        void change_flag(char f) { flag = f;};
        bool connect_to_server();
        char flag = '0';
        double data = 0;
        bool starting = false;
        std::string server_Ip;
        size_t server_Port;
    private:
    #pragma region Members
        WSADATA wsaData;
        SOCKET connectSocket;
        SOCKADDR_IN serverAddr = {};
        std::string acc;
    #pragma endregion
    #pragma region Methods
    bool recvCall();
    bool sendCall();
    #pragma endregion

};