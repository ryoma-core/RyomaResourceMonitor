#ifndef SOCKETWORKER_H
#define SOCKETWORKER_H

#include <QObject>
#include <atomic>
#include <string>

class SocketWorker : public QObject
{
    Q_OBJECT
public:
    explicit SocketWorker(const std::string& ip , size_t port ,QObject *parent = nullptr);
    ~SocketWorker();
    std::atomic_char m_mode{'0'};
    bool m_iscommunicate = false;

public slots:
    void start();
    void stop();

signals:
    void cpuReady(double v);
    void memoryReady(double v);
    void diskReady(double v);
    void Failed();
    void reSetGraph();

    void finished();
private:
    std::string m_ip;
    size_t m_port = 0;
    std::atomic_bool m_stop{false};
};

#endif // SOCKETWORKER_H
