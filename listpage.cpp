#include "listpage.h"
#include "ui_listpage.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSaveFile>
#include <QtGlobal>

ListPage::ListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListPage)
{
    ui->setupUi(this);

    m_dir = QCoreApplication::applicationDirPath();
    m_path = QDir(m_dir).filePath("devices.json");

    LoadDevices();
    m_adddialog.Setting();

    connect(&m_adddialog,&AddDialog::Done,
           this,[this](QString n,QString i,QString p){
        if(m_adddialog.AddEditFlag)
            {
            EditDevice(n,i,p);
        }
        else{
            SaveDevice(n,i,p);
        }
    });

    m_pollingTimer.setInterval(5000); //(ms) 5.0 second
    connect(&m_pollingTimer, &QTimer::timeout, this, &ListPage::OnPolling);
    m_pollingTimer.start();
}

ListPage::~ListPage()
{
    delete ui;
}

void ListPage::SaveDevice(QString name,QString ip,QString port)
{
    int portNum = port.toInt();
    if (name.isEmpty() || ip.isEmpty() || portNum <= 0) return;

    QJsonArray arr;

    QFile readFile(m_path);
    if (readFile.exists() && readFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = readFile.readAll();
        readFile.close();

        if (!data.trimmed().isEmpty())
        {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(data, &err);
            if (err.error == QJsonParseError::NoError && doc.isArray())
                arr = doc.array();
        }
    }
    QJsonObject obj;
    obj["name"] = name;
    obj["ip"]   = ip;
    obj["port"] = portNum;
    arr.append(obj);

    QSaveFile saveFile(m_path);
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QJsonDocument outDoc(arr);
    saveFile.write(outDoc.toJson(QJsonDocument::Indented));
    saveFile.commit();
}

void ListPage::LoadDevices()
{
    ui->DeviceList->clear();

    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data = file.readAll();
    file.close();

    if (data.trimmed().isEmpty()) return;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data,&err);
    if(err.error != QJsonParseError::NoError) return;
    if(!doc.isArray()) return;

    QJsonArray arr = doc.array();

    for(const auto& v : arr)
    {
        if(!v.isObject()) continue;
        QJsonObject obj = v.toObject();
        QString name = obj["name"].toString();
        QString ip = obj["ip"].toString();
        int port = obj["port"].toInt();

        if (name.isEmpty() || ip.isEmpty() || port <= 0) continue;

        auto* item = new QListWidgetItem(name);
        item->setData(Qt::UserRole, ip);
        item->setData(Qt::UserRole + 1, port);
        ui->DeviceList->addItem(item);
    }
}

void ListPage::EditDevice(QString name,QString ip,QString port)
{
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data = file.readAll();
    file.close();

    if(data.trimmed().isEmpty()) return;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data,&err);
    if(err.error != QJsonParseError::NoError) return;
    if(!doc.isArray()) return;

    QJsonArray arr = doc.array();

    QListWidgetItem* item = ui->DeviceList->currentItem();
    if (!item) return;

    QString i_name = item->text();
    QString i_ip = item->data(Qt::UserRole).toString();
    int i_port = item->data(Qt::UserRole+1).toInt();

    for(size_t index =0u; index<arr.size();index++)
    {
        if(!arr[index].isObject()) continue;

        QJsonObject obj = arr[index].toObject();

        if (obj["name"].toString() == i_name &&
            obj["ip"].toString()   == i_ip &&
            obj["port"].toInt()    == i_port)
        {
            obj["name"] = name;
            obj["ip"]   = ip;
            obj["port"] = port.toInt();

            arr[index] = obj;
            break;
        }
    }

    QSaveFile saveFile(m_path);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QJsonDocument outDoc(arr);
    saveFile.write(outDoc.toJson(QJsonDocument::Indented));
    saveFile.commit();
    LoadDevices();
}

void ListPage::OnPolling()
{
    SetLoggerUI(m_listlogger->m_isrunning);
}

void ListPage::SetLoggerUI(bool ok)
{
    ui->Logger->setFixedSize(12, 12);
    ui->Logger->setStyleSheet(QString(
                                  "border-radius: 6px;"
                                  "border: 1px solid #333;"
                                  "background: %1;"
                                  ).arg(ok ? "#00c853" : "#d50000"));

}

void ListPage::on_DeviceList_itemDoubleClicked(QListWidgetItem *item)
{
    QString ip = item->data(Qt::UserRole).toString();
    int port   = item->data(Qt::UserRole + 1).toInt();
    QString temp = "[CONNECT] Sever Connecting";
    m_listlogger->WriteLine(temp);
    emit Connection(ip,port);
}


void ListPage::on_Add_clicked()
{
    m_adddialog.AddEditFlag= false;
    m_adddialog.Setting();
    m_adddialog.setModal(true);
    m_adddialog.exec();
    LoadDevices();
}


void ListPage::on_Edit_clicked()
{
    QListWidgetItem* item = ui->DeviceList->currentItem();
    if (!item) return;

    QString name = item->text();
    QString ip = item->data(Qt::UserRole).toString();
    QString port = QString::number(item->data(Qt::UserRole+1).toInt());

    m_adddialog.AddEditFlag= true;
    m_adddialog.EditSetting(name,ip,port);
    m_adddialog.setModal(true);
    m_adddialog.exec();
}


void ListPage::on_Delete_clicked()
{
    QListWidgetItem* item = ui->DeviceList->currentItem();
    if (!item) return;

    QString name = item->text();
    QString ip = item->data(Qt::UserRole).toString();
    int port = item->data(Qt::UserRole+1).toInt();

    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data = file.readAll();
    file.close();

    if(data.trimmed().isEmpty()) return;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data,&err);
    if(err.error != QJsonParseError::NoError) return;
    if(!doc.isArray()) return;

    QJsonArray arr = doc.array();

    for(size_t index =0u; index<arr.size();index++)
    {
        if(!arr[index].isObject()) continue;

        QJsonObject obj = arr[index].toObject();

        if (obj["name"].toString() == name &&
            obj["ip"].toString()   == ip &&
            obj["port"].toInt()    == port)
        {
            arr.removeAt(static_cast<int>(index));
            break;
        }
    }

    QSaveFile saveFile(m_path);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QJsonDocument outDoc(arr);
    saveFile.write(outDoc.toJson(QJsonDocument::Indented));
    saveFile.commit();
    LoadDevices();
}

