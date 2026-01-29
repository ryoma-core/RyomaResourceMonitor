#include "socketworker.h"
#include <QThread>
#include <QTimer>
#include "socket.h"
#include <iostream>



SocketWorker::SocketWorker(const std::string& ip , size_t port ,QObject *parent) : m_ip{ip}, m_port{port}
{

}

SocketWorker::~SocketWorker()
{
}


void SocketWorker::start()
{
    m_stop.store(false);
    m_iscommunicate = true;
    Socket sock;
    sock.settings(m_ip,m_port);
    size_t reset_count = 0u;
    while(!m_stop.load())
    {
        if(reset_count == 1800u)
        {
            reset_count = 0u;
            reSetGraph();
        }
        sock.flag = '0';
        if(!sock.socket_start())
        {
            m_iscommunicate = false;
            emit Failed();
            break;
        }
        emit cpuReady(sock.data);
        sock.flag = '1';
        if(!sock.socket_start())
        {
            m_iscommunicate = false;
            emit Failed();
            break;
        }
        emit memoryReady(sock.data);
        sock.flag = '2';
        if(!sock.socket_start())
        {
            m_iscommunicate = false;
            emit Failed();
            break;
        }
        emit diskReady(sock.data);
        QThread::msleep(1000);
        reset_count++;
    }
    emit finished();
    sock.socket_stop();
}


void SocketWorker::stop()
{
    m_stop = true;
}


