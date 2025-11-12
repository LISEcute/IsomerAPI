#ifndef CPP_ISOMERAPI_H
#define CPP_ISOMERAPI_H

#include <QMainWindow>
//#include <QWidget>
#include <QApplication>
//#include <QWidget>
#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QList>
#include <QVector>

#include "L_vectorStruct.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class IsomerAPI;
}
QT_END_NAMESPACE

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

class IsomerAPI : public QMainWindow
{
    Q_OBJECT

public:
    IsomerAPI(QWidget *parent = nullptr);
    ~IsomerAPI();

    std::tuple<QVector<Level>, QVector<Transition>> prepData();

private slots:
    void applyFilters();
    void openDrawing();
    void sumStatRefresh();
    void clearFilters();

private:

    void sourceFilter();

    QVariant queryModel(const QString &queryRequest);
    Ui::IsomerAPI *ui;

    QSqlDatabase dbIsomLevel;
    QSqlQuery query;
    QSqlTableModel *model;
    QList<QLineEdit*> filterBounds;

    QString dbPath;
    QStringList entrySources;
};
#endif // CPP_ISOMERAPI_H
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
