#include "leveleditor.h"
#include "ui_leveleditor.h"

#include <QMessageBox>

levelEditor::levelEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::levelEditor)
{
    //setup form
    ui->setupUi(this);

    //init models and delegates
    entryModel = new EntryModel(this);
    delegate = new EntryDelegate(this);
    pathModel = new PathModel(this);

    setWindowModified(false);

    //connect views to models, init view params

    ui->entryTable->setModel(entryModel);

    ui->entryTable->setItemDelegate(delegate);
    ui->entryTable->resizeRowsToContents();
    ui->entryTable->horizontalHeader()->setStretchLastSection(true);
    ui->entryTable->verticalHeader()->setVisible(true);
    ui->entryTable->setColumnHidden(6, true);
    ui->entryTable->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                    QAbstractItemView::DoubleClicked);
    ui->entryTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->entryTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pathTable->setModel(pathModel);
    ui->pathTable->resizeRowsToContents();
    ui->pathTable->horizontalHeader()->setStretchLastSection(true);
    ui->pathTable->verticalHeader()->setVisible(true);
    ui->pathTable->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                   QAbstractItemView::DoubleClicked);
    ui->pathTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->pathTable->setSelectionMode(QAbstractItemView::SingleSelection);

    entrySelectModel = ui->entryTable->selectionModel();
    pathSelectModel = ui->pathTable->selectionModel();

    //connext model signals and slots
    connect(entrySelectModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            entryModel,SLOT(entryRow(QModelIndex,QModelIndex)));
   connect(entryModel,SIGNAL(entryPath(QVector<Point>*)),
           pathModel, SLOT(setPath(QVector<Point>*)));
   connect(entryModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
           this, SLOT(modelModified()));
   connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newFile()));
   connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
   connect(ui->actionSave_As, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
   connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));

   setCurrentFile("");
}

levelEditor::~levelEditor()
{
    delete ui;
}

void levelEditor::modelModified()
{
    setWindowModified(true);
}

void levelEditor::on_addEntry_clicked()
{
    //add entry button
    int row = entryModel->rowCount(QModelIndex());
    entryModel->insertRows(row,1,QModelIndex());


    QModelIndex index = entryModel->index(row, 0, QModelIndex());
    ui->entryTable->setCurrentIndex(index);
    ui->entryTable->edit(index);
    statusBar()->showMessage("Entry Added",2000);
     setWindowModified(true);
}

void levelEditor::on_copyEntry_clicked()
{
    //copy entry button
    if (entrySelectModel->selectedIndexes().isEmpty()) return;

    int row = entrySelectModel->selectedIndexes().first().row();
    if(row < entryModel->rowCount(QModelIndex()) && row >= 0){
        entryModel->copyRow(row);
        QModelIndex index = entryModel->index(row+1, 0, QModelIndex());
        ui->entryTable->edit(index);
        statusBar()->showMessage("Entry Copied", 2000);
         setWindowModified(true);
    }else{
        statusBar()->showMessage("Entry Copy Failed", 2000);
    }
}

void levelEditor::on_sortEntries_clicked()
{
    //sort entry button
    entryModel->sort();
    entrySelectModel->clear();
    statusBar()->showMessage("Entries Sorted", 2000);
}
void levelEditor::on_removeEntry_clicked()
{
    //remove entry button
    if (entrySelectModel->selectedIndexes().isEmpty()) return;

    int row = entrySelectModel->selectedIndexes().first().row();

    if(row< entryModel->rowCount(QModelIndex()) && row >= 0){
        entryModel->removeRows(row, 1, QModelIndex());
        statusBar()->showMessage("Entry Removed",2000);
         setWindowModified(true);

    }
}



void levelEditor::on_addPath_clicked()
{
    //add path
    int row = pathModel->rowCount(QModelIndex());
    pathModel->insertRows(row, 1, QModelIndex());

    QModelIndex index = pathModel->index(row, 0, QModelIndex());
    ui->pathTable->setCurrentIndex(index);
    ui->pathTable->edit(index);
    statusBar()->showMessage("Path Node Added",2000);
     setWindowModified(true);
}

void levelEditor::on_copyPath_clicked()
{
    if(pathSelectModel->selectedIndexes().isEmpty()) return;

    int row = pathSelectModel->selectedIndexes().first().row();
    if(row < pathModel->rowCount(QModelIndex()) && row >= 0){
        pathModel->copyRow(row);
        QModelIndex index = pathModel->index(row+1,0, QModelIndex());
        ui->pathTable->edit(index);
        statusBar()->showMessage("Path Copied", 2000);
        setWindowModified(true);
    }else{
        statusBar()->showMessage("Path Copy Failed", 2000);
    }
}

void levelEditor::on_deletePath_clicked()
{
    //delete path
    if(pathSelectModel->selectedIndexes().isEmpty()) return;

    int row = pathSelectModel->selectedIndexes().first().row();

    if(row < pathModel->rowCount(QModelIndex()) && row >= 0){
        pathModel->removeRows(row, 1, QModelIndex());
        statusBar()->showMessage("Path Node Removed",2000);
         setWindowModified(true);
    }
}

void levelEditor::newFile()
{
    if(okToContinue()){
        entryModel->reset();
        pathModel->reset();
        setCurrentFile("");
    }
}

bool levelEditor::save()
{
    if(curFile.isEmpty()){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool levelEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, "Save Enemy List", ".", "ENEMIES file (*.enemies)");
    if(fileName.isEmpty()){
        return false;
    }

    return saveFile(fileName);
}

void levelEditor::open()
{
    if(okToContinue()){
        QString fileName = QFileDialog::getOpenFileName(
                    this, "Open Enemy List", ".", "ENEMIES file (*.enemies)");
        if(!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

bool levelEditor::saveFile(const QString &fileName)
{
    if(!writeFile(fileName)){
        statusBar()->showMessage("Save Cancelled", 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage("File Saved", 2000);
    return true;
}

void levelEditor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = "Untitled";
    if(!curFile.isEmpty()){
        shownName = strippedName(curFile);
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg("Level Editor"));
}

bool levelEditor::writeFile(const QString &fileName)
{
    //create and validate file
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        //displate error if invalid
        QMessageBox::warning(this, "Level Editor",
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    //create JSON document from entry model
    QJsonObject entriesObject;
    entryModel->write(entriesObject);
    QJsonDocument saveDoc(entriesObject);

    //wite file
    file.write(saveDoc.toJson());
    file.close();

    return true;

}

bool levelEditor::loadFile(const QString &fileName)
{
    if(readFile(fileName)){
        statusBar()->showMessage("Loading Failed", 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage("File Loaded", 2000);
    return true;
}

bool levelEditor::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, tr("Level Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));

    if(jsonDoc.isObject()){
        entryModel->read(jsonDoc.object());
        return true;
    }
    return false;
}

bool levelEditor::okToContinue()
{
    if(isWindowModified()){
        int r = QMessageBox::warning(this, "Level Editor",
                                     "This File has been modified.\n"
                                     "Would you like to save your changes?",
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes){
            return save();
        }else if( r == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

QString levelEditor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void levelEditor::closeEvent(QCloseEvent *e)
{
    if(okToContinue()){
        e->accept();
    }else{
        e->ignore();
    }
}






