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

    std::pair<int, int> getOptions();

    explicit transmissionDlg(QWidget *parent = nullptr);
    ~transmissionDlg();

private:
    Ui::transmissionDlg *ui;
};

#endif // D_TRANSMISSIONCALC_H
