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
    if (m_worker)m_worker->stop();

    m_thread.quit();
    m_thread.wait();

    delete ui;
}


void MonitoringPage::setEndpoint(QString ip, int port)
{
    device_Ip = ip;
    device_Port = port;
}

void MonitoringPage::startMonitoring()
{
    stopMonitoring();

    m_worker = new SocketWorker(device_Ip.toStdString(),
                                static_cast<size_t>(device_Port));
    m_worker->moveToThread(&m_thread);

    connect(m_worker, &SocketWorker::Failed, this, [this]{
        ShowStatus("[ERROR](Network)-\"Socket Networking\"", 5000);
    }, Qt::QueuedConnection);

    connect(&m_thread, &QThread::started,
            m_worker, &SocketWorker::start, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::cpuReady,
            ui->cpuPageWidget, &Cpugraph::appendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::memoryReady,
            ui->memoryPageWidget, &Memorygraph::appendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::diskReady,
            ui->diskPageWidget, &Diskgraph::appendValue, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::reSetGraph,
            this, [this](){
                ui->cpuPageWidget->clearGraph();
                ui->memoryPageWidget->clearGraph();
                ui->diskPageWidget->clearGraph();
            }, Qt::QueuedConnection);

    connect(m_worker, &SocketWorker::finished,
            &m_thread, &QThread::quit, Qt::QueuedConnection);

    connect(&m_thread, &QThread::finished,
            m_worker, &QObject::deleteLater);

    m_thread.start();
}

void MonitoringPage::stopMonitoring()
{
    if (!m_worker) return;
    m_worker->stop();
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
    emit goBack();
}

void MonitoringPage::ShowStatus(const QString &msg, int ms)
{
    statusLabel.setText(msg);
    statusLabel.show();
    QTimer::singleShot(ms, this, [this]{
        statusLabel.clear();
        statusLabel.hide();
    });
}

