#ifndef PATHMODEL_H
#define PATHMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "TileMap/entitymap.h"

class PathModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PathModel(QObject *parent = 0);

    // QAbstractItemModel interface
public:
    int             rowCount(const QModelIndex &parent) const;
    int             columnCount(const QModelIndex &parent) const;
    QVariant        data(const QModelIndex &index, int role) const;
    bool            setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant        headerData(int section, Qt::Orientation orientation, int role) const;
    bool            insertRows(int row, int count, const QModelIndex &parent);
    bool            removeRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags   flags(const QModelIndex &index) const;
    void            reset();
    bool            copyRow(int row);

public slots:
    void setPath(QVector<Point> *paths);

private:
    QVector<Point> *pathList;

};

#endif // PATHMODEL_H
