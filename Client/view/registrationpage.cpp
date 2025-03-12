#include "registrationpage.h"
#include <QSpacerItem>

RegistrationPage::RegistrationPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupStyles();
}


void RegistrationPage::clearInputs() {
    nicknameEdit->clear();
    passwordEdit->clear();
    phoneEdit->clear();
}

void RegistrationPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 20, 40, 20);
    mainLayout->setSpacing(30);

    titleLabel = new QLabel("用户注册");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setSpacing(15);

    nicknameEdit = new QLineEdit;
    nicknameEdit->setPlaceholderText("请输入昵称");
    nicknameEdit->setObjectName("nicknameEdit");

    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setObjectName("passwordEdit");

    phoneEdit = new QLineEdit;
    phoneEdit->setPlaceholderText("请输入手机号");
    phoneEdit->setObjectName("phoneEdit");

    inputLayout->addWidget(nicknameEdit);
    inputLayout->addWidget(passwordEdit);
    inputLayout->addWidget(phoneEdit);

    registerButton = new QPushButton("立即注册");
    registerButton->setObjectName("registerButton");
    registerButton->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    backButton = new QPushButton("返回登录");
    backButton->setObjectName("linkButton");

    bottomLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
    bottomLayout->addWidget(backButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(registerButton);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);

    connect(registerButton, &QPushButton::clicked, this, [=](){
        emit registrationRequested(nicknameEdit->text(),
                                  passwordEdit->text(),
                                  phoneEdit->text());
    });
    connect(backButton, &QPushButton::clicked, this, &RegistrationPage::backToLoginPage);
}

void RegistrationPage::setupStyles()
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

    QPushButton#registerButton {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #00b894, stop:1 #55efc4);
        color: white;
        border: none;
        border-radius: 8px;
        padding: 14px;
        font-size: 16px;
        font-weight: bold;
    }

    QPushButton#registerButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #55efc4, stop:1 #00b894);
    }
    )");

    // 设置固定尺寸
    setMinimumSize(400, 500);
    nicknameEdit->setMinimumHeight(45);
    passwordEdit->setMinimumHeight(45);
    phoneEdit->setMinimumHeight(45);
    registerButton->setMinimumHeight(50);
}
