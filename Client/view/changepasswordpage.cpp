#include "changepasswordpage.h"
#include <QSpacerItem>

ChangePasswordPage::ChangePasswordPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupStyles();
}

void ChangePasswordPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 20, 40, 20);
    mainLayout->setSpacing(30);

    titleLabel = new QLabel("重置密码");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    accountLabel = new QLabel("已验证手机号：");
    accountLabel->setObjectName("accountLabel");
    accountLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(accountLabel);

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setSpacing(15);

    newPasswordEdit = new QLineEdit;
    newPasswordEdit->setPlaceholderText("输入新密码");
    newPasswordEdit->setEchoMode(QLineEdit::Password);
    newPasswordEdit->setObjectName("newPasswordEdit");

    confirmPasswordEdit = new QLineEdit;
    confirmPasswordEdit->setPlaceholderText("再次输入新密码");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setObjectName("confirmPasswordEdit");

    inputLayout->addWidget(newPasswordEdit);
    inputLayout->addWidget(confirmPasswordEdit);

    confirmButton = new QPushButton("确定重置密码");
    confirmButton->setObjectName("confirmButton");
    confirmButton->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    backButton = new QPushButton("返回登录");
    backButton->setObjectName("linkButton");

    bottomLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
    bottomLayout->addWidget(backButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(confirmButton);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);

    connect(confirmButton, &QPushButton::clicked, this, [=](){
        emit passwordChangeRequested(accout,newPasswordEdit->text(), confirmPasswordEdit->text());
    });
    connect(backButton, &QPushButton::clicked, this, &ChangePasswordPage::backToLoginPage);
}

void ChangePasswordPage::setupStyles()
{
    setStyleSheet(R"(
    QWidget {
        background-color: #f5f6fa;
    }

    QLabel#titleLabel {
        color: #2d3436;
        font-size: 28px;
        font-weight: bold;
        margin-bottom: 20px;
    }

    QLabel#accountLabel {
        color: #636e72;
        font-size: 16px;
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

    QPushButton#confirmButton {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #6c5ce7, stop:1 #a8a4e6);
        color: white;
        border: none;
        border-radius: 8px;
        padding: 14px;
        font-size: 16px;
        font-weight: bold;
    }

    QPushButton#confirmButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #a8a4e6, stop:1 #6c5ce7);
    }
    )");

    // 设置固定尺寸
    setMinimumSize(400, 500);
    newPasswordEdit->setMinimumHeight(45);
    confirmPasswordEdit->setMinimumHeight(45);
    confirmButton->setMinimumHeight(50);
}

void ChangePasswordPage::setVerifiedPhone(const QString &phoneNumber)
{
    accout=phoneNumber;
    accountLabel->setText("已验证手机号: " + phoneNumber);
}
