#ifndef L_LEVELPROXYMODEL_H
#define L_LEVELPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

class LevelProxyModel : public QSortFilterProxyModel
{
public:
    explicit LevelProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {}

    void setT12Column(int column)
    {
        m_t12Column = column;
    }

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &parent) const override
    {
        QModelIndex idx = sourceModel()->index(sourceRow, m_t12Column, parent);
        return idx.data().toDouble() > 0.01;
    }

private:
    int m_t12Column = 7;
};


#endif // L_LEVELPROXYMODEL_H
