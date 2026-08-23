#ifndef D_DRAWINGOPTIONS_H
#define D_DRAWINGOPTIONS_H

#include <QDialog>

namespace Ui {
class drawingChoiceDlg;
}
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

class drawingChoiceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit drawingChoiceDlg(QWidget *parent = nullptr);
    ~drawingChoiceDlg();

    QString getDrawChoice();

private:
    Ui::drawingChoiceDlg *ui;
};

#endif // D_DRAWINGOPTIONS_H
