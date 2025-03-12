#ifndef EDITPROFILEDIALOG_H
#define EDITPROFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QIcon>
#include <QPixmap>

class EditProfileDialog : public QDialog {
    Q_OBJECT
public:
    explicit EditProfileDialog(QWidget* parent = nullptr);

    // 获取编辑后的内容
    QString getNickname() const;
    QString getDeclaration() const;
    QString getPhone() const;
    QPixmap getAvatar() const;

    // 设置已有资料
    void setNickname(const QString &nickname);
    void setDeclaration(const QString &declaration);
    void setPhone(const QString &phone);
    void setAvatar(const QPixmap &avatar);
signals:
    void updateProfileRequest(const QString &nickname, const QString &declaration, const QString &phone, const QPixmap &avatar); // 发送更新请求信号
private slots:
    void onChangeAvatar();



private:
    QPushButton *avatarButton;
    QLineEdit* nicknameEdit;
    QLineEdit* declarationEdit;
    QLineEdit* phoneEdit;
    QPushButton *saveButton ;
    QPushButton *cancelButton ;
};

#endif // EDITPROFILEDIALOG_H
