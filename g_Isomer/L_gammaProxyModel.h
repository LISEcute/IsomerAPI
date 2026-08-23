#ifndef L_GAMMAPROXYMODEL_H
#define L_GAMMAPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QModelIndex>

class GammaProxyModel : public QSortFilterProxyModel
{
public:
    explicit GammaProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {}

    void setGAMMAColumn(int column)
    {
        m_gamColumn = column;
    }

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &parent) const override
    {
        QModelIndex idx = sourceModel()->index(sourceRow, m_gamColumn, parent);
        return idx.data().toDouble() > 0;
    }

private:
    int m_gamColumn = 7;
};

#endif // L_GAMMAPROXYMODEL_H
