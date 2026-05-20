#ifndef W_DOWNLOADDIALOG_H
#define W_DOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
class DownloadDialog;
}

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QWidget *parent = nullptr);
    ~DownloadDialog();

private:
    Ui::DownloadDialog *ui;
};

#endif // W_DOWNLOADDIALOG_H
