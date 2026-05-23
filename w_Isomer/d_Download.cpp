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
