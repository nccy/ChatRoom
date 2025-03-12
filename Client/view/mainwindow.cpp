// mainwindow.cpp
#include "mainwindow.h"
#include <QMessageBox>
#include "network/tcpclient.h"
#include <QDebug>
#include <QGuiApplication>
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_stack(new QStackedWidget(this)),
      m_loginPage(new LoginPage(this)),
      m_chatMainPage(new ChatMainPage(this)),
      m_changePasswordPage(new ChangePasswordPage(this)),
      m_forgotPasswordPage(new ForgotPasswordPage(this)),
      m_registrationPage(new RegistrationPage(this)),
      m_controller(ClientController::instance())
{
    // 注册 User 类型到 Qt 元对象系统
    qRegisterMetaType<UserInfo>("UserInfo");
    setupPages();
    setupNetwork();
    connectSignals();
}

void MainWindow::setupPages() {
    m_stack->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_stack->addWidget(m_loginPage);
    m_stack->addWidget(m_chatMainPage);
    m_stack->addWidget(m_changePasswordPage);
    m_stack->addWidget(m_forgotPasswordPage);
    m_stack->addWidget(m_registrationPage);
    setCentralWidget(m_stack);
}

void MainWindow::setupNetwork() {
    TcpClient::instance()->connectToServer("127.0.0.1", 12345);
}

void MainWindow::connectSignals() {


    // 页面跳转信号（直接传递页面指针）
    connect(m_loginPage, &LoginPage::showRegistrationPage,
           this, [this]{ switchToPage(m_registrationPage); });
    connect(m_loginPage, &LoginPage::showForgotPasswordPage,
           this, [this]{ switchToPage(m_forgotPasswordPage); });
    connect(m_changePasswordPage, &ChangePasswordPage::backToLoginPage,
           this, [this]{ switchToPage(m_loginPage); });
    connect(m_forgotPasswordPage, &ForgotPasswordPage::backToLoginPage,
           this, [this]{ switchToPage(m_loginPage); });
    connect(m_registrationPage, &RegistrationPage::backToLoginPage,
           this, [this]{ switchToPage(m_loginPage); });
    connect(m_chatMainPage,&ChatMainPage::backToLoginPage,
            this,[this]{switchToPage(m_loginPage);});


    // 业务逻辑信号
//    connect(m_controller, &ClientController::loginResult,
//           this, &MainWindow::handleLoginResult);

    //页面请求
    connect(m_loginPage, &LoginPage::loginRequested,
           m_controller, &ClientController::handleLogin);
    connect(m_registrationPage, &RegistrationPage::registrationRequested,
           m_controller, &ClientController::handleRegistration);
    connect(m_forgotPasswordPage,&ForgotPasswordPage::retrievePasswordRequested,
           m_controller,&ClientController::handleForgotPassword);
    connect(m_changePasswordPage,&ChangePasswordPage::passwordChangeRequested,
           m_controller,&ClientController::handleResetPassword);
    connect(m_chatMainPage,&ChatMainPage::editProfileRequested,
            m_controller,&ClientController::editProfileRequested);



    // 页面响应
    connect(m_controller, &ClientController::loginResult,
               this, &MainWindow::handleLoginResult);

    connect(m_controller, &ClientController::registerResult,
               this, &MainWindow::handleRegisterResult);

    connect(m_controller, &ClientController::codeVerificationResult,
               this, &MainWindow::handleCodeVerification);

    connect(m_controller, &ClientController::passwordResetResult,
               this, &MainWindow::handlePasswordReset);
    connect(m_controller, &ClientController::editProfileResult,
            this,&MainWindow::handleEditProfileResult);

}

void MainWindow::switchToPage(QWidget *page) {
    if (page && page->parent() == m_stack) {
        m_stack->setCurrentWidget(page);
    }
    if (page == m_chatMainPage) {
        // 手动设置窗口大小为 ChatMainPage 的初始大小
        this->resize(1200, 800);
        // 调用居中函数
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            QRect screenGeometry = screen->availableGeometry();
            int x = (screenGeometry.width() - this->width()) / 2;
            int y = (screenGeometry.height() - this->height()) / 2;
            this->move(x, y);
        }
    }
}

void MainWindow::handleLoginResult(bool success, const QString &message, const UserInfo user)
{
    if (success) {
        QMessageBox::information(this, "登录成功", "欢迎回来，" + user.getNickname());
        QPixmap pixmap = base64ToPixmap(user.getAvatarBase64());
        m_chatMainPage->setProfile(user.getNickname(),user.getAccount(),user.getDeclaration(),"在线",pixmap);
        switchToPage(m_chatMainPage);
    } else {
        QMessageBox::warning(this, "登录失败", message);
        //m_loginPage->clearPassword(); // 清空密码输入框
    }
}

void MainWindow::handleRegisterResult(bool success, const QString &message, const UserInfo &newUser)
{
    if (success) {
        QMessageBox::information(this, "注册成功", "账号注册成功，请登录");
        // 自动填充手机号到登录页
        m_loginPage->setAccount(newUser.getPhone());
        // 清空注册页敏感信息
        m_registrationPage->clearInputs();
        switchToPage(m_loginPage);
    } else {
        QMessageBox::warning(this, "注册失败", message);
    }
}

void MainWindow::handleCodeVerification(bool success, const QString &message, const QString &phoneNumber)
{
    if (success) {
        QMessageBox::information(this, "验证通过", "验证码正确，请设置新密码");
        qDebug() <<phoneNumber;
        m_changePasswordPage->setVerifiedPhone(phoneNumber); // 传递已验证手机号
        switchToPage(m_changePasswordPage);
    } else {
        QMessageBox::warning(this, "验证失败", message);
        m_forgotPasswordPage->updateCaptcha(); // 刷新验证码
    }
}

void MainWindow::handlePasswordReset(bool success, const QString &message, const QString &newPassword)
{
    if (success) {
        QMessageBox::information(this, "重置成功",
            QString("密码已重置，新密码：%1\n请妥善保管").arg(newPassword));
        switchToPage(m_loginPage);
        //m_loginPage->setAccount(m_changePasswordPage-); // 自动填充账号
    } else {
        QMessageBox::warning(this, "重置失败", message);
    }
}

MainWindow::~MainWindow() {
    TcpClient::instance()->disconnectFromHost();
}

QPixmap MainWindow::base64ToPixmap(const QString& base64String) {
    // 将 Base64 字符串解码为字节数组
    QByteArray byteArray = QByteArray::fromBase64(base64String.toUtf8());

    // 创建 QPixmap 对象
    QPixmap pixmap;
    if (!pixmap.loadFromData(byteArray)) {
        qDebug() << "Failed to load pixmap from data.";
    }
    return pixmap;
}
void MainWindow::handleEditProfileResult(bool success,
                                       const QString &message,
                                       const UserInfo &updatedUser)
{
    if (success) {
        QPixmap pixmap = base64ToPixmap(updatedUser.getAvatarBase64());
        m_chatMainPage->setEditProfile(updatedUser.getNickname(),updatedUser.getDeclaration(),updatedUser.getPhone(),pixmap);
        qDebug() <<message;
    } else {
        qDebug() <<message;
    }
}
