#include "friendinfodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

FriendInfoDialog::FriendInfoDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("好友信息");
    setFixedSize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // --- 上部 ---
    QHBoxLayout *topLayout = new QHBoxLayout;
    // 左侧：头像
    avatarLabel = new QLabel;
    avatarLabel->setFixedSize(80, 80);
    avatarLabel->setStyleSheet("border: 1px solid #ccc;");
    // 右侧：好友信息（昵称、账号、宣言）
    QVBoxLayout *infoLayout = new QVBoxLayout;
    nicknameLabel = new QLabel("昵称");
    accountLabel = new QLabel("账号");
    declarationLabel = new QLabel("宣言");
    infoLayout->addWidget(nicknameLabel);
    infoLayout->addWidget(accountLabel);
    infoLayout->addWidget(declarationLabel);

    topLayout->addWidget(avatarLabel);
    topLayout->addLayout(infoLayout);
    mainLayout->addLayout(topLayout);

    // --- 中部：备注栏 ---
    QHBoxLayout *middleLayout = new QHBoxLayout;
    QLabel *remarkLabel = new QLabel("备注:");
    remarkEdit = new QLineEdit;
    middleLayout->addWidget(remarkLabel);
    middleLayout->addWidget(remarkEdit);
    mainLayout->addLayout(middleLayout);

    // --- 下部：按钮 ---
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    deleteButton = new QPushButton("删除好友");
    messageButton = new QPushButton("发消息");
    bottomLayout->addWidget(deleteButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(messageButton);
    mainLayout->addLayout(bottomLayout);
}

void FriendInfoDialog::setAvatar(const QPixmap &avatar)
{
    if (!avatar.isNull()){
        avatarLabel->setPixmap(avatar.scaled(avatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void FriendInfoDialog::setNickname(const QString &nickname)
{
    nicknameLabel->setText("昵称: " + nickname);
}

void FriendInfoDialog::setAccount(const QString &account)
{
    accountLabel->setText("账号: " + account);
}

void FriendInfoDialog::setDeclaration(const QString &declaration)
{
    declarationLabel->setText("宣言: " + declaration);
}

void FriendInfoDialog::setRemark(const QString &remark)
{
    remarkEdit->setText(remark);
}

QString FriendInfoDialog::getRemark() const
{
    return remarkEdit->text();
}
