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


    QHash<QPair<int, int>, Isotope> prepData();

private slots:

    void on_action_About_triggered();
    void on_pb_downloadCSV_clicked();

    void applyFilters();
    void sourceFilter();
    void openDrawing();
    void clearFilters();
    void viewSelect();

private:

    void statRefresh();
    QVariant queryModel(const QString &queryRequest);

    Ui::IsomerAPI *ui;
    QSqlDatabase dbIsomLevel;
    QString dbPath;
    QStringList headerNames;

    QSqlTableModel *modelFull;
    QSqlTableModel *modelIsomers;
    QSqlTableModel *modelGammas;
    QVector<std::tuple<QSqlTableModel*, QString, QTableView*>> modelTuples;
    QVector<QSqlTableModel*> modelsVector;
    QHash<QPair<int,int>,Isotope> selectedIsotopes;    // QPair<int,int> acts as isotope key with A,Z number


    QList<QLineEdit*> filterBounds;
    QStringList entrySources;
    QList<QLineEdit*> summaryStats;
    QString queryStr;
    QSqlQuery query;

};
#endif // CPP_ISOMERAPI_H
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
