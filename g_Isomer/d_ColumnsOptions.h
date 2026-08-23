#ifndef D_COLUMNSOPTIONS_H
#define D_COLUMNSOPTIONS_H

#include <QDialog>

namespace Ui {
class columnToggleDlg;
}

class columnToggleDlg : public QDialog
{
    Q_OBJECT

public:
    explicit columnToggleDlg(QWidget *parent = nullptr);
    ~columnToggleDlg();

public slots:


private:
    Ui::columnToggleDlg *ui;
};

#endif // D_COLUMNSOPTIONS_H
