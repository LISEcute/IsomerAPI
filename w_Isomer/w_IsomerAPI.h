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
#include <QTableView>
#include <QMap>
#include <QSortFilterProxyModel>

#include "L_gammaProxyModel.h"
#include "L_levelProxyModel.h"
#include "L_vectorStruct.h"
#include "o_cacheLevelProxy.h"

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


    QMap<QPair<int, int>, Isotope> prepData();

    void writeDecayTXT(QPair<int,int> isoKey);

private slots:

    void on_actionAbout_triggered();
    void on_actionSave_As_triggered();
    void on_actionCalc_Transmission_triggered();
    void on_actionExit_triggered();


    void applyFilters();
    void sourceFilter();
    QVariant queryModel(const QString &queryRequest);

    void statRefresh();
    void openDrawing();
    void clearFilters();

    void onRowSelected(QTableView *view);
    void clearSelection(int widgetIndex);
    bool checkSelection(int widgetIndex);




private:

    Ui::IsomerAPI *ui;
    QSqlDatabase dbIsomLevel;
    QString dbPath;
    QStringList headerNames;

    QSqlTableModel *modelFull;
    LevelProxyModel *levelProxy;
    GammaProxyModel *gammaProxy;

    cacheLevelProxy *cacheLevel;

    QSqlQueryModel *levelQuery;
    QSqlQueryModel *gammaQuery;


    QSqlTableModel *modelIsomers;
    QSqlTableModel *modelGammas;

    QVector<std::tuple<QAbstractItemModel*, QTableView*>> modelTuples;
    QVector<QSqlTableModel*> modelsVector;
    QSortFilterProxyModel *proxyModel;
    QMap<QPair<int,int>,Isotope> filteredIsotopes;    // QPair<int,int> acts as isotope key with A,Z number


    QList<QLineEdit*> filterBounds;
    QStringList entrySources;
    QList<QLineEdit*> summaryStats;
    QString queryStr;
    QSqlQuery query;
    int currentPage;

};
#endif // CPP_ISOMERAPI_H
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
