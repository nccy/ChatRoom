#ifndef FORGOTPASSWORDPAGE_H
#define FORGOTPASSWORDPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ForgotPasswordPage : public QWidget
{
    Q_OBJECT
public:
    explicit ForgotPasswordPage(QWidget *parent = nullptr);

    void setupUI();
    void setupStyles();
    void updateCaptcha(); // 更新验证码图片和文本
    QString generateCaptchaText(); // 生成随机验证码文本
    QPixmap generateCaptchaImage(const QString &captchaText); // 生成验证码图片

signals:
    void retrievePasswordRequested(const QString& phone, const QString& captcha, const QString& curCaptcha);
    void refreshCaptchaRequested();
    void backToLoginPage();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:

    QLineEdit *phoneEdit;
    QLineEdit *captchaEdit;
    QPushButton *retrieveButton;
    QPushButton *backButton;
    QLabel *titleLabel;
    QLabel *captchaImage;
    QString currentCaptcha; // 当前验证码文本
};

#endif // FORGOTPASSWORDPAGE_H
