#include "d_Transmission.h"
#include "ui_d_Transmission.h"
#include "w_Isomer/L_element.h"

transmissionDlg::transmissionDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transmissionDlg)
{
    ui->setupUi(this);
}

std::pair<int, int> transmissionDlg::getOptions(){
    QString AStr = ui->le_A->text();
    QString ZStr = ui->le_Z->text();

    int A;
    int Z;

    bool ZInt;

    ZStr.toInt(&ZInt);
    A = AStr.toInt();
    if (!ZInt) {
        Z = atomicSymbol(ZStr);
    } else {
        Z = ZStr.toInt();
    }

    return {Z,A};
}


transmissionDlg::~transmissionDlg()
{
    delete ui;
}
