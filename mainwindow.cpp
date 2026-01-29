#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->stackedWidget->setCurrentWidget(ui->loginPageWidget);
    // ui->stackedWidget->setFocus();

    auto mon = qobject_cast<MonitoringPage*>(ui->monitoringPageWidget);
    ui->stackedWidget->setCurrentWidget(ui->listPageWidget);
    ui->stackedWidget->setFocus();

    connect(ui->listPageWidget,&ListPage::connection,this,[this,mon](QString ip,int port){
        mon->setEndpoint(ip, port);
        mon->startMonitoring();
        ui->stackedWidget->setCurrentWidget(mon);
        ui->stackedWidget->setFocus();
    });

    connect(ui->monitoringPageWidget,&MonitoringPage::goBack,this,[this]()
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
