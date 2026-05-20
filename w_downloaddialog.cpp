#include "w_downloaddialog.h"
#include "ui_w_downloaddialog.h"

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
