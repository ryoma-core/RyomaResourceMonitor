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
    void Start();
    void Stop();

signals:
    void CpuReady(double v);
    void MemoryReady(double v);
    void DiskReady(double v);
    void Failed();
    void ReSetGraph();

    void Finished();
private:
    std::string m_ip;
    size_t m_port = 0;
    std::atomic_bool m_stop{false};
};

#endif // SOCKETWORKER_H
