#ifndef LEVELPROXYMODEL_H
#define LEVELPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QVector>

class LevelProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit LevelProxyModel(QObject *parent = nullptr);

    void setT12Column(int column);
    void setLEVEL_IDColumn(int column);
    void setLEVELColumn(int column);

    // void clearShownLevels();


protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

private:
    mutable QVector<int> shownLvlIDs;

    int m_t12Column = -1;
    int m_LEVELColumn = -1;
    int m_LEVEL_IDcolumn = -1;
};

#endif // LEVELPROXYMODEL_H
