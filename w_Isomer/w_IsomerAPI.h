#ifndef CPP_ISOMERAPI_H
#define CPP_ISOMERAPI_H

#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlDatabase>
#include <QSqlTableModel>
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

    // ~~~~~ QPair<int,int> acts as isotope key with A,Z number
    QHash<QPair<int,int>,Isotope> selectedIsotopes;

    // std::tuple<QVector<Level>, QVector<Transition>> prepData();

private slots:
    void applyFilters();
    void openDrawing();
    void statRefresh();
    void clearFilters();

private:

    void sourceFilter();

    QVariant queryModel(const QString &queryRequest);
    QString queryStr;

    Ui::IsomerAPI *ui;

    QSqlDatabase dbIsomLevel;
    QSqlQuery query;
    QSqlTableModel *model;

    QList<QLineEdit*> filterBounds;
    QList<QLineEdit*> summaryStats;

    QString dbPath;
    QStringList entrySources;
};
#endif // CPP_ISOMERAPI_H
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
