#ifndef LISTPAGE_H
#define LISTPAGE_H

#include <QWidget>
#include<QListWidgetItem>
#include "adddialog.h"

namespace Ui {
class ListPage;
}

class ListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ListPage(QWidget *parent = nullptr);
    ~ListPage();

private slots:
    void on_DeviceList_itemDoubleClicked(QListWidgetItem *item);

    void on_Add_clicked();

    void on_Edit_clicked();

    void on_Delete_clicked();

signals:
    void connection(QString ip,int port);

private:
    Ui::ListPage *ui;
    void saveDevice(QString name,QString ip,QString port);
    void loadDevices();
    void editDevice(QString name,QString ip,QString port);
    AddDialog adddialog;

    QString exeDir;
    QString filePath;
};

#endif // LISTPAGE_H
