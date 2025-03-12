#ifndef CHANGEPASSWORDPAGE_H
#define CHANGEPASSWORDPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ChangePasswordPage : public QWidget
{
    Q_OBJECT
public:
    explicit ChangePasswordPage(QWidget *parent = nullptr);

    void setVerifiedPhone(const QString &phoneNumber);

signals:
    void passwordChangeRequested(const QString& phone, const QString &newPassword, const QString &confirmPassword);
    void backToLoginPage();

private:
    void setupUI();
    void setupStyles();

    QLabel *titleLabel;
    QLabel *accountLabel;
    QLineEdit *newPasswordEdit;
    QLineEdit *confirmPasswordEdit;
    QPushButton *confirmButton;
    QPushButton *backButton;
    QString accout;
};

#endif // CHANGEPASSWORDPAGE_H
