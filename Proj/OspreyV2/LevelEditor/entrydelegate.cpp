#include "entrydelegate.h"

#include <QLineEdit>

EntryDelegate::EntryDelegate(QObject *parent):
    QItemDelegate(parent)
{ }



QWidget *EntryDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if(index.column() == 0 || index.column() == 3 || index.column() == 4){
        QSpinBox *editor = new QSpinBox(parent);
        editor->setRange(-100000, 100000);
        editor->setSingleStep(50);
        return editor;
    }else if(index.column() == 1 || index.column() == 2){
            QComboBox *editor = new QComboBox(parent);
            switch(index.column()){
            case 1:
                editor->addItem("EnemyProbe");
                editor->addItem("EnemyScout");
                editor->addItem("EnemyPestilence");
                editor->addItem("EnemyScarab");
                editor->addItem("EnemyCruiser");
                editor->addItem("EnemyCruiser");
                break;
            case 2:
                editor->addItem("WHITE");
                editor->addItem("BLACK");
                break;
            }
            return editor;
    }
    QLineEdit *editor = new QLineEdit(parent);

    connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
    return editor;

}
void EntryDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(editor);
    if (edit) {
        edit->setText(index.model()->data(index, Qt::DisplayRole).toString());
        return;
    }
    QSpinBox *numEdit = qobject_cast<QSpinBox *>(editor);
    if(numEdit){
        numEdit->setValue(index.model()->data(index, Qt::DisplayRole).toInt());
        return;
    }
    QComboBox *comboEdit = qobject_cast<QComboBox *>(editor);
    if(comboEdit){

            comboEdit->setCurrentIndex(comboEdit->findText(index.model()->data(index, Qt::DisplayRole).toString()));

        return;
    }

}

void EntryDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
    if (edit) {
        model->setData(index, edit->text());
        return;
    }
    QSpinBox *numEdit = qobject_cast<QSpinBox *>(editor);
    if(numEdit){
        model->setData(index, numEdit->value());
    }
    QComboBox *comboEdit = qobject_cast<QComboBox *>(editor);
    if(comboEdit){
        model->setData(index, comboEdit->currentText());
    }

}

void EntryDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
