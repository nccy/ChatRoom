// LoginPage.h
#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class LoginPage : public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    void setAccount(const QString& account);

signals:
    void loginRequested(const QString& username, const QString& password);
    void showRegistrationPage();
    void showForgotPasswordPage();

private:
    void setupUI();
    void setupStyles();

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *forgotButton;
    QLabel *titleLabel;
};

#endif // LOGINPAGE_H
