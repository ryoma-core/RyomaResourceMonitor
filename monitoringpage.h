#ifndef MONITORINGPAGE_H
#define MONITORINGPAGE_H

#include <QWidget>
#include <QThread>
#include <QLabel>
#include "socketworker.h"


namespace Ui {
class MonitoringPage;
}

class MonitoringPage : public QWidget
{
    Q_OBJECT

public:
    explicit MonitoringPage(QWidget *parent = nullptr);
    ~MonitoringPage();
    void setEndpoint(QString ip , int port);
    void startMonitoring();
    void stopMonitoring();

signals:
    void goBack();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MonitoringPage *ui;

    QThread m_thread;
    SocketWorker* m_worker = nullptr;
    QString device_Ip = "";
    int device_Port = 0;
    QLabel statusLabel;
    void ShowStatus(const QString& msg, int ms);
};

#endif // MONITORINGPAGE_H
