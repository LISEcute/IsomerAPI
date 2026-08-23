#include "L_levelProxyModel.h"

#include <QDebug>


LevelProxyModel::LevelProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}


void LevelProxyModel::setT12Column(int column)
{
    m_t12Column = column;
}


void LevelProxyModel::setLEVEL_IDColumn(int column)
{
    m_LEVEL_IDcolumn = column;
}


void LevelProxyModel::setLEVELColumn(int column)
{
    m_LEVELColumn = column;
}

void LevelProxyModel::rebuildCache()
{
    m_firstLevelRows.clear();
    m_cachedRowCount = sourceModel() ? sourceModel()->rowCount() : 0;

    if (!sourceModel() || m_LEVEL_IDcolumn < 0) {
        invalidateFilter();
        return;
    }

    for (int row = 0; row < m_cachedRowCount; ++row) {
        const int id = sourceModel()->index(row, m_LEVEL_IDcolumn).data().toInt();
        if (!m_firstLevelRows.contains(id)) {
            m_firstLevelRows.insert(id, row);
        }
    }

    invalidateFilter();
}

void LevelProxyModel::ensureCache() const
{
    const int currentRowCount = sourceModel() ? sourceModel()->rowCount() : 0;
    if (currentRowCount == m_cachedRowCount) {
        return;
    }

    m_firstLevelRows.clear();
    m_cachedRowCount = currentRowCount;

    if (!sourceModel() || m_LEVEL_IDcolumn < 0) {
        return;
    }

    for (int row = 0; row < currentRowCount; ++row) {
        const int id = sourceModel()->index(row, m_LEVEL_IDcolumn).data().toInt();
        if (!m_firstLevelRows.contains(id)) {
            m_firstLevelRows.insert(id, row);
        }
    }
}


// void LevelProxyModel::clearShownLevels()
// {
//     shownLvlIDs.clear();
// }

bool LevelProxyModel::filterAcceptsRow(
    int sourceRow,
    const QModelIndex &parent) const
    {
        ensureCache();

        int id = sourceModel()->index(sourceRow, m_LEVEL_IDcolumn).data().toInt();

        QModelIndex idT12 = sourceModel()->index(sourceRow, m_t12Column, parent);
        QModelIndex idLEVEL = sourceModel()->index(sourceRow, m_LEVELColumn, parent);

        return idT12.data().toDouble() >= 0.01
               && idLEVEL.data().toDouble() > 0
               && m_firstLevelRows.value(id, -1) == sourceRow;

    }
