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

    void setLEVEL_IDColumn(int column) {
        m_LEVEL_IDcolumn = column;
    }

    void setLEVELColumn(int column) {
        m_LEVELColumn = column;
    }

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &parent) const override
    {
        int id = sourceModel()->index(sourceRow, m_LEVEL_IDcolumn).data().toInt();


        /// ---------
        /// ~~~~ THIS LOOP RUNS EXPONENTIALLY SLOWER AS YOU SCROLL TO LOAD MORE ROWS
        for (int i = 0; i < sourceRow; ++i)
        {
            if (sourceModel()->index(i, m_LEVEL_IDcolumn).data().toInt() == id)
                return false;
        }
        /// ---------

        QModelIndex idT12 = sourceModel()->index(sourceRow, m_t12Column, parent);
        QModelIndex idLEVEL = sourceModel()->index(sourceRow, m_LEVELColumn, parent);

        return idT12.data().toDouble() > 0.01 && idLEVEL.data().toDouble() > 0;

        // QModelIndex idx = sourceModel()->index(sourceRow, m_t12Column, parent);
        // return idx.data().toDouble() > 0.01;
    }

private:
    int m_t12Column;
    int m_LEVELColumn;
    int m_LEVEL_IDcolumn;
};


#endif // L_LEVELPROXYMODEL_H
