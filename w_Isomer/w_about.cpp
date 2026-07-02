#include "w_about.h"
#include "ui_w_about.h"
#include "w_Isomer/L_isomerAPI_version.h"

#include <QDesktopServices>

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
About::About(QWidget *parent)
    : QWidget(parent), ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_Version->setText(QStringLiteral("Version ") + isomerAPI_version);
    ui->label_Date->setText(isomerAPI_date);


    connect(ui->label_LISE, SIGNAL(clicked()), this, SLOT(CmLISE()));
    connect(ui->label_IsomerAPI, SIGNAL(clicked()), this, SLOT(CmIsomerAPI()));
    connect(ui->label_contact, SIGNAL(clicked()), this, SLOT(CmMail()));
    // connect(ui->)

}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
About::~About()
{
    delete ui;
}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void About::CmLISE() {    QDesktopServices::openUrl(QUrl(ui->label_LISE->text()));}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
void About::CmIsomerAPI()
{
    QString ss("https://lise.frib.msu.edu/porting/Hudson/JanuaryIsomerProjectUpdate.pdf");
    QDesktopServices::openUrl(QUrl(ss));
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
void About::CmMail()
{
    QString ss("mailto:miltner@frib.msu.edu?subject=IsomerAPI ");
    ss.append(ui->label_Version->text());
    QDesktopServices::openUrl(QUrl(ss));
}
