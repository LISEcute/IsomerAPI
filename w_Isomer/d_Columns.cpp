#include "d_Columns.h"
#include "ui_d_Columns.h"

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
