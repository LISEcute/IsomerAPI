#ifndef W_ABOUT_H
#define W_ABOUT_H

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private slots:
    void CmLISE();
    void CmIsomerAPI();
    void CmMail();

private:
    Ui::About *ui;
};

#endif // W_ABOUT_H
