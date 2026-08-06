#include "o_cacheLevelProxy.h"

cacheLevelProxy::cacheLevelProxy(QObject *parent)
    :QSortFilterProxyModel(parent)
{

}

/// ~~~~~ This needs to be fixed. filter accept always has mismatch of m_firstOccurrence and sourceRow values
void cacheLevelProxy::rebuildCache()
{
    m_firstOccurrence.clear();
    qDebug() << "[rebuildCache: triggered]";

    if (!sourceModel()) {
        qDebug() << "[rebuildCache: NO SOURCE]";
        return;
    }

    for (int row = 0; row < sourceModel()->rowCount(); ++row)
    {
        int id = sourceModel()->index(row, m_LEVEL_IDcolumn).data().toInt();

        // only keep the first row for each LEVEL_ID
        if (!m_firstOccurrence.contains(id)) {
            m_firstOccurrence.insert(id, row);
            qDebug() << "[rebuildCache: KEEP ID]" << id << row;
        }
    }

    invalidateFilter();
}


/// ~~~~~ This needs to be fixed. filter accept always has mismatch of m_firstOccurrence and sourceRow values

bool cacheLevelProxy::filterAcceptsRow(int sourceRow,
                                       const QModelIndex &parent) const
{
    QModelIndex idx = sourceModel()->index(sourceRow, m_t12Column, parent);

    if (idx.data().toDouble() <= 0.01)
        return false;

    int id = sourceModel()->index(sourceRow, m_LEVEL_IDcolumn).data().toInt();
    qDebug() << "[cache filterAcceptsRow:]" << (m_firstOccurrence.value(id) == sourceRow) << id << sourceRow << m_firstOccurrence.value(id);
    return m_firstOccurrence.value(id) == sourceRow;
}
