#ifndef LISTPAGE_H
#define LISTPAGE_H

#include <QWidget>
#include<QListWidgetItem>
#include "adddialog.h"
#include "logger.h"
#include <QTimer>

namespace Ui {
class ListPage;
}

class ListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ListPage(QWidget *parent = nullptr);
    ~ListPage();
    void SettingLogger(std::shared_ptr<Logger>& log){m_listlogger=log;}

private slots:
    void on_DeviceList_itemDoubleClicked(QListWidgetItem *item);

    void on_Add_clicked();

    void on_Edit_clicked();

    void on_Delete_clicked();

signals:
    void Connection(QString ip,int port);

private:
    Ui::ListPage *ui;
    void SaveDevice(QString name,QString ip,QString port);
    void LoadDevices();
    void EditDevice(QString name,QString ip,QString port);
    void OnPolling();
    void SetLoggerUI(bool ok);
    // ------------------- //

    AddDialog m_adddialog;

    QString m_dir;
    QString m_path;
    QTimer m_pollingTimer;

    std::shared_ptr<Logger> m_listlogger;
};

#endif // LISTPAGE_H
