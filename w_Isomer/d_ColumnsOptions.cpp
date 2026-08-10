#include "d_ColumnsOptions.h"
#include "ui_d_ColumnsOptions.h"

columnToggleDlg::columnToggleDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::columnToggleDlg)
{
    ui->setupUi(this);
}

columnToggleDlg::~columnToggleDlg()
{
    delete ui;
}
