#include "d_DrawingOptions.h"
#include "ui_d_DrawingOptions.h"

drawingChoiceDlg::drawingChoiceDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::drawingChoiceDlg)
{
    ui->setupUi(this);
}

drawingChoiceDlg::~drawingChoiceDlg()
{
    delete ui;
}


int drawingChoiceDlg::getDrawChoice(){
    int ss;
    if (ui->rb_filtered->isChecked()) {
        ss = 1;
    } else if (ui->rb_lvlSelected->isChecked()) {
        ss = 2;
    } else if (ui->rb_gamSelected->isChecked()) {
        ss = 3;
    } else { ss = 0; }
    return ss;
}
