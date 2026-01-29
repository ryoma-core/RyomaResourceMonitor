#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void loginSucceeded();

private slots:
    void on_LogingButton_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
