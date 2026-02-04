#include "adddialog.h"
#include "ui_adddialog.h"
#include <QToolTip>

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::Setting()
{
    ui->Name->clear();
    ui->IP->clear();
    ui->PORT->clear();
}

void AddDialog::EditSetting(QString n, QString i, QString p)
{
    ui->Name->setText(n);
    ui->IP->setText(i);
    ui->PORT->setText(p);
}


void AddDialog::on_OkButton_clicked()
{
    if(ui->Name->text().isEmpty() || ui->IP->text().isEmpty() || ui->PORT->text().isEmpty())
    {
        QToolTip::showText(ui->OkButton->mapToGlobal(QPoint(0, 0)),
                           "[ERROR] NAME / IP / PORT 전부 입력 요청.",
                           ui->OkButton);
        return;
    }
    emit Done(ui->Name->text(),ui->IP->text(),ui->PORT->text());
    accept();
}


void AddDialog::on_CancelButton_clicked()
{
    Setting();
    reject();
}

