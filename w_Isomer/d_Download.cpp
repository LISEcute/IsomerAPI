#include "d_Download.h"
#include "ui_d_Download.h"

DownloadDialog::DownloadDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DownloadDialog)
{
    ui->setupUi(this);
}

DownloadDialog::~DownloadDialog()
{
    delete ui;
}

QString DownloadDialog::getSelection(){
    QString ss;
    qDebug() << "[downloadDlg getSelection: checked sqlite/csv?]" << ui->rb_csv->isChecked() << ui->rb_sqlite->isChecked();
    if (ui->rb_csv->isChecked()) { ss = "CSV"; }
    else if (ui->rb_sqlite->isChecked()) { ss = "SQLite"; }
    else { ss = "[downloadDlg: No selection]"; }
    return ss;
}
