#ifndef GROUPINFODIALOG_H
#define GROUPINFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class GroupInfoDialog : public QDialog {
    Q_OBJECT
public:
    explicit GroupInfoDialog(QWidget *parent = nullptr);

    // 设置初始群聊信息
    void setAvatar(const QPixmap &avatar);
    void setGroupName(const QString &groupName);
    void setGroupID(const QString &groupID);
    void setMemberCount(const QString &memberCount);

private slots:
    void onUploadAvatar();

private:
    // 上部：左侧头像及上传按钮，右侧群聊信息
    QLabel *avatarLabel;
    QPushButton *uploadAvatarButton;
    QLabel *groupNameLabel;
    QLabel *groupIDLabel;
    QLabel *memberCountLabel;

    // 下部：操作按钮
    QPushButton *exitGroupButton;
    QPushButton *messageButton;
};

#endif // GROUPINFODIALOG_H
