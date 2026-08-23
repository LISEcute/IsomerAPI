#ifndef D_TRANSMISSIONCALC_H
#define D_TRANSMISSIONCALC_H

#include <QDialog>

namespace Ui {
class transmissionDlg;
}

class transmissionDlg : public QDialog
{
    Q_OBJECT

public:

    std::tuple<int,int,float> getOptions();

    explicit transmissionDlg(QWidget *parent = nullptr);
    ~transmissionDlg();

private:
    Ui::transmissionDlg *ui;
};

#endif // D_TRANSMISSIONCALC_H
