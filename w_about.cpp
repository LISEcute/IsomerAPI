#include "w_about.h"
#include "ui_w_about.h"

About::About(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
