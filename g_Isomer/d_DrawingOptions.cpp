#include "d_DrawingOptions.h"
#include "ui_d_DrawingOptions.h"

//--------------------------------------------------------
drawingChoiceDlg::drawingChoiceDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::drawingChoiceDlg)
{
    ui->setupUi(this);
}
//--------------------------------------------------------
drawingChoiceDlg::~drawingChoiceDlg()
{
    delete ui;
}

//--------------------------------------------------------
QString drawingChoiceDlg::getDrawChoice()
{
    QString ss;

    if (ui->rb_filtered->isChecked()) {
        ss = "filt";
    } else if (ui->rb_lvlSelected->isChecked()) {
        ss = "lvl";
    } else if (ui->rb_gamSelected->isChecked()) {
        ss = "gam";
    } else { ss = ""; }
    return ss;
}
//--------------------------------------------------------
