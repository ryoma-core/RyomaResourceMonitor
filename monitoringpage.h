#ifndef MONITORINGPAGE_H
#define MONITORINGPAGE_H

#include <QWidget>
#include <QThread>
#include <QLabel>
#include "socketworker.h"
#include "logger.h"


namespace Ui {
class MonitoringPage;
}

class MonitoringPage : public QWidget
{
    Q_OBJECT

public:
    explicit MonitoringPage(QWidget *parent = nullptr);
    ~MonitoringPage();
    void SetEndpoint(QString ip , int port);
    void StartMonitoring();
    void StopMonitoring();
    void SettingLogger(std::shared_ptr<Logger>& log) {m_monitoringlogger=log;}

signals:
    void GoBack();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MonitoringPage *ui;
    void ShowStatus(const QString& msg, int ms);
    // ------------------------ //
    QThread m_thread;
    SocketWorker* m_worker = nullptr;
    QString m_deviceIP = "";
    int m_devicePort = 0;
    QLabel m_statusLabel;

    std::shared_ptr<Logger> m_monitoringlogger;
};

#endif // MONITORINGPAGE_H
