#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include "TileMap/entitymap.h"
#include "LevelEditor/entrymodel.h"
#include "LevelEditor/entrydelegate.h"
#include "LevelEditor/pathmodel.h"

namespace Ui {
class levelEditor;
}

class levelEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit levelEditor(QWidget *parent = 0);
    ~levelEditor();

private slots:
    void modelModified();
    void on_addEntry_clicked();
    void on_removeEntry_clicked();
    void on_addPath_clicked();
    void on_deletePath_clicked();

    //file members
    void newFile();
    bool save();
    bool saveAs();
    void open();

    void on_copyEntry_clicked();

    void on_copyPath_clicked();

    void on_sortEntries_clicked();

private:

    QString curFile;
    Ui::levelEditor *ui;
    EntryModel *entryModel;
    QSortFilterProxyModel *pmodel;
    QItemSelectionModel *entrySelectModel;
    EntryDelegate *delegate;

    PathModel *pathModel;
    QItemSelectionModel *pathSelectModel;

    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    bool readFile(const QString &fileName);
    bool okToContinue();
    QString strippedName(const QString &fullFileName);




    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};





#endif // LEVELEDITOR_H
