#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    void Setting();
    void EditSetting(QString n ,QString i, QString p);
    bool AddEditFlag = false;

signals:
    void Done(QString n,QString i,QString p);

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
