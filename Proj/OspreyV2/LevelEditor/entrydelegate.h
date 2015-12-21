#ifndef ENTRYDELEGATE_H
#define ENTRYDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>
#include <QComboBox>


class EntryDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit EntryDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:
public slots:
    void commitAndCloseEditor();

    // QAbstractItemDelegate interface
public:
};

#endif // ENTRYDELEGATE_H
