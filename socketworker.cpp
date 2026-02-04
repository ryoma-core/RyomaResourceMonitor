#include "socketworker.h"
#include <QThread>
#include <QTimer>
#include <iostream>
#include "socket.h"



SocketWorker::SocketWorker(const std::string& ip , size_t port ,QObject *parent) : m_ip{ip}, m_port{port}
{

}

SocketWorker::~SocketWorker()
{
}


void SocketWorker::Start()
{
    m_stop.store(false);
    m_iscommunicate = true;
    Socket sock;
    sock.Settings(m_ip,m_port);
    size_t reset_count = 0u;
    while(!m_stop.load())
    {
        if(reset_count == 1800u)
        {
            reset_count = 0u;
            ReSetGraph();
        }
        sock.m_flag = '0';
        if(!sock.SocketStart())
        {
            m_iscommunicate = false;
            emit Failed();
            sock.SocketStop();
            break;
        }
        emit CpuReady(sock.m_data);
        sock.m_flag = '1';
        if(!sock.SocketStart())
        {
            m_iscommunicate = false;
            emit Failed();
            sock.SocketStop();
            break;
        }
        emit MemoryReady(sock.m_data);
        sock.m_flag = '2';
        if(!sock.SocketStart())
        {
            m_iscommunicate = false;
            emit Failed();
            sock.SocketStop();
            break;
        }
        emit DiskReady(sock.m_data);
        QThread::msleep(1000);
        reset_count++;
    }
    emit Finished();
    sock.SocketStop();
}


void SocketWorker::Stop()
{
    m_stop = true;
}


