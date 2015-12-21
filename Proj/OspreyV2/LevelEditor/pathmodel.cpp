#include "pathmodel.h"

PathModel::PathModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    pathList = NULL;
}


/**
 * @brief PathModel::rowCount
 * @param parent
 * @return
 */
int PathModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent);
    if(pathList){
        return pathList->size();
    }
    return 0;
}

/**
 * @brief PathModel::columnCount
 * @param parent
 * @return
 */
int PathModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent);
    return 2;
}

QVariant PathModel::data(const QModelIndex &index, int role) const
{
    if(pathList && index.isValid()){
       if (role == Qt::DisplayRole || role == Qt::EditRole){
           switch(index.column()){
           case 0:
               return pathList->at(index.row()).x();
           case 1:
               return pathList->at(index.row()).y();
           }
       }
    }
    return QVariant();
}

/**
 * @brief PathModel::setData
 * @param index
 * @param value
 * @param role
 * @return
 */
bool PathModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(pathList && index.isValid() && role == Qt::EditRole){
        switch(index.column()){
        case 0:
            pathList->operator [](index.row()).setX(value.toFloat());
            break;
        case 1:
            pathList->operator [](index.row()).setY(value.toFloat());
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/**
 * @brief PathModel::headerData
 * @param section
 * @param orientation
 * @param role
 * @return
 */
QVariant PathModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case 0:
                return "X Position";
            case 1:
                return "Y Position";
            }
        }else if(orientation == Qt::Vertical){
            return section;
        }
    }
    return QVariant();
}

/**
 * @brief PathModel::insertRows
 * @param row
 * @param count
 * @param parent
 * @return
 */
bool PathModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count);
    if(pathList){
        beginInsertRows(parent, row, row);
        pathList->insert(row, Point());
        endInsertRows();
        return true;
    }
    return false;
}

/**
 * @brief PathModel::copyRow
 * @param row
 * @return
 */
bool PathModel::copyRow(int row)
{
    if(pathList && !pathList->isEmpty() &&
            row >= 0 && row < pathList->size()){
        beginInsertRows(QModelIndex(), row, row);

        pathList->insert(row,Point(pathList->at(row)));
        endInsertRows();
        return true;
    }
    return false;
}

/**
 * @brief PathModel::removeRows
 * @param row
 * @param count
 * @param parent
 * @return
 */
bool PathModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count);
    if(pathList){
        beginRemoveRows(parent,row,row);
        pathList->takeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

/**
 * @brief PathModel::flags
 * @param index
 * @return
 */
Qt::ItemFlags PathModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

/**
 * @brief PathModel::reset
 */
void PathModel::reset()
{
    if(pathList){
        if(!pathList->isEmpty()){
            beginResetModel();
            pathList->clear();

            endResetModel();
        }
    }
}

/**
 * @brief PathModel::setPath
 * @param paths
 */
void PathModel::setPath(QVector<Point> *paths)
{
    beginResetModel();
    pathList = paths;
    endResetModel();

}
