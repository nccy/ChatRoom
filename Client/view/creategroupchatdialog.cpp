#include "creategroupchatdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

CreateGroupChatDialog::CreateGroupChatDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("创建群聊");
    setFixedSize(300, 100);

    // 使用水平布局：左侧为群聊名称编辑栏，右侧为创建按钮
    QHBoxLayout *layout = new QHBoxLayout(this);

    groupNameEdit = new QLineEdit;
    groupNameEdit->setPlaceholderText("请输入群聊名称");
    createButton = new QPushButton("创建");

    layout->addWidget(groupNameEdit, 1);
    layout->addWidget(createButton);

    // 点击创建按钮即结束对话框（可扩展为进一步创建群聊的逻辑）
    connect(createButton, &QPushButton::clicked, this, &CreateGroupChatDialog::accept);
}

QString CreateGroupChatDialog::getGroupName() const {
    return groupNameEdit->text();
}
