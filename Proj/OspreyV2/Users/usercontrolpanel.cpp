#include "usercontrolpanel.h"
#include "ui_usercontrolpanel.h"
#include "user.h"
#include "Util/regex.h"
#include "Util/dbconnect.h"

#include <QMessageBox>

UserControlPanel::UserControlPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserControlPanel)
{
    valid = "background-color:#CFC; color:#363;";
    invalid = "background-color:#FCC; color:#633;";
    defaultText = "background-color:#FFF; color:#000;";
    errorText = "color:#F00;";

    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(checkTabs()));
    checkTabs();
}

UserControlPanel::~UserControlPanel()
{
    delete ui;
}

void UserControlPanel::clearFields(QWidget *&widget)
{
    QList<QLineEdit *> editFields = widget->findChildren<QLineEdit *>
            (QString(), Qt::FindDirectChildrenOnly );

    foreach(QLineEdit *field, editFields){
        field->clear();
        field->setStyleSheet(defaultText);
    }

    QList<QLabel *> labels = widget->findChildren<QLabel *>
            (QString(), Qt::FindDirectChildrenOnly);

    foreach (QLabel* l, labels) {
        if(l->styleSheet().compare(errorText) == 0){
            l->clear();
        }
    }
}



void UserControlPanel::checkTabs()
{
    if(ui->tabWidget->currentWidget() == ui->homeTab){
        if(User::isLoggedIn()){
            clearFields(ui->scoreTab);
            ui->tabWidget->setCurrentWidget(ui->scoreTab);
            ui->homeTab->setEnabled(false);
            ui->registerTab->setEnabled(true);
            ui->scoreTab->setEnabled(true);
            //TODO populate Score from DB
        }else{
            clearFields(ui->homeTab);
            ui->homeTab->setEnabled(true);
            ui->registerTab->setEnabled(true);
            ui->scoreTab->setEnabled(false);
        }
    }else if(ui->tabWidget->currentWidget() == ui->registerTab){
        if(User::isLoggedIn()){
            User::logout();
            ui->tabWidget->setTabText(2, "Register");
            ui->homeTab->setEnabled(true);
            ui->registerTab->setEnabled(true);
            ui->scoreTab->setEnabled(false);
        }else{
            clearFields(ui->registerTab);
            ui->homeTab->setEnabled(true);
            ui->registerTab->setEnabled(true);
            ui->scoreTab->setEnabled(false);
        }
    }
}

void UserControlPanel::on_regCancelButton_clicked()
{
    //registration cancel button
    clearFields(ui->homeTab);
    ui->tabWidget->setCurrentWidget(ui->homeTab);
    ui->scoreTab->setEnabled(false);
    ui->registerTab->setEnabled(true);
}

void UserControlPanel::on_regFNameField_editingFinished()
{
    if(ui->regFNameField->text().length() > 0){
        if(matchName(ui->regFNameField->text())){
            ui->regFNameField->setStyleSheet(valid);
            ui->regFNameValid->setText("");
        }else{
            ui->regFNameField->setStyleSheet(invalid);
            ui->regFNameValid->setText("<html>Valid Name must be 1-20 Alphabetic characters</html>");
        }
    }else{
        ui->regFNameField->setStyleSheet(invalid);
        ui->regFNameValid->setText("<html>First Name Required</html>");
    }
}

void UserControlPanel::on_regLNameField_editingFinished()
{
    if(ui->regLNameField->text().length() > 0){
        if(matchName(ui->regLNameField->text())){
            ui->regLNameField->setStyleSheet(valid);
            ui->regLNameValid->setText("");
        }else{
            ui->regLNameField->setStyleSheet(invalid);
            ui->regLNameValid->setText("<html>Valid Name must be 1-20 Alphabetic characters</html>");
        }
    }else{
        ui->regLNameField->setStyleSheet(invalid);
        ui->regLNameValid->setText("<html>Last Name Required</html>");
    }
}

void UserControlPanel::on_regUserField_editingFinished()
{
    if(ui->regUserField->text().length() > 0){
        if(matchUser(ui->regUserField->text())){
            ui->regUserField->setStyleSheet(valid);
            ui->regUserValid->setText("");
        }else{
            ui->regUserField->setStyleSheet(invalid);
            ui->regUserValid->setText("<html>Handle must be 3-20 characters long </br> AlphaNumeric or @ # $ %</html>");
        }
    }else{
        ui->regUserField->setStyleSheet(invalid);
        ui->regUserValid->setText("<html>User Name Required</html>");
    }
}

void UserControlPanel::on_regEmailField_editingFinished()
{
    if(ui->regEmailField->text().length() > 0){
        if(matchEmail(ui->regEmailField->text())){
            ui->regEmailField->setStyleSheet(valid);
            ui->regEmailValid->setText("");
        }else{
            ui->regEmailField->setStyleSheet(invalid);
            ui->regEmailValid->setText("<html>Invalid email (name@site.domain)</html>");
        }
        //TODO check DB for duplicate email
        if(DBConnect::checkEmail(ui->regEmailField->text()) > 0){
            ui->regEmailField->setStyleSheet(invalid);
            ui->regEmailValid->setText("Email allready registered");
        }
    }else{
        ui->regEmailField->setStyleSheet(invalid);
        ui->regEmailValid->setText("<html>Email Required</html>");
    }
}

void UserControlPanel::on_regPassField_editingFinished()
{
    if(ui->regPassField->text().length() > 0){
        if(matchPass(ui->regPassField->text())){
            ui->regPassField->setStyleSheet(valid);
            ui->regPassValid->setText("");
        }else{
            ui->regPassField->setStyleSheet(invalid);
            ui->regPassValid->setText("<html>Password must be 6-20 characters long </br> AlphaNumeric or @ # $ %</html>");
        }
    }else{
        ui->regPassField->setStyleSheet(invalid);
        ui->regPassValid->setText("<html>Password Required</html>");
    }
}

void UserControlPanel::on_regPassField2_editingFinished()
{
    if(ui->regPassField->text().length() > 0 && ui->regPassField2->text().length() > 0){
        if(matchPass(ui->regPassField->text())){
            if(ui->regPassField->text().compare(ui->regPassField2->text()) == 0){
                ui->regPassField->setStyleSheet(valid);
                ui->regPassField2->setStyleSheet(valid);
                ui->regPassValid2->setText("");
            }else{
                ui->regPassField2->setStyleSheet(invalid);
                ui->regPassValid2->setText("Passwords Must Match");
            }
        }else{
            if(ui->regPassField->text().compare(ui->regPassField2->text()) == 0){
                ui->regPassField2->setStyleSheet(valid);
                ui->regPassValid2->setText("");
            }else{
                ui->regPassField2->setStyleSheet(invalid);
                ui->regPassValid2->setText("Passwords Must Match");
            }
        }
    }
}

void UserControlPanel::on_regRegisterButton_clicked()
{
    submitRegistration();
}



void UserControlPanel::submitRegistration()
{
    int errors = 0;
    //validate first name
    if(ui->regFNameField->text().length() > 0){
        if(matchName(ui->regFNameField->text())){
            ui->regFNameField->setStyleSheet(valid);
            ui->regFNameValid->setText("");
        }else{
            errors++;
            ui->regFNameField->setStyleSheet(invalid);
            ui->regFNameValid->setText("<html>Valid Name must be 1-20 Alphabetic characters</html>");
        }
    }else{
        errors++;
        ui->regFNameField->setStyleSheet(invalid);
        ui->regFNameValid->setText("<html>First Name Required</html>");
    }

    //validate last name
    if(ui->regLNameField->text().length() > 0){
        if(matchName(ui->regLNameField->text())){
            ui->regLNameField->setStyleSheet(valid);
            ui->regLNameValid->setText("");
        }else{
            errors++;
            ui->regLNameField->setStyleSheet(invalid);
            ui->regLNameValid->setText("<html>Valid Name must be 1-20 Alphabetic characters</html>");
        }
    }else{
        errors++;
        ui->regLNameField->setStyleSheet(invalid);
        ui->regLNameValid->setText("<html>Last Name Required</html>");
    }

    //validate email
    if(ui->regEmailField->text().length() > 0){
        if(matchEmail(ui->regEmailField->text())){
            ui->regEmailField->setStyleSheet(valid);
            ui->regEmailValid->setText("");
        }else{
            errors++;
            ui->regEmailField->setStyleSheet(invalid);
            ui->regEmailValid->setText("<html>Invalid email (name@site.domain)</html>");
        }
        //TODO check DB for duplicate email
        if(DBConnect::checkEmail(ui->regEmailField->text()) > 0){
            errors++;
            ui->regEmailField->setStyleSheet(invalid);
            ui->regEmailValid->setText("Email allready registered");
        }
    }else{
        ui->regEmailField->setStyleSheet(invalid);
        ui->regEmailValid->setText("<html>Email Required</html>");
    }

    //validate username
    if(ui->regUserField->text().length() > 0){
        if(matchUser(ui->regUserField->text())){
            ui->regUserField->setStyleSheet(valid);
            ui->regUserValid->setText("");
        }else{
            errors++;
            ui->regUserField->setStyleSheet(invalid);
            ui->regUserValid->setText("<html>Handle must be 3-20 characters long </br> AlphaNumeric or @ # $ %</html>");
        }
    }else{
        errors++;
        ui->regUserField->setStyleSheet(invalid);
        ui->regUserValid->setText("<html>User Name Required</html>");
    }
    //validate password
    if(ui->regPassField->text().length() > 0){
        if(matchPass(ui->regPassField->text())){
            ui->regPassField->setStyleSheet(valid);
            ui->regPassValid->setText("");
        }else{
            errors++;
            ui->regPassField->setStyleSheet(invalid);
            ui->regPassValid->setText("<html>Password must be 6-20 characters long </br> AlphaNumeric or @ # $ %</html>");
        }
    }else{
        errors++;
        ui->regPassField->setStyleSheet(invalid);
        ui->regPassValid->setText("<html>Password Required</html>");
    }

    //validate confirm pass
    if(ui->regPassField->text().length() > 0 && ui->regPassField2->text().length() > 0){
        if(matchPass(ui->regPassField->text())){
            if(ui->regPassField->text().compare(ui->regPassField2->text()) == 0){
                ui->regPassField->setStyleSheet(valid);
                ui->regPassField2->setStyleSheet(valid);
                ui->regPassValid2->setText("");
            }else{
                errors++;
                ui->regPassField2->setStyleSheet(invalid);
                ui->regPassValid2->setText("Passwords Must Match");
            }
        }else{
            if(ui->regPassField->text().compare(ui->regPassField2->text()) == 0){
                ui->regPassField2->setStyleSheet(valid);
                ui->regPassValid2->setText("");
            }else{
                errors++;
                ui->regPassField2->setStyleSheet(invalid);
                ui->regPassValid2->setText("Passwords Must Match");
            }
        }
    }

    //continue registration if no errors
    if(errors == 0){
        int reg = DBConnect::doRegister(
                    ui->regFNameField->text(),
                    ui->regLNameField->text(),
                    ui->regUserField->text(),
                    ui->regEmailField->text(),
                    ui->regPassField->text()
                    );
        if(reg == 1){
            QMessageBox::information(this,
                    "Registration Success!",
                    "<html><h1>Thank You!</h1><p> You are now registered.</p></html>");
            clearFields(ui->registerTab);
            ui->tabWidget->setCurrentWidget(ui->homeTab);
        }
    }else{
        QMessageBox::warning(this,
                "Registration Error!!!",
                "<html><h1>Error</h1>"
                "<p>You could not be registered due to a system error.</br>"
                "We apologize for any inconvenience.</p></html>");
    }
}



void UserControlPanel::on_loginCancelButton_clicked()
{
    reject();
}

void UserControlPanel::on_loginLoginButton_clicked()
{
    //login
    int errors = 0;

    //email check
    if(ui->loginEmailField->text().length() > 0){
        ui->loginEmailValid->setText("");
    }else{
        errors++;
        ui->loginEmailValid->setText("Email Required");
    }

    if(ui->loginPassField->text().length() > 0){
        ui->loginPassValid->setText("");
    }else{
        errors++;
        ui->loginPassValid->setText("Password Required");
    }

    if(errors == 0){
        bool login = DBConnect::login(ui->loginEmailField->text(), ui->loginPassField->text());
        if(login){
            ui->tabWidget->setTabText(2, "LogOut");
            clearFields(ui->homeTab);
            ui->tabWidget->setCurrentIndex(1);
            checkTabs();
        }else{
            QMessageBox::warning(this,
                    "Login Error!",
                    "<html><h1>Error</h1>"
                    "<p>Email and/or password not found.</p></html>");
        }
    }
}
