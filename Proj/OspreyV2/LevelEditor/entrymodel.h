#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H
#include <QtCore>
#include "TileMap/entitymap.h"
#include <QAbstractTableModel>

class EntryModel:public QAbstractTableModel
{
    Q_OBJECT
public:
    EntryModel(QObject *parent = 0);
    ~EntryModel();



    int             rowCount(const QModelIndex &parent) const;
    int             columnCount(const QModelIndex &parent) const;
    QVariant        data(const QModelIndex &index, int role) const;
    bool            setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant        headerData(int section, Qt::Orientation orientation, int role) const;
    bool            insertRows(int row, int count, const QModelIndex &parent);
    bool            copyRow(int row);
    Qt::ItemFlags   flags(const QModelIndex &index) const;
    bool            removeRows(int row, int count, const QModelIndex &parent);
    void            reset();
    void            sort();


    //Json stuff
    void            read(const QJsonObject &json);
    void            write(QJsonObject &json)const;

private:
    DList<EnemyEntry> entryList;
    EnemyEntry      newEntry();

signals:
    void            entryPath(QVector<Point> *paths);


public slots:
    void            entryRow(const QModelIndex &current, const QModelIndex &previous);
};


#endif // ENTRYMODEL_H
