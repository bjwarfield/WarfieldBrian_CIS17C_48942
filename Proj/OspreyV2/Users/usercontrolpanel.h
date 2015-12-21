#ifndef USERCONTROLPANEL_H
#define USERCONTROLPANEL_H

#include <QDialog>

namespace Ui {
class UserControlPanel;
}

class UserControlPanel : public QDialog
{
    Q_OBJECT

public:
    explicit UserControlPanel(QWidget *parent = 0);
    ~UserControlPanel();

private:
    Ui::UserControlPanel *ui;
    QString valid;
    QString invalid;
    QString defaultText;
    QString errorText;
    void clearFields(QWidget *&widget);
    void submitRegistration();

private slots:
    void checkTabs();
    void on_regCancelButton_clicked();
    void on_regFNameField_editingFinished();
    void on_regLNameField_editingFinished();
    void on_regUserField_editingFinished();
    void on_regEmailField_editingFinished();
    void on_regPassField_editingFinished();
    void on_regPassField2_editingFinished();
    void on_regRegisterButton_clicked();
    void on_loginLoginButton_clicked();
    void on_loginCancelButton_clicked();

};

#endif // USERCONTROLPANEL_H
