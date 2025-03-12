#ifndef CREATEGROUPCHATDIALOG_H
#define CREATEGROUPCHATDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class CreateGroupChatDialog : public QDialog {
    Q_OBJECT
public:
    explicit CreateGroupChatDialog(QWidget* parent = nullptr);

    // 获取用户输入的群聊名称
    QString getGroupName() const;

private:
    QLineEdit *groupNameEdit;
    QPushButton *createButton;
};

#endif // CREATEGROUPCHATDIALOG_H
