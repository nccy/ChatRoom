#include "forgotpasswordpage.h"
#include <QSpacerItem>
#include <QEvent>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QPainter>

ForgotPasswordPage::ForgotPasswordPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupStyles();
    updateCaptcha();  // 新增初始化验证码
}

void ForgotPasswordPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 20, 40, 20);
    mainLayout->setSpacing(30);

    titleLabel = new QLabel("找回密码");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setSpacing(15);

    phoneEdit = new QLineEdit;
    phoneEdit->setPlaceholderText("请输入注册手机号");
    phoneEdit->setObjectName("phoneEdit");

    QWidget *captchaContainer = new QWidget;
    QHBoxLayout *captchaLayout = new QHBoxLayout(captchaContainer);
    captchaLayout->setContentsMargins(0, 0, 0, 0);
    captchaLayout->setSpacing(10);

    captchaEdit = new QLineEdit;
    captchaEdit->setPlaceholderText("请输入验证码");
    captchaEdit->setObjectName("captchaEdit");

    captchaImage = new QLabel;
    captchaImage->setAlignment(Qt::AlignCenter);
    captchaImage->setObjectName("captchaImage");
    captchaImage->setCursor(Qt::PointingHandCursor);
    captchaImage->installEventFilter(this);

    captchaLayout->addWidget(captchaEdit);
    captchaLayout->addWidget(captchaImage);

    inputLayout->addWidget(phoneEdit);
    inputLayout->addWidget(captchaContainer);

    retrieveButton = new QPushButton("一键找回");
    retrieveButton->setObjectName("retrieveButton");
    retrieveButton->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    backButton = new QPushButton("返回登录");
    backButton->setObjectName("linkButton");

    bottomLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
    bottomLayout->addWidget(backButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(retrieveButton);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);

    connect(retrieveButton, &QPushButton::clicked, this, [=](){
        emit retrievePasswordRequested(phoneEdit->text(), captchaEdit->text(),currentCaptcha);
    });
    connect(backButton, &QPushButton::clicked, this, &ForgotPasswordPage::backToLoginPage);
}

bool ForgotPasswordPage::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == captchaImage && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            updateCaptcha();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

QString ForgotPasswordPage::generateCaptchaText()
{
    const QString chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    QString captcha;
    for (int i = 0; i < 4; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.length());
        captcha.append(chars[index]);
    }
    return captcha;
}

QPixmap ForgotPasswordPage::generateCaptchaImage(const QString &captchaText)
{
    QPixmap pixmap(120, 40);
    pixmap.fill(Qt::white); // 白色背景

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制干扰线
    for (int i = 0; i < 5; ++i) {
        painter.setPen(QColor(QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256)));
        painter.drawLine(
            QRandomGenerator::global()->bounded(pixmap.width()),
            QRandomGenerator::global()->bounded(pixmap.height()),
            QRandomGenerator::global()->bounded(pixmap.width()),
            QRandomGenerator::global()->bounded(pixmap.height())
        );
    }

    // 绘制验证码文本（带随机旋转和颜色）
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    painter.setFont(font);

    for (int i = 0; i < captchaText.length(); ++i) {
        painter.save();
        // 随机颜色
        painter.setPen(QColor(QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256)));
        // 随机旋转角度（-30到30度）
        qreal angle = QRandomGenerator::global()->bounded(-30, 30);
        QPoint position(20 + i * 25, 25); // 字符位置
        painter.translate(position);
        painter.rotate(angle);
        painter.drawText(-10, -10, 20, 20, Qt::AlignCenter, QString(captchaText[i]));
        painter.restore();
    }

    // 添加噪点
    for (int i = 0; i < 50; ++i) {
        painter.setPen(QColor(QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256),
                              QRandomGenerator::global()->bounded(256)));
        painter.drawPoint(
            QRandomGenerator::global()->bounded(pixmap.width()),
            QRandomGenerator::global()->bounded(pixmap.height())
        );
    }

    return pixmap;
}

void ForgotPasswordPage::updateCaptcha()
{
    currentCaptcha = generateCaptchaText(); // 生成新文本
    QPixmap pixmap = generateCaptchaImage(currentCaptcha);
    captchaImage->setPixmap(pixmap); // 显示新图片
}


void ForgotPasswordPage::setupStyles()
{
    setStyleSheet(R"(
    QWidget {
        background-color: #f5f6fa;
    }

    QLabel#titleLabel {
        color: #2d3436;
        font-size: 28px;
        font-weight: bold;
        margin-bottom: 30px;
    }

    QLineEdit {
        background-color: white;
        border: 2px solid #dcdde1;
        border-radius: 8px;
        padding: 12px;
        font-size: 14px;
    }

    QLineEdit:focus {
        border-color: #0984e3;
    }

    QPushButton#retrieveButton {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #e17055, stop:1 #ff7675);
        color: white;
        border: none;
        border-radius: 8px;
        padding: 14px;
        font-size: 16px;
        font-weight: bold;
    }

    QPushButton#retrieveButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #ff7675, stop:1 #e17055);
    }

    #captchaImage {
        background-color: #ffffff;
        border: 2px solid #dcdde1;
        border-radius: 8px;
        min-width: 100px;
        min-height: 45px;
    }

    #captchaImage:hover {
        border-color: #0984e3;
    }
    )");

    // 设置固定尺寸
    setMinimumSize(400, 500);
    phoneEdit->setMinimumHeight(45);
    captchaEdit->setMinimumHeight(45);
    retrieveButton->setMinimumHeight(50);
}


