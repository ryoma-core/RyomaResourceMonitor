#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , m_logger(std::make_shared<Logger>())
{
    ui->setupUi(this);
    // ui->stackedWidget->setCurrentWidget(ui->loginPageWidget);
    // ui->stackedWidget->setFocus();
    auto mon = qobject_cast<MonitoringPage*>(ui->monitoringPageWidget);
    ui->listPageWidget->SettingLogger(m_logger);
    ui->stackedWidget->setCurrentWidget(ui->listPageWidget);
    ui->stackedWidget->setFocus();

    connect(ui->listPageWidget,&ListPage::Connection,this,[this,mon](QString ip,int port){
        mon->SettingLogger(m_logger);
        mon->SetEndpoint(ip, port);
        ui->stackedWidget->setCurrentWidget(mon);
        ui->stackedWidget->setFocus();
        mon->StartMonitoring();
    });

    connect(ui->monitoringPageWidget,&MonitoringPage::GoBack,this,[this]()
            {
        ui->stackedWidget->setCurrentWidget(ui->listPageWidget);
        ui->stackedWidget->setFocus();

    });

    /*
    auto loginPage = qobject_cast<LoginPage*>(ui->loginPageWidget);
    connect(loginPage, &LoginPage::loginSucceeded, this, [this]{
        ui->stackedWidget->setCurrentWidget(ui->monitoringPageWidget); //다음페이지 이동
        ui->stackedWidget->setFocus();
    });
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
