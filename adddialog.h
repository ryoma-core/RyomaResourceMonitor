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
    void setting();
    void editSetting(QString n ,QString i, QString p);
    bool add_edit_flag = false;

signals:
    void done(QString n,QString i,QString p);

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
