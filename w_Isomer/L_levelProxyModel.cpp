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


// void LevelProxyModel::clearShownLevels()
// {
//     shownLvlIDs.clear();
// }

bool LevelProxyModel::filterAcceptsRow(
    int sourceRow,
    const QModelIndex &parent) const
    {
        int id = sourceModel()->index(sourceRow, m_LEVEL_IDcolumn).data().toInt();


        // if (shownLvlIDs.contains(id)) {
        //     qDebug() << "[lvlProxy: already have level]";

        // } else {
        //     shownLvlIDs.append(id);
        // }

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

        return idT12.data().toDouble() >= 0.01 && idLEVEL.data().toDouble() > 0 && !shownLvlIDs.contains(id);

    }
