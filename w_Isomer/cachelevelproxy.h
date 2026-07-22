#ifndef CACHELEVELPROXY_H
#define CACHELEVELPROXY_H

#include "qsortfilterproxymodel.h"
class cacheLevelProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    // cacheLevelProxy();

    explicit cacheLevelProxy(QObject *parent = nullptr);

    void setLEVEL_IDColumn(int col) {
        m_LEVEL_IDcolumn = col;
    }
    void setT12Column(int col) {
        m_t12Column = col;
    }

    void rebuildCache();

    QHash<int, int> m_firstOccurrence;


protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &parent) const override;

private:
    int m_LEVEL_IDcolumn = -1;
    int m_t12Column = -1;

    // QHash<int, int> m_firstOccurrence;
};



// class cacheLevelProxy : public QSortFilterProxyModel
// {
//     Q_OBJECT

// public:
//     explicit LevelProxyModel(QObject *parent = nullptr);

//     void setLevelIDColumn(int col) { m_LEVEL_IDcolumn = col; }
//     void setT12Column(int col) { m_t12Column = col; }

//     void rebuildCache();

// protected:
//     bool filterAcceptsRow(int sourceRow,
//                           const QModelIndex &parent) const override;

// private:
//     int m_LEVEL_IDcolumn = -1;
//     int m_t12Column = -1;

//     QHash<int, int> m_firstOccurrence;
// };

#endif // CACHELEVELPROXY_H


