// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginpage.h"
#include "controller/clientcontroller.h"
#include "chatmainpage.h"
#include "changepasswordpage.h"
#include "forgotpasswordpage.h"
#include "registrationpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap base64ToPixmap(const QString& base64String);
private slots:
    // 直接通过页面对象指针跳转
    void switchToPage(QWidget *page);
    void handleLoginResult(bool success, const QString &message, const UserInfo user);
    void handleRegisterResult(bool success, const QString &message, const UserInfo &newUser);
    void handleCodeVerification(bool success, const QString &message, const QString &phoneNumber);
    void handlePasswordReset(bool success, const QString &message, const QString &newPassword);
    void handleEditProfileResult(bool success, const QString &message,const UserInfo &updatedUser);


private:
    void setupPages();
    void setupNetwork();
    void connectSignals();

    QStackedWidget *m_stack;
    LoginPage *m_loginPage;
    ChatMainPage *m_chatMainPage;
    ChangePasswordPage *m_changePasswordPage;
    ForgotPasswordPage *m_forgotPasswordPage;
    RegistrationPage *m_registrationPage;
    ClientController *m_controller;
};

#endif // MAINWINDOW_H
