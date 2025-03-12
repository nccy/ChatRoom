#include "loginpage.h"
#include <QSpacerItem>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupStyles();
}

void LoginPage::setAccount(const QString& account) {
    usernameEdit->setText(account);

    // 可选：自动聚焦密码输入框
    passwordEdit->clear();
    passwordEdit->setFocus();
}

void LoginPage::setupUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 20, 40, 20);
    mainLayout->setSpacing(30);

    // 标题
    titleLabel = new QLabel("欢迎使用聊天室");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // 输入区域
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setSpacing(15);

    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("请输入账号");
    usernameEdit->setObjectName("usernameEdit");

    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setObjectName("passwordEdit");

    inputLayout->addWidget(usernameEdit);
    inputLayout->addWidget(passwordEdit);

    // 登录按钮
    loginButton = new QPushButton("登 录");
    loginButton->setObjectName("loginButton");
    loginButton->setCursor(Qt::PointingHandCursor);

    // 底部链接
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    registerButton = new QPushButton("注册账号");
    forgotButton = new QPushButton("忘记密码");
    registerButton->setObjectName("linkButton");
    forgotButton->setObjectName("linkButton");

    bottomLayout->addWidget(registerButton);
    bottomLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    bottomLayout->addWidget(forgotButton);

    // 组装主布局
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);

    // 信号连接
    connect(loginButton, &QPushButton::clicked, this, [=](){
        emit loginRequested(usernameEdit->text(), passwordEdit->text());
    });
    connect(registerButton, &QPushButton::clicked, this, &LoginPage::showRegistrationPage);
    connect(forgotButton, &QPushButton::clicked, this, &LoginPage::showForgotPasswordPage);
}

void LoginPage::setupStyles()
{
    setStyleSheet(R"(
    QWidget {
        background-color: #f5f6fa;
    }

    QLabel#titleLabel {
        color: #2d3436;
        font-size: 28px;
        font-weight: bold;
        margin-bottom: 30px;
    }

    QLineEdit {
        background-color: white;
        border: 2px solid #dcdde1;
        border-radius: 8px;
        padding: 12px;
        font-size: 14px;
    }

    QLineEdit:focus {
        border-color: #0984e3;
    }

    QPushButton#loginButton {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #0984e3, stop:1 #74b9ff);
        color: white;
        border: none;
        border-radius: 8px;
        padding: 14px;
        font-size: 16px;
        font-weight: bold;
    }

    QPushButton#loginButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #74b9ff, stop:1 #0984e3);
    }

    QPushButton#linkButton {
        color: #636e72;
        background: transparent;
        border: none;
        font-size: 13px;
        text-decoration: underline;
    }

    QPushButton#linkButton:hover {
        color: #2d3436;
    }
    )");

    // 设置固定尺寸
    setMinimumSize(400, 500);
    usernameEdit->setMinimumHeight(45);
    passwordEdit->setMinimumHeight(45);
    loginButton->setMinimumHeight(50);
}
