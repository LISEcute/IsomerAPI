#include "w_about.h"
#include "ui_w_about.h"
#include "w_Isomer/L_isomerAPIversion.h"

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
About::About(QWidget *parent)
    : QWidget(parent), ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_Version->setText(isomerAPI_version);
    ui->label_Date->setText(isomerAPI_date);
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
About::~About()
{
    delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
