#ifndef CPP_ISOMERAPI_H
#define CPP_ISOMERAPI_H

#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QList>
#include <QVector>
#include <QHash>

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

    QStringList headerNames;

    QHash<QPair<int, int>, Isotope> prepData();

private slots:
    void applyFilters();
    void openDrawing();
    void sumStatRefresh();
    void clearFilters();

private:
    void sourceFilter();
    void refreshTableView();
    QVariant queryModel(const QString &queryRequest);

    Ui::IsomerAPI *ui;

    QSqlDatabase dbLevels;
    QSqlDatabase dbGammas;
    QSqlQuery query;
    QSqlQueryModel *model;
    QList<QLineEdit*> filterBounds;

    QString dbPathLevels;
    QString dbPathGammas;
    QString activeFilter;
    QStringList entrySources;
};
#endif // CPP_ISOMERAPI_H
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
