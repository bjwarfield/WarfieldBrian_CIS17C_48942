#include "entrymodel.h"

EntryModel::EntryModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

EntryModel::~EntryModel()
{

}


int EntryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent);
    return entryList.size();
}

int EntryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent);
    return 6;
}

QVariant EntryModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()){

        if (role == Qt::TextAlignmentRole) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }else if(role == Qt::DisplayRole || role == Qt::EditRole){

            switch(index.column()){
            case 0:

                return entryList[index.row()].spawnTrigger;
            case 1:
                return entryList[index.row()].enemyClass;
            case 2:
                return entryList[index.row()].polarity == WHITE ? "WHITE" : "BLACK";
            case 3:
                return entryList[index.row()].spawnX;
            case 4:
                return entryList[index.row()].spawnY;
            case 5:
                return entryList[index.row()].spawnRef;

            }
        }
    }
    return QVariant();
}

bool EntryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        switch(index.column()){
        case 0:
            entryList[index.row()].spawnTrigger = value.toInt();
            break;
        case 1:
            entryList[index.row()].enemyClass = value.toString();
            break;
        case 2:
            entryList[index.row()].polarity = value.toString() == "WHITE" ? WHITE : BLACK;
            break;
        case 3:
            entryList[index.row()].spawnX = value.toInt();
            break;
        case 4:
            entryList[index.row()].spawnY = value.toInt();
            break;
        case 5:
            entryList[index.row()].spawnRef = value.toString();
            break;
//        case 6:
//            return entryList[index.row()].paths;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant EntryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case 0:
                return "SpawnTrigger";
            case 1:
                return "EnemyClassName";
            case 2:
                return "Polatity";
            case 3:
                return "SpawnX";
            case 4:
                return "SpawnY";
            case 5:
                return "SpawnRef";
            }
        }else if(orientation == Qt::Vertical){
            return section;
        }
    }
    return QVariant();
}

bool EntryModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(count);
    beginInsertRows(parent, row, row);
    entryList.insert(row, newEntry());
    endInsertRows();
    return true;

}

bool EntryModel::copyRow(int row)
{
    if(!entryList.isEmpty() && row >= 0 && row < entryList.size()){

        beginInsertRows(QModelIndex(),row, row);
//        EnemyEntry e;
//        e.enemyClass = entryList.at(row).enemyClass;
//        e.paths = entryList.at(row).paths;
//        e.polarity = entryList.at(row).polarity;
//        e.spawnRef = entryList.at(row).spawnRef;
//        e.spawnTrigger = entryList.at(row).spawnTrigger;
//        e.spawnX = entryList.at(row).spawnX;
//        e.spawnY = entryList.at(row).spawnY;

        entryList.insert(row, entryList.at(row));
        endInsertRows();

        return true;
    }
    return false;
}

bool EntryModel::removeRows(int row, int count, const QModelIndex &parent)
{

    Q_UNUSED(count);
    beginRemoveRows(parent,row,row);
    entryList.takeAt(row);
    endRemoveRows();
    return true;

}

void EntryModel::reset()
{
    beginResetModel();
    entryList.clear();
    emit entryPath(NULL);
    endResetModel();
}

void EntryModel::sort()
{
    beginResetModel();
    entryList.sort();
    emit entryPath(NULL);
    endResetModel();
}

void EntryModel::read(const QJsonObject &json)
{
    beginResetModel();
    entryList.clear();

    QJsonArray enemyList = json["enemyList"].toArray();
    if(enemyList.size() > 0){
        for(int i = 0; i < enemyList.size(); i++){
            QJsonObject je = enemyList[i].toObject();

            EnemyEntry entry;
            entry.spawnTrigger = je["spawnTrigger"].toInt();
            entry.enemyClass = je["enemyClassName"].toString();
            entry.polarity = je["polarity"].toInt() % 2 == 0 ? WHITE : BLACK;
            entry.spawnX = je["spawnX"].toInt();
            entry.spawnY = je["spawnY"].toInt();

            QJsonArray pathList = je["paths"].toArray();
            for (int j = 0; j < pathList.size(); ++j) {
                QJsonArray path = pathList.at(j).toArray();
                entry.paths.append(Point(path.at(0).toInt(),path.at(1).toInt()));
            }

            entry.spawnRef = je["spawnRef"].toString();

            entryList.append(entry);
        }
    }
    endResetModel();

}

void EntryModel::write(QJsonObject &json) const
{
    DList<EnemyEntry>::const_iterator itr;

    QJsonArray enemyList;
    for (itr = entryList.cbegin(); itr != entryList.cend(); itr++){
        QJsonObject entry;
        entry["spawnTrigger"] = itr->spawnTrigger;
        entry["enemyClassName"] = itr->enemyClass;
        entry["polarity"] = itr->polarity == WHITE ? 0 : 1;
        entry["spawnX"] = itr->spawnX;
        entry["spawnY"] = itr->spawnY;
        entry["spawnRef"] = itr->spawnRef;

        QJsonArray pathList;

        for(int j = 0; j < itr->paths.size(); j++){
            QJsonArray path = {itr->paths.at(j).x(), itr->paths.at(j).y()};
//            path.append(itr->paths[j].x());
//            path.append(itr->paths[j].y());
            pathList.append(path);
        }
        entry["paths"] = pathList;
        enemyList.append(entry);
    }

    json["enemyList"] = enemyList;

}
EnemyEntry EntryModel::newEntry()
{
    EnemyEntry entry;
    entry.spawnTrigger = 0;
    entry.enemyClass = "EnemyScout";
    entry.polarity = WHITE;
    entry.spawnX = 0;
    entry.spawnY = 0;
    entry.spawnRef = "Test";

    return entry;
}

void EntryModel::entryRow(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid()){
        emit entryPath(&entryList[current.row()].paths);
    }else{
//        QVector<Point> * entryPaths = NULL;
        emit entryPath(NULL);
    }
}


Qt::ItemFlags EntryModel::flags(const QModelIndex &index) const
{

    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}





