#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class RegistrationPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegistrationPage(QWidget *parent = nullptr);
    void clearInputs();

signals:
    void registrationRequested(const QString& nickname,
                              const QString& password,
                              const QString& phone);
    void backToLoginPage();

private:
    void setupUI();
    void setupStyles();

    QLineEdit *nicknameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *phoneEdit;
    QPushButton *registerButton;
    QPushButton *backButton;
    QLabel *titleLabel;
};

#endif // REGISTRATIONPAGE_H
