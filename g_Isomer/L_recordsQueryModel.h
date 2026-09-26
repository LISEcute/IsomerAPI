#include "qsqlrecord.h"
#include "w_IsomerAPI.h"
#include <QSqlQueryModel>

#ifndef L_RECORDSQUERYMODEL_H
#define L_RECORDSQUERYMODEL_H

#endif // L_RECORDSQUERYMODEL_H

class RecordsQueryModel : public QSqlQueryModel
{
public:
    explicit RecordsQueryModel(QObject *parent = nullptr)
        : QSqlQueryModel(parent) {}

    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override
    {
        if (orientation == Qt::Horizontal &&
            role == Qt::DisplayRole &&
            section >= 0 &&
            section < columnCount()) {

            const QString key = record().fieldName(section);

            if (IsomerAPI::headerMap.contains(key))
                return IsomerAPI::headerMap.value(key);
        }


        return QSqlQueryModel::headerData(section, orientation, role);
    }
};
