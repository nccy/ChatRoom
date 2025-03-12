#include "groupinfodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

GroupInfoDialog::GroupInfoDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("群聊信息");
    setFixedSize(400, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // --- 上部 ---
    QHBoxLayout *topLayout = new QHBoxLayout;

    // 左侧：群聊头像和重新上传按钮
    QVBoxLayout *avatarLayout = new QVBoxLayout;
    avatarLabel = new QLabel;
    avatarLabel->setFixedSize(80, 80);
    avatarLabel->setStyleSheet("border: 1px solid #ccc;");
    uploadAvatarButton = new QPushButton("重新上传群头像");
    uploadAvatarButton->setFixedWidth(120);
    connect(uploadAvatarButton, &QPushButton::clicked, this, &GroupInfoDialog::onUploadAvatar);
    avatarLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    avatarLayout->addWidget(uploadAvatarButton, 0, Qt::AlignCenter);

    // 右侧：群聊信息（名称、群聊号、群聊人数）
    QVBoxLayout *infoLayout = new QVBoxLayout;
    groupNameLabel = new QLabel("群聊名称");
    groupIDLabel = new QLabel("群聊号");
    memberCountLabel = new QLabel("群聊人数");
    infoLayout->addWidget(groupNameLabel);
    infoLayout->addWidget(groupIDLabel);
    infoLayout->addWidget(memberCountLabel);

    topLayout->addLayout(avatarLayout);
    topLayout->addLayout(infoLayout);
    mainLayout->addLayout(topLayout);

    // --- 下部：按钮 ---
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    exitGroupButton = new QPushButton("退出群聊");
    messageButton = new QPushButton("发消息");
    bottomLayout->addWidget(exitGroupButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(messageButton);
    mainLayout->addLayout(bottomLayout);
}

void GroupInfoDialog::setAvatar(const QPixmap &avatar)
{
    if (!avatar.isNull()){
        avatarLabel->setPixmap(avatar.scaled(avatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void GroupInfoDialog::setGroupName(const QString &groupName)
{
    groupNameLabel->setText("群聊名称: " + groupName);
}

void GroupInfoDialog::setGroupID(const QString &groupID)
{
    groupIDLabel->setText("群聊号: " + groupID);
}

void GroupInfoDialog::setMemberCount(const QString &memberCount)
{
    memberCountLabel->setText("群聊人数: " + memberCount);
}

void GroupInfoDialog::onUploadAvatar()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择群头像", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()){
        QPixmap newAvatar(fileName);
        if (!newAvatar.isNull()){
            setAvatar(newAvatar);
        }
    }
}
