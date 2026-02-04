#include "monitoringpage.h"
#include "ui_monitoringpage.h"

#include <QTimer>

MonitoringPage::MonitoringPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonitoringPage)
{
    ui->setupUi(this);
    ui->gridLayout->setRowStretch(0, 0);
    ui->gridLayout->setRowStretch(1, 1);
    ui->gridLayout->setColumnStretch(0, 1);
    ui->stackedWidget->setCurrentWidget(ui->cpuPageWidget);
}

MonitoringPage::~MonitoringPage()
{
    if (m_worker)m_worker->Stop();

    m_thread.quit();
    m_thread.wait();

    delete ui;
}


void MonitoringPage::SetEndpoint(QString ip, int port)
{
    m_deviceIP = ip;
    m_devicePort = port;
}

void MonitoringPage::StartMonitoring()
{
    StopMonitoring();

    m_worker = new SocketWorker(m_deviceIP.toStdString(),
                                static_cast<size_t>(m_devicePort));
    m_worker->moveToThread(&m_thread);

    connect(m_worker, &SocketWorker::Failed, this, [this]{
        ShowStatus("[ERROR](Network)-\"Socket Networking\"", 5000);
        if(m_monitoringlogger)
            {
        QString temp = "[ERROR](Network)-\"Socket Networking\"";
        m_monitoringlogger->WriteLine(temp);
        }
    }, Qt::QueuedConnection);

    connect(&m_thread, &QThread::started,
            m_worker, &SocketWorker::Start, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::CpuReady,
            ui->cpuPageWidget, &Cpugraph::AppendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::MemoryReady,
            ui->memoryPageWidget, &Memorygraph::AppendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::DiskReady,
            ui->diskPageWidget, &Diskgraph::AppendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::ReSetGraph,
            this, [this](){
                ui->cpuPageWidget->ClearGraph();
                ui->memoryPageWidget->ClearGraph();
                ui->diskPageWidget->ClearGraph();
            }, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::Finished,
            &m_thread, &QThread::quit, Qt::QueuedConnection);

    connect(&m_thread, &QThread::finished,
            m_worker, &QObject::deleteLater);

    m_thread.start();
}

void MonitoringPage::StopMonitoring()
{
    if (!m_worker) return;
    if(m_monitoringlogger)
    {
    QString temp = "[STOP] Thread Stop";
    m_monitoringlogger->WriteLine(temp);
    }
    m_worker->Stop();
    m_thread.quit();
    m_thread.wait();
    m_worker = nullptr;
}

void MonitoringPage::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->cpuPageWidget);
}


void MonitoringPage::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->memoryPageWidget);
}


void MonitoringPage::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->diskPageWidget);
}


void MonitoringPage::on_pushButton_4_clicked()
{

    if(m_monitoringlogger)
    {
    QString temp = "[DISCONNECTED] Server Disconnected";
    m_monitoringlogger->WriteLine(temp);
    }
    ui->cpuPageWidget->ClearGraph();
    ui->memoryPageWidget->ClearGraph();
    ui->diskPageWidget->ClearGraph();
    emit GoBack();
}

void MonitoringPage::ShowStatus(const QString &msg, int ms)
{
    m_statusLabel.setText(msg);
    m_statusLabel.show();
    QTimer::singleShot(ms, this, [this]{
        m_statusLabel.clear();
        m_statusLabel.hide();
    });
}

