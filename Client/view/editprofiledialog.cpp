#include "editprofiledialog.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>

// 构造函数
EditProfileDialog::EditProfileDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("编辑资料");
    setFixedSize(300, 400);

    // 移除上下文帮助按钮标志
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 头像部分：按钮显示头像，点击可更换
    avatarButton = new QPushButton;
    avatarButton->setFixedSize(80, 80);
    QPixmap defaultAvatar(":/avatar.png");
    avatarButton->setIcon(QIcon(defaultAvatar));
    avatarButton->setIconSize(avatarButton->size());
    avatarButton->setFlat(true);
    connect(avatarButton, &QPushButton::clicked, this, &EditProfileDialog::onChangeAvatar);
    mainLayout->addWidget(avatarButton, 0, Qt::AlignCenter);

    // 表单部分：昵称、宣言、手机号码
    QFormLayout *formLayout = new QFormLayout;
    nicknameEdit = new QLineEdit;
    declarationEdit = new QLineEdit;
    phoneEdit = new QLineEdit;
    formLayout->addRow("昵称:", nicknameEdit);
    formLayout->addRow("宣言:", declarationEdit);
    formLayout->addRow("手机号码:", phoneEdit);
    mainLayout->addLayout(formLayout);

    // 按钮部分：右下角“保存”与“取消”
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    saveButton = new QPushButton("保存");
    cancelButton = new QPushButton("取消");
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, [this]() {
        emit updateProfileRequest(getNickname(), getDeclaration(), getPhone(), getAvatar());
    });
    connect(cancelButton, &QPushButton::clicked, this, &EditProfileDialog::reject);
}

// 获取编辑后的昵称
QString EditProfileDialog::getNickname() const {
    return nicknameEdit->text();
}

// 获取编辑后的宣言
QString EditProfileDialog::getDeclaration() const {
    return declarationEdit->text();
}

// 获取编辑后的手机号码
QString EditProfileDialog::getPhone() const {
    return phoneEdit->text();
}

// 获取编辑后的头像
QPixmap EditProfileDialog::getAvatar() const {
    return avatarButton->icon().pixmap(avatarButton->size());
}

// 设置已有的昵称
void EditProfileDialog::setNickname(const QString &nickname) {
    nicknameEdit->setText(nickname);
}

// 设置已有的宣言
void EditProfileDialog::setDeclaration(const QString &declaration) {
    declarationEdit->setText(declaration);
}

// 设置已有的手机号码
void EditProfileDialog::setPhone(const QString &phone) {
    phoneEdit->setText(phone);
}

// 设置已有的头像
void EditProfileDialog::setAvatar(const QPixmap &avatar) {
    if (!avatar.isNull()){
        avatarButton->setIcon(QIcon(avatar));
        avatarButton->setIconSize(avatarButton->size());
    }
}

// 响应点击头像按钮，选择新的头像
void EditProfileDialog::onChangeAvatar() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()){
        QPixmap newAvatar(fileName);
        if (!newAvatar.isNull()){
            setAvatar(newAvatar);
        }
    }
}
