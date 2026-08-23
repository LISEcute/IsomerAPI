#include "d_TransmissionCalc.h"
#include "ui_d_TransmissionCalc.h"
#include "w_Isomer/L_IsomerElement.h"

#include <QMessageBox>

transmissionDlg::transmissionDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transmissionDlg)
{
    ui->setupUi(this);
}

std::tuple<int,int,float> transmissionDlg::getOptions(){
    QString AStr = ui->le_A->text();
    QString ZStr = ui->le_Z->text();
    QString T12Str = ui->le_T12->text();
    if (T12Str == "") T12Str = ui->le_T12->placeholderText();
    qDebug() << "[d_transm: check strings]" << AStr << ZStr << T12Str;


    if (AStr == "" || ZStr == "") {
        QMessageBox::warning(
            this,
            tr("No Isotope Selected"),
            tr("Empty A and Z selected, please enter either integers or atomic symbol to run calculation.")
            );
        return {-1,-1,-1};
    }

    int A;
    int Z;
    float T12 = T12Str.toFloat();

    bool ZInt;

    ZStr.toInt(&ZInt);
    A = AStr.toInt();
    if (!ZInt) {
        Z = atomicSymbol(ZStr);
    } else {
        Z = ZStr.toInt();
    }

    return {Z,A,T12};
}


transmissionDlg::~transmissionDlg()
{
    delete ui;
}
