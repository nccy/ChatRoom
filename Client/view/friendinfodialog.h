#ifndef FRIENDINFODIALOG_H
#define FRIENDINFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>

class FriendInfoDialog : public QDialog {
    Q_OBJECT
public:
    explicit FriendInfoDialog(QWidget *parent = nullptr);

    // 设置初始好友信息
    void setAvatar(const QPixmap &avatar);
    void setNickname(const QString &nickname);
    void setAccount(const QString &account);
    void setDeclaration(const QString &declaration);
    void setRemark(const QString &remark);

    // 获取编辑后的备注（其他信息一般不允许修改）
    QString getRemark() const;

private:
    // 上部
    QLabel *avatarLabel;
    QLabel *nicknameLabel;
    QLabel *accountLabel;
    QLabel *declarationLabel;
    // 中部：备注栏
    QLineEdit *remarkEdit;
    // 下部：操作按钮
    QPushButton *deleteButton;
    QPushButton *messageButton;
};

#endif // FRIENDINFODIALOG_H
