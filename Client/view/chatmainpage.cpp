#include "chatmainpage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTime>
#include <QEvent>
#include <QListWidgetItem>
#include <QTextBrowser> // 新增头文件
#include <QGuiApplication>
#include <QScreen>


/**
 * @brief ChatMainPage::ChatMainPage 构造函数
 * @param parent
 *
 * 在构造函数中依次调用:
 * 1. initUI()        // 初始化整体布局（分割器、左右区域）
 * 2. applyStyles()    // 设置统一样式
 * 3. setupConnections() // 建立信号槽
 * 4. initSettingsMenu() // 初始化菜单
 */
ChatMainPage::ChatMainPage(QWidget *parent)
    : QMainWindow(parent)
    , mainSplitter(nullptr)
    , leftWidget(nullptr)
    , profileWidget(nullptr)
    , avatarContainer(nullptr)
    , avatarLabel(nullptr)
    , statusIndicator(nullptr)
    , onlineTextLabel(nullptr)
    , nameLabel(nullptr)
    , idLabel(nullptr)
    , signLabel(nullptr)
    , settingsBtn(nullptr)
    , btnAdd(nullptr)
    , btnGroup(nullptr)
    , searchInput(nullptr)
    , btnMessage(nullptr)
    , btnContacts(nullptr)
    , btnGroups(nullptr)
    , navButtonGroup(nullptr)
    , rightWidget(nullptr)
    , rightStackedWidget(nullptr)
    , emptyPage(nullptr)
    , emptyPageLabel(nullptr)
    , friendChatPage(nullptr)
    , friendChatHeader(nullptr)
    , friendNameLabel(nullptr)
    , editFriendBtn(nullptr)
    , friendChatHistory(nullptr)
    , friendChatInputArea(nullptr)
    , friendEmojiBtn(nullptr)
    , friendFileBtn(nullptr)
    , friendImageBtn(nullptr)
    , friendShakeBtn(nullptr)
    , friendMessageInput(nullptr)
    , friendSendBtn(nullptr)
    , groupChatPage(nullptr)
    , groupChatSplitter(nullptr)
    , groupChatLeftArea(nullptr)
    , groupChatHeader(nullptr)
    , groupNameLabel(nullptr)
    , editGroupBtn(nullptr)
    , groupChatHistory(nullptr)
    , groupChatInputArea(nullptr)
    , groupEmojiBtn(nullptr)
    , groupFileBtn(nullptr)
    , groupImageBtn(nullptr)
    , groupMessageInput(nullptr)
    , groupSendBtn(nullptr)
    , groupMemberArea(nullptr)
    , memberCountLabel(nullptr)
    , groupMemberList(nullptr)
    , toggleMemberListBtn(nullptr)
    , isMemberListVisible(true)
    , friendRequestPage(nullptr)
    , friendRequestList(nullptr)
    , groupRequestPage(nullptr)
    , groupRequestList(nullptr) // 确保所有新控件在初始化列表置空
    , settingsMenu(nullptr)
    , editProfileDlg(nullptr)

{
    initUI();
    applyStyles();
    initSettingsMenu();
    setupConnections();

    // 窗口基础设置
    resize(1200, 800);
    setWindowTitle("网络聊天室");
    setStyleSheet("font-family: 'Microsoft YaHei';"); // 确保中文字体显示
    // 居中窗口：获取主屏幕的可用区域，计算窗口左上角坐标，然后移动窗口
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
}

void ChatMainPage::setProfile(const QString name,const QString id,const QString sign,const QString status,const QPixmap &src)
{
    nameLabel->setText(name);
    idLabel->setText("ID: "+id);
    signLabel->setText("宣言："+sign);
    onlineTextLabel->setText(status);
    avatarLabel->setPixmap(circularAvatar(src,60));
}


/**
 * @brief ChatMainWindow::initUI
 * 初始化主界面结构，包括分割器和左右区域
 */
void ChatMainPage::initUI()
{
    // 创建主分割器
    mainSplitter = new QSplitter(Qt::Horizontal, this);

    // 创建左侧边栏并添加到分割器
    createLeftSidebar();
    mainSplitter->addWidget(leftWidget);

    // 创建右侧聊天区并添加到分割器
    createRightChatArea();
    mainSplitter->addWidget(rightWidget);

    // 左侧占 30%，右侧占 70%
    mainSplitter->setStretchFactor(0, 3);
    mainSplitter->setStretchFactor(1, 7);

    // 设置分割器为主窗口中心组件
    setCentralWidget(mainSplitter);
}

/**
 * @brief ChatMainWindow::createLeftSidebar
 * 创建左侧边栏布局，包括头像、设置按钮、搜索框、联系人列表等
 */
void ChatMainPage::createLeftSidebar()
{
    // 左侧主容器
    leftWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(leftWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 个人信息区域
    profileWidget = new QWidget;
    QVBoxLayout *profileMainLayout = new QVBoxLayout(profileWidget);
    profileMainLayout->setContentsMargins(8, 8, 8, 8);  // 减小边距
    profileMainLayout->setSpacing(5);                   // 减小间距

    // ========== 顶部行：三列布局（左-头像相关 | 中-昵称/ID | 右-按钮）==========
    QHBoxLayout *topProfileLayout = new QHBoxLayout;
    topProfileLayout->setContentsMargins(0, 0, 0, 0);
    topProfileLayout->setSpacing(8);  // 减小水平间距

    // >>>>>>> 左侧：头像容器（头像+状态指示器+在线文本）<<<<<<<
    QWidget *avatarSection = new QWidget;
    QVBoxLayout *avatarSectionLayout = new QVBoxLayout(avatarSection);
    avatarSectionLayout->setContentsMargins(0, 0, 0, 0);
    avatarSectionLayout->setSpacing(2);  // 减小头像与在线文本的间距

    // 头像容器
    avatarContainer = new QWidget;
    avatarContainer->setFixedSize(68, 68);

    // 圆形头像
    avatarLabel = new QLabel(avatarContainer);
    avatarLabel->setGeometry(4, 4, 60, 60);

    // 状态指示器（右下角覆盖显示）
    statusIndicator = new QLabel(avatarContainer);
    statusIndicator->setFixedSize(12, 12);
    statusIndicator->move(avatarContainer->width() - statusIndicator->width() - 3,
                          avatarContainer->height() - statusIndicator->height() - 3);

    // 在线文本（头像正下方）
    onlineTextLabel = new QLabel("在线");
    onlineTextLabel->setAlignment(Qt::AlignCenter);
    onlineTextLabel->setStyleSheet("font-size: 10px;");  // 缩小字体大小

    // 组装左侧区域
    avatarSectionLayout->addWidget(avatarContainer, 0, Qt::AlignCenter);
    avatarSectionLayout->addWidget(onlineTextLabel);
    topProfileLayout->addWidget(avatarSection);

    // >>>>>>> 中间：昵称和ID（垂直居中）<<<<<<<
    QWidget *nameSection = new QWidget;
    QVBoxLayout *nameSectionLayout = new QVBoxLayout(nameSection);
    nameSectionLayout->setContentsMargins(0, 0, 0, 0);
    nameSectionLayout->setSpacing(1);  // 减小昵称和ID的间距

    nameLabel = new QLabel("清风徐来");
    nameLabel->setStyleSheet("font-size: 14px;");  // 设置昵称字体大小
    idLabel   = new QLabel("ID: user_2024");
    idLabel->setStyleSheet("font-size: 12px; color: #666;");  // 设置ID字体大小和颜色

    nameSectionLayout->addWidget(nameLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    nameSectionLayout->addWidget(idLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    topProfileLayout->addWidget(nameSection);

    // >>>>>>> 右侧：按钮组（垂直排列）<<<<<<<
    QWidget *btnSection = new QWidget;
    QVBoxLayout *btnSectionLayout = new QVBoxLayout(btnSection);
    btnSectionLayout->setContentsMargins(0, 0, 0, 0);
    btnSectionLayout->setSpacing(5);  // 减小按钮之间的间距

    settingsBtn = new QPushButton("设置");
    btnAdd      = new QPushButton("加好友/群");
    btnGroup    = new QPushButton("创建群聊");

    // 设置按钮样式
    QString btnStyle = "QPushButton { border: 1px solid #ccc; border-radius: 4px; padding: 4px 8px; font-size: 12px; }"
                       "QPushButton:hover { background-color: #f0f0f0; }";
    settingsBtn->setStyleSheet(btnStyle);
    btnAdd->setStyleSheet(btnStyle);
    btnGroup->setStyleSheet(btnStyle);

    btnSectionLayout->addWidget(settingsBtn);
    btnSectionLayout->addWidget(btnAdd);
    btnSectionLayout->addWidget(btnGroup);
    topProfileLayout->addWidget(btnSection);

    // 设置三列的比例（左:中:右 = 2:3:2）
    topProfileLayout->setStretch(0, 2);
    topProfileLayout->setStretch(1, 3);
    topProfileLayout->setStretch(2, 2);

    // 将顶部布局加入profileMainLayout
    profileMainLayout->addLayout(topProfileLayout);

    // ========== 个性签名 ==========
    signLabel = new QLabel(QString("宣言：") + "代码构建世界，交流连接你我");
    signLabel->setWordWrap(true);
    signLabel->setStyleSheet("font-size: 12px; color: #666; margin-top: 4px;");  // 设置个性签名字体大小、颜色和上边距
    profileMainLayout->addWidget(signLabel);

    // ========== 搜索框 ==========
    searchInput = new QLineEdit;
    searchInput->setPlaceholderText("搜索联系人、群组或聊天记录");
    searchInput->setStyleSheet("border: 1px solid #ccc; border-radius: 4px; padding: 4px; font-size: 12px;");
    profileMainLayout->addWidget(searchInput);
    // 安装事件过滤器，当点击搜索框时切换到搜索页面
    searchInput->installEventFilter(this);

    // ========== 导航按钮(消息、好友、群组) ==========
    QHBoxLayout *navLayout = new QHBoxLayout;
    navLayout->setSpacing(8);

    btnMessage  = new QToolButton;
    btnContacts = new QToolButton;
    btnGroups   = new QToolButton;

    btnMessage->setText("消息");
    btnContacts->setText("好友");
    btnGroups->setText("群组");

    btnMessage->setCheckable(true);
    btnContacts->setCheckable(true);
    btnGroups->setCheckable(true);

    QString navBtnStyle = "QToolButton { font-size: 12px; padding: 4px 8px; }"
                          "QToolButton:checked { background-color: #e0e0e0; }";
    btnMessage->setStyleSheet(navBtnStyle);
    btnContacts->setStyleSheet(navBtnStyle);
    btnGroups->setStyleSheet(navBtnStyle);

    navLayout->addWidget(btnMessage);
    navLayout->addWidget(btnContacts);
    navLayout->addWidget(btnGroups);

    profileMainLayout->addLayout(navLayout);
    // 新增：导航按钮组（互斥选择）
    navButtonGroup = new QButtonGroup(this);
    navButtonGroup->addButton(btnMessage);
    navButtonGroup->addButton(btnContacts);
    navButtonGroup->addButton(btnGroups);
    navButtonGroup->setExclusive(true);
    // 默认选中“消息”
    btnMessage->setChecked(true);

    // 将个人信息区域加入左侧主布局
    mainLayout->addWidget(profileWidget);

//    // 添加一个垂直拉伸，让后续动态区域固定在底部
//    mainLayout->addStretch();

    // 初始化左侧动态区域（即 QStackedWidget）
    initLeftSidebarPages();

    // 将动态区域添加到左侧主布局（拉伸之后添加，所以在底部显示）
    mainLayout->addWidget(stackedListArea);
}
/**
 * @brief ChatMainWindow::createRightChatArea
 * 创建右侧聊天区布局：包含空白页、好友聊天页和群聊页
 */
void ChatMainPage::createRightChatArea()
{
    // 右侧主容器
    rightWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(rightWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 创建堆叠窗口
    rightStackedWidget = new QStackedWidget;
    layout->addWidget(rightStackedWidget);

    // 创建空白页面
    emptyPage = new QWidget;
    QVBoxLayout *emptyLayout = new QVBoxLayout(emptyPage);
    emptyPageLabel = new QLabel("请选择一个聊天");
    emptyPageLabel->setAlignment(Qt::AlignCenter);
    emptyPageLabel->setStyleSheet("font-size: 16px; color: #999;");
    emptyLayout->addWidget(emptyPageLabel);
    rightStackedWidget->addWidget(emptyPage);
    // 创建好友聊天页面
    createFriendChatUI();
    rightStackedWidget->addWidget(friendChatPage);

    // 创建群聊页面
    createGroupChatUI();
    rightStackedWidget->addWidget(groupChatPage);

    // 创建好友请求通知页面
    createFriendRequestPage();
    rightStackedWidget->addWidget(friendRequestPage);

    // 创建群组请求通知页面
    createGroupRequestPage();
    rightStackedWidget->addWidget(groupRequestPage);

    // 默认显示空白页面
    rightStackedWidget->setCurrentWidget(emptyPage);
}
void ChatMainPage::createFriendRequestPage()
{
    friendRequestPage = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(friendRequestPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    friendRequestList = new QListWidget;
    friendRequestList->setStyleSheet(
        "QListWidget { background: white; border: none; }"
        "QListWidget::item { border-bottom: 1px solid #eee; }"
    );

    // 添加示例数据
    addFriendRequestItem("张三", true, "pending", QDateTime::currentDateTime());  // 发出的请求
    addFriendRequestItem("李四", false, "waiting", QDateTime::currentDateTime()); // 收到的请求

    mainLayout->addWidget(friendRequestList);
}
void ChatMainPage::addFriendRequestItem(const QString &name, bool isOutgoing, const QString &status, const QDateTime &date)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(0, 70));

    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(15, 5, 15, 5);

    // 头像
    QLabel *avatar = new QLabel;
    avatar->setPixmap(circularAvatar(QPixmap(":/avatar.png"), 40));
    layout->addWidget(avatar);

    // 文字信息
    QVBoxLayout *infoLayout = new QVBoxLayout;
    QLabel *text = new QLabel;
    QLabel *time = new QLabel(date.toString("yyyy-MM-dd hh:mm"));
    time->setStyleSheet("color: #999; font-size: 12px;");

    if(isOutgoing){
        text->setText(QString("%1 正在回应你的好友申请").arg(name));
    }else{
        text->setText(QString("%1 申请添加好友").arg(name));
    }
    infoLayout->addWidget(text);
    infoLayout->addWidget(time);
    layout->addLayout(infoLayout, 1);

    // 右侧操作区
    if(status == "pending"){
        QLabel *statusLabel = new QLabel("等待回应");
        statusLabel->setStyleSheet("color: #666;");
        layout->addWidget(statusLabel);
    }else if(status == "waiting"){
        QPushButton *acceptBtn = new QPushButton("同意");
        QPushButton *rejectBtn = new QPushButton("拒绝");
        // 按钮样式
        QString btnStyle = "QPushButton { border-radius:15px; padding:5px 15px; }";
        acceptBtn->setStyleSheet(btnStyle + "background: #0084ff; color: white;");
        rejectBtn->setStyleSheet(btnStyle + "background: #f0f0f0; color: #666;");

        // 连接信号
        connect(acceptBtn, &QPushButton::clicked, [=](){ updateFriendRequestStatus(item, "accepted"); });
        connect(rejectBtn, &QPushButton::clicked, [=](){ updateFriendRequestStatus(item, "rejected"); });

        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->addWidget(acceptBtn);
        btnLayout->addWidget(rejectBtn);
        layout->addLayout(btnLayout);
    }

    friendRequestList->addItem(item);
    friendRequestList->setItemWidget(item, widget);
}
void ChatMainPage::updateFriendRequestStatus(QListWidgetItem *item, const QString &status)
{
    QWidget *widget = friendRequestList->itemWidget(item);
    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(widget->layout());
    QLayoutItem *lastItem = layout->itemAt(layout->count()-1);

    // 移除原有按钮
    if(QLayout *btnLayout = lastItem->layout()){
        QLayoutItem *child;
        while ((child = btnLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        layout->removeItem(btnLayout);
        delete btnLayout;
    }

    // 添加状态标签
    QLabel *statusLabel = new QLabel;
    if(status == "accepted"){
        statusLabel->setText("已同意");
        statusLabel->setStyleSheet("color: #52c41a;");
    }else{
        statusLabel->setText("已拒绝");
        statusLabel->setStyleSheet("color: #ff4d4f;");
    }
    layout->addWidget(statusLabel);
}
void ChatMainPage::createGroupRequestPage()
{
    groupRequestPage = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(groupRequestPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    groupRequestList = new QListWidget;
    groupRequestList->setStyleSheet(friendRequestList->styleSheet());

    // 添加示例数据
    addGroupRequestItem("技术交流群", "王五", "join", QDateTime::currentDateTime());
    addGroupRequestItem("项目组", "李四", "invite", QDateTime::currentDateTime());

    mainLayout->addWidget(groupRequestList);
}

void ChatMainPage::addGroupRequestItem(const QString &groupName, const QString &userName, const QString &type, const QDateTime &date)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(0, 70));

    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(15, 5, 15, 5);

    // 头像
    QLabel *avatar = new QLabel;
    avatar->setPixmap(circularAvatar(QPixmap(":/avatar.png"), 40));
    layout->addWidget(avatar);

    // 文字信息
    QVBoxLayout *infoLayout = new QVBoxLayout;
    QLabel *text = new QLabel;
    if(type == "join"){
        text->setText(QString("%1 申请加入群组 %2").arg(userName).arg(groupName));
    }else{
        text->setText(QString("%1 邀请你加入群组 %2").arg(userName).arg(groupName));
    }
    QLabel *time = new QLabel(date.toString("yyyy-MM-dd hh:mm"));
    time->setStyleSheet("color: #999;");
    infoLayout->addWidget(text);
    infoLayout->addWidget(time);
    layout->addLayout(infoLayout, 1);

    // 操作按钮
    QPushButton *acceptBtn = new QPushButton("同意");
    QPushButton *rejectBtn = new QPushButton("拒绝");
    // 按钮样式
    QString btnStyle = "QPushButton { border-radius:15px; padding:5px 15px; }";
    acceptBtn->setStyleSheet(btnStyle + "background: #0084ff; color: white;");
    rejectBtn->setStyleSheet(btnStyle + "background: #f0f0f0; color: #666;");

    // 连接信号
    connect(acceptBtn, &QPushButton::clicked, [=](){ updateGroupRequestStatus(item, "accepted"); });
    connect(rejectBtn, &QPushButton::clicked, [=](){ updateGroupRequestStatus(item, "rejected"); });

    // ...按钮样式和信号连接与好友页面类似...
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(acceptBtn);
    btnLayout->addWidget(rejectBtn);
    layout->addLayout(btnLayout);
    groupRequestList->addItem(item);
    groupRequestList->setItemWidget(item, widget);
}
void ChatMainPage::updateGroupRequestStatus(QListWidgetItem *item, const QString &status)
{
    if (!item || !groupRequestList) return;

    QWidget *widget = groupRequestList->itemWidget(item);
    if (!widget) return;

    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(widget->layout());
    if (!layout) return;

    // 移除原有按钮
    QLayoutItem *lastItem = layout->itemAt(layout->count()-1);
    if (QLayout *btnLayout = lastItem->layout()) {
        QLayoutItem *child;
        while ((child = btnLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        layout->removeItem(btnLayout);
        delete btnLayout;
    }

    // 添加状态标签
    QLabel *statusLabel = new QLabel;
    if (status == "accepted") {
        statusLabel->setText("已同意");
        statusLabel->setStyleSheet("color: #52c41a;");
    } else {
        statusLabel->setText("已拒绝");
        statusLabel->setStyleSheet("color: #ff4d4f;");
    }
    layout->addWidget(statusLabel);
}
/**
 * @brief ChatMainWindow::createFriendChatUI
 * 创建好友聊天界面
 */
void ChatMainPage::createFriendChatUI()
{
    friendChatPage = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(friendChatPage);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // ========== 顶部栏 ==========
    friendChatHeader = new QWidget;
    friendChatHeader->setFixedHeight(50);
    friendChatHeader->setStyleSheet("background-color: #f5f5f5; border-bottom: 1px solid #ddd;");
    QHBoxLayout *headerLayout = new QHBoxLayout(friendChatHeader);

    friendNameLabel = new QLabel("好友昵称");
    friendNameLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    friendNameLabel->setCursor(Qt::PointingHandCursor);
    friendNameLabel->installEventFilter(this);


    editFriendBtn = new QPushButton("编辑");
    editFriendBtn->setStyleSheet("QPushButton { border: 1px solid #ddd; border-radius: 4px; padding: 4px 8px; }");
    editFriendBtn->setFixedWidth(60);

    headerLayout->addWidget(friendNameLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(editFriendBtn);

    layout->addWidget(friendChatHeader);

    // ========== 聊天记录区 ==========
    // 聊天记录区
    // 聊天记录区
    friendChatHistory = new QListWidget;
    friendChatHistory->setStyleSheet(
       "QListWidget { background: #f8f9fa; border: none; }"
       "QListWidget::item { border: none; padding: 0px; margin: 0px; }" // 移除所有间距
       "QListWidget::item:selected { background: transparent; }"
       "QScrollBar:vertical { width: 8px; background: transparent; }"
       "QScrollBar::handle:vertical { background: #ccc; border-radius: 4px; min-height: 30px; }"
       "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
       "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }"
    );
    //QListWidget 在大小变化时，自动重新计算子项布局
    friendChatHistory->setResizeMode(QListView::Adjust);
    friendChatHistory->setFlow(QListView::TopToBottom);
    friendChatHistory->setWrapping(false);

    // 设置像素级滚动
    friendChatHistory->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    friendChatHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 使用QScroller实现平滑滚动
    QScroller::grabGesture(friendChatHistory, QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(friendChatHistory, QScroller::MiddleMouseButtonGesture);

    // 配置滚动属性
    QScrollerProperties scrollerProperties = QScroller::scroller(friendChatHistory)->scrollerProperties();
    scrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    scrollerProperties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0.0); // 立即响应
    scrollerProperties.setScrollMetric(QScrollerProperties::DragStartDistance, 0.0);    // 立即开始拖动
    scrollerProperties.setScrollMetric(QScrollerProperties::ScrollingCurve, QEasingCurve::OutCubic); // 平滑曲线
    scrollerProperties.setScrollMetric(QScrollerProperties::DecelerationFactor, 0.05);  // 较小的减速因子
    scrollerProperties.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.5);      // 限制最大速度
    QScroller::scroller(friendChatHistory)->setScrollerProperties(scrollerProperties);

    // 安装事件过滤器处理鼠标滚轮事件
    friendChatHistory->viewport()->installEventFilter(this);
    layout->addWidget(friendChatHistory, 1);

    // ========== 底部操作栏 ==========
    friendChatInputArea = new QWidget;
    QVBoxLayout *inputLayout = new QVBoxLayout(friendChatInputArea);
    inputLayout->setContentsMargins(10, 5, 10, 10);
    inputLayout->setSpacing(5);

    // 功能按钮栏
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(10);

    friendEmojiBtn = new QPushButton("😊 表情");
    friendFileBtn = new QPushButton("📎 文件");
    friendImageBtn = new QPushButton("🖼️ 图片");
    friendShakeBtn = new QPushButton("📳 抖动");

    QString btnStyle = "QPushButton { background: #f0f0f0; border-radius: 4px; padding: 5px 10px; }";
    friendEmojiBtn->setStyleSheet(btnStyle);
    friendFileBtn->setStyleSheet(btnStyle);
    friendImageBtn->setStyleSheet(btnStyle);
    friendShakeBtn->setStyleSheet(btnStyle);

    btnLayout->addWidget(friendEmojiBtn);
    btnLayout->addWidget(friendFileBtn);
    btnLayout->addWidget(friendImageBtn);
    btnLayout->addWidget(friendShakeBtn);
    btnLayout->addStretch();

    inputLayout->addLayout(btnLayout);

    // 输入框和发送按钮
    QHBoxLayout *sendLayout = new QHBoxLayout;
    friendMessageInput = new QTextEdit;
    friendMessageInput->setPlaceholderText("输入消息...");
    friendMessageInput->setMaximumHeight(80);
    friendMessageInput->setStyleSheet("border: 1px solid #ddd; border-radius: 4px; padding: 8px;");

    friendSendBtn = new QPushButton("发送");
    friendSendBtn->setMinimumWidth(80);
    friendSendBtn->setStyleSheet("background: #0084ff; color: white; border-radius: 4px;");

    sendLayout->addWidget(friendMessageInput, 4);
    sendLayout->addWidget(friendSendBtn, 1);

    inputLayout->addLayout(sendLayout);
    layout->addWidget(friendChatInputArea);
}
/**
 * @brief ChatMainWindow::createGroupChatUI
 * 创建群聊界面
 */
void ChatMainPage::createGroupChatUI()
{
    groupChatPage = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(groupChatPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 创建水平分割器，左侧是聊天区，右侧是成员列表
    groupChatSplitter = new QSplitter(Qt::Horizontal);
    mainLayout->addWidget(groupChatSplitter);

    // ========== 左侧聊天区 ==========
    groupChatLeftArea = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(groupChatLeftArea);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);

    // 顶部栏
    groupChatHeader = new QWidget;
    groupChatHeader->setFixedHeight(50);
    groupChatHeader->setStyleSheet("background-color: #f5f5f5; border-bottom: 1px solid #ddd;");
    QHBoxLayout *headerLayout = new QHBoxLayout(groupChatHeader);

    groupNameLabel = new QLabel("群聊名称 (0)");
    groupNameLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    editGroupBtn = new QPushButton("编辑");
    editGroupBtn->setStyleSheet("QPushButton { border: 1px solid #ddd; border-radius: 4px; padding: 4px 8px; }");
    editGroupBtn->setFixedWidth(60);

    toggleMemberListBtn = new QPushButton("成员列表 ▶");
    toggleMemberListBtn->setStyleSheet("QPushButton { border: 1px solid #ddd; border-radius: 4px; padding: 4px 8px; }");

    headerLayout->addWidget(groupNameLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(toggleMemberListBtn);
    headerLayout->addWidget(editGroupBtn);

    leftLayout->addWidget(groupChatHeader);

    // 聊天记录区
    groupChatHistory = new QListWidget;

    //QListWidget 在大小变化时，自动重新计算子项布局
    groupChatHistory->setResizeMode(QListView::Adjust);
    groupChatHistory->setFlow(QListView::TopToBottom);
    groupChatHistory->setWrapping(false);

    groupChatHistory->setMinimumWidth(300);
    groupChatHistory->setStyleSheet(
     "QListWidget { background: #f8f9fa; border: none; }"
     "QListWidget::item { border: none; padding: 0px; margin: 0px; }" // 移除所有间距
     "QListWidget::item:selected { background: transparent; }"
     "QScrollBar:vertical { width: 8px; background: transparent; }"
     "QScrollBar::handle:vertical { background: #ccc; border-radius: 4px; min-height: 30px; }"
     "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
     "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }"
    );

    // 设置像素级滚动
    groupChatHistory->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    groupChatHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 使用QScroller实现平滑滚动
    QScroller::grabGesture(groupChatHistory, QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(groupChatHistory, QScroller::MiddleMouseButtonGesture);

    // 配置滚动属性
    QScrollerProperties scrollerProperties = QScroller::scroller(groupChatHistory)->scrollerProperties();
    scrollerProperties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    scrollerProperties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0.0);
    scrollerProperties.setScrollMetric(QScrollerProperties::DragStartDistance, 0.0);
    scrollerProperties.setScrollMetric(QScrollerProperties::ScrollingCurve, QEasingCurve::OutCubic);
    scrollerProperties.setScrollMetric(QScrollerProperties::DecelerationFactor, 0.05);
    scrollerProperties.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.5);
    QScroller::scroller(groupChatHistory)->setScrollerProperties(scrollerProperties);

    // 安装事件过滤器处理鼠标滚轮事件
    groupChatHistory->viewport()->installEventFilter(this);
    leftLayout->addWidget(groupChatHistory, 1);

    // 底部操作栏
    groupChatInputArea = new QWidget;
    QVBoxLayout *inputLayout = new QVBoxLayout(groupChatInputArea);
    inputLayout->setContentsMargins(10, 5, 10, 10);
    inputLayout->setSpacing(5);

    // 功能按钮栏
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(10);

    groupEmojiBtn = new QPushButton("😊 表情");
    groupFileBtn = new QPushButton("📎 文件");
    groupImageBtn = new QPushButton("🖼️ 图片");

    QString btnStyle = "QPushButton { background: #f0f0f0; border-radius: 4px; padding: 5px 10px; }";
    groupEmojiBtn->setStyleSheet(btnStyle);
    groupFileBtn->setStyleSheet(btnStyle);
    groupImageBtn->setStyleSheet(btnStyle);

    btnLayout->addWidget(groupEmojiBtn);
    btnLayout->addWidget(groupFileBtn);
    btnLayout->addWidget(groupImageBtn);
    btnLayout->addStretch();

    inputLayout->addLayout(btnLayout);

    // 输入框和发送按钮
    QHBoxLayout *sendLayout = new QHBoxLayout;
    groupMessageInput = new QTextEdit;
    groupMessageInput->setPlaceholderText("输入消息...");
    groupMessageInput->setMaximumHeight(80);
    groupMessageInput->setStyleSheet("border: 1px solid #ddd; border-radius: 4px; padding: 8px;");

    groupSendBtn = new QPushButton("发送");
    groupSendBtn->setMinimumWidth(80);
    groupSendBtn->setStyleSheet("background: #0084ff; color: white; border-radius: 4px;");

    sendLayout->addWidget(groupMessageInput, 4);
    sendLayout->addWidget(groupSendBtn, 1);

    inputLayout->addLayout(sendLayout);
    leftLayout->addWidget(groupChatInputArea);

    // ========== 右侧成员列表 ==========
    groupMemberArea = new QWidget;
    QVBoxLayout *memberLayout = new QVBoxLayout(groupMemberArea);
    memberLayout->setContentsMargins(10, 10, 10, 10);

    memberCountLabel = new QLabel("群成员 (0)");
    memberCountLabel->setStyleSheet("font-size: 14px; font-weight: bold; margin-bottom: 10px;");

    groupMemberList = new QListWidget;
    groupMemberList->setStyleSheet(
        "QListWidget { border: none; }"
        "QListWidget::item { padding: 5px; }"
    );

    memberLayout->addWidget(memberCountLabel);
    memberLayout->addWidget(groupMemberList, 1);

    // 添加左右两部分到分割器
    groupChatSplitter->addWidget(groupChatLeftArea);
    groupChatSplitter->addWidget(groupMemberArea);

    // 设置初始比例 (7:3)
    groupChatSplitter->setStretchFactor(0, 7);
    groupChatSplitter->setStretchFactor(1, 3);

    // 默认隐藏成员列表
    isMemberListVisible = true;
    toggleGroupMemberList(); // 这会将其隐藏
}

bool ChatMainPage::eventFilter(QObject *watched, QEvent *event)
{
    // 处理鼠标滚轮事件，实现平滑滚动
    if (event->type() == QEvent::Wheel) {
        // 判断是哪个视口触发了事件
        if (watched == friendChatHistory->viewport() || watched == groupChatHistory->viewport()) {
            QListWidget *listWidget = (watched == friendChatHistory->viewport()) ?
                                      friendChatHistory : groupChatHistory;

            // 获取当前滚动位置
            int value = listWidget->verticalScrollBar()->value();

            // 固定小增量滚动，不依赖于滚轮事件的具体值
            int delta = 30; // 每次滚动5个像素

            // 根据滚轮方向决定滚动方向
            if (static_cast<QWheelEvent*>(event)->delta() > 0)  {
                listWidget->verticalScrollBar()->setValue(value - delta);
            } else {
                listWidget->verticalScrollBar()->setValue(value + delta);
            }

            // 事件已处理
            return true;
        }
    }

    // 处理搜索框点击事件
    if (watched == searchInput && event->type() == QEvent::MouseButtonPress) {
        // 切换到搜索结果页面，同时取消导航按钮的选中状态
        stackedListArea->setCurrentWidget(searchWidget);
        btnMessage->setChecked(false);
        btnContacts->setChecked(false);
        btnGroups->setChecked(false);
    }

    // 默认事件处理
    return QMainWindow::eventFilter(watched, event);
}


QPixmap ChatMainPage::circularAvatar(const QPixmap &src, int diameter)
{
    if(src.isNull())
        return QPixmap();
    QPixmap circular(diameter, diameter);
    circular.fill(Qt::transparent);
    QPainter painter(&circular);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(0, 0, diameter, diameter);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, diameter, diameter, src);
    return circular;
}


/**
 * @brief ChatMainWindow::applyStyles
 * 统一管理所有控件的样式设置，方便后续修改和维护
 */


void ChatMainPage::applyStyles()
{
    // ========== 设置头像为圆形 ==========
    // 如果您有自己的头像资源，可自行替换
    QPixmap sourcePix(":/avatar.png");
    if(!sourcePix.isNull()) {
        QPixmap circularPix(60, 60);
        circularPix.fill(Qt::transparent);

        QPainter painter(&circularPix);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.addEllipse(0, 0, 60, 60);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, 60, 60, sourcePix);
        avatarLabel->setPixmap(circularPix);
    }

    // 在线状态指示器样式
    statusIndicator->setStyleSheet(
        "background-color: #52c41a;"  // 在线颜色
        "border-radius:7px;"
        "border:2px solid white;"
    );

    // ========== 样式：圆角按钮 + 边框 ==========
    QString roundButtonStyle = R"(
        QPushButton {
            background: transparent;
            border: 1px solid #ddd;
            padding: 7px 12px;
            color: #666;
            font: 13px 'Microsoft YaHei';
            border-radius: 4px;
        }
        QPushButton:hover {
            background: #f0f0f0;
        }
        QPushButton:pressed {
            background: #e0e0e0;
        }
    )";

    // 应用于 设置、加好友/群、创建群聊 三个按钮
    settingsBtn->setStyleSheet(roundButtonStyle);
    btnAdd->setStyleSheet(roundButtonStyle);
    btnGroup->setStyleSheet(roundButtonStyle);

    // ========== 名称、ID、宣言标签的样式 ==========
    nameLabel->setStyleSheet("font: 16px 'Microsoft YaHei'; color: #333;");
    idLabel->setStyleSheet("font: 12px 'Microsoft YaHei'; color: #666;");
    onlineTextLabel->setStyleSheet("font: 12px 'Microsoft YaHei'; color: #52c41a;");
    signLabel->setStyleSheet("font: 12px 'Microsoft YaHei'; color: #999;");

    // ========== 搜索框样式 ==========
    searchInput->setStyleSheet(R"(
        QLineEdit {
            padding:8px 15px;
            border:1px solid #ddd;
            border-radius:15px;
            font:13px 'Microsoft YaHei';
        }
    )");

    // ========== 导航按钮样式 ==========
    QString navStyle = R"(
        QToolButton {
            padding:8px 15px;
            border-radius:15px;
            font:13px 'Microsoft YaHei';
            color:#666;
        }
        QToolButton:hover {
            background:#f0f0f0;
        }
        QToolButton:checked {
            background:#e0f0ff;
            color:#1890ff;
        }
    )";
    btnMessage->setStyleSheet(navStyle);
    btnContacts->setStyleSheet(navStyle);
    btnGroups->setStyleSheet(navStyle);

    // ====== 统一设置各个列表控件的样式 ======
    // 定义列表项样式（调整最小高度和内边距）
    QString listItemStyle = "QListWidget { font-size: 12px; } QListWidget::item { min-height: 50px; padding: 5px; }";
    QSize iconSize(40, 40);  // 设置头像图标的大小

    if(messageList) {
        messageList->setStyleSheet(listItemStyle);
        messageList->setIconSize(iconSize);
    }
    if(friendList) {
        friendList->setStyleSheet(listItemStyle);
        friendList->setIconSize(iconSize);
    }
    if(groupList) {
        groupList->setStyleSheet(listItemStyle);
        groupList->setIconSize(iconSize);
    }
    if(searchFriendList) {
        searchFriendList->setStyleSheet(listItemStyle);
        searchFriendList->setIconSize(iconSize);
    }
    if(searchGroupList) {
        searchGroupList->setStyleSheet(listItemStyle);
        searchGroupList->setIconSize(iconSize);
    }
    if(searchChatList) {
        searchChatList->setStyleSheet(listItemStyle);
        searchChatList->setIconSize(iconSize);
    }
}

/**
 * @brief ChatMainWindow::setupConnections
 * 建立界面控件之间的信号槽连接
 */
void ChatMainPage::setupConnections()
{
    // “设置”按钮点击
    connect(settingsBtn, &QPushButton::clicked, this, &ChatMainPage::showSettingsMenu);

    // 导航按钮点击切换动态区域
    connect(btnMessage, &QToolButton::clicked, this, [=](){
        stackedListArea->setCurrentWidget(messageList);
    });
    connect(btnContacts, &QToolButton::clicked, this, [=](){
        stackedListArea->setCurrentWidget(friendWidget);
    });
    connect(btnGroups, &QToolButton::clicked, this, [=](){
        stackedListArea->setCurrentWidget(groupWidget);
    });
    // 新增：消息列表项点击
    connect(messageList, &QListWidget::itemClicked, this, &ChatMainPage::onMessageItemClicked);

    // 新增：好友列表项点击
    connect(friendList, &QListWidget::itemClicked, this, &ChatMainPage::onFriendItemClicked);

    // 新增：群组列表项点击
    connect(groupList, &QListWidget::itemClicked, this, &ChatMainPage::onGroupItemClicked);

    // 新增：切换群成员列表显示
    connect(toggleMemberListBtn, &QPushButton::clicked, this, &ChatMainPage::toggleGroupMemberList);

    // 在setupConnections函数中添加
    connect(friendNotifyBtn, &QPushButton::clicked, [=](){
        rightStackedWidget->setCurrentWidget(friendRequestPage);
    });

    connect(groupNotifyBtn, &QPushButton::clicked, [=](){
        rightStackedWidget->setCurrentWidget(groupRequestPage);
    });
    connect(btnGroup, &QPushButton::clicked, this, &ChatMainPage::createGroupChat);
    connect(btnAdd, &QPushButton::clicked, this, &ChatMainPage::addFriendGroup);
    // 连接好友编辑按钮点击信号到对应槽函数
    connect(editFriendBtn, &QPushButton::clicked, this, &ChatMainPage::editFriendInfo);

    // 连接群聊编辑按钮点击信号到对应槽函数
    connect(editGroupBtn, &QPushButton::clicked, this, &ChatMainPage::editGroupInfo);

    //菜单栏处理
    connect(editAction,   &QAction::triggered, this, &ChatMainPage::editProfile);

    connect(pwdAction,    &QAction::triggered, this, &ChatMainPage::changePassword);

    connect(logoutAction, &QAction::triggered, this, &ChatMainPage::backToLoginPage);


    // 可根据需要继续添加其他按钮、输入框的信号槽
}
/**
 * @brief ChatMainWindow::onMessageItemClicked
 * 处理消息列表项点击事件
 * @param item 被点击的列表项
 */
void ChatMainPage::onMessageItemClicked(QListWidgetItem *item)
{
    if (!item) return;

    QString text = item->text();
    // 简单判断是好友还是群聊（实际应用中应该有更好的方式）
    if (text.contains("张三")) {
        // 显示好友聊天页面
        friendNameLabel->setText("张三");
        rightStackedWidget->setCurrentWidget(friendChatPage);
        // 添加示例消息
        addExampleMessages();
    } else if (text.contains("李四")) {
        // 显示好友聊天页面
        friendNameLabel->setText("李四");
        rightStackedWidget->setCurrentWidget(friendChatPage);
        // 添加示例消息
        addExampleMessages();
    }
}
/**
 * @brief ChatMainWindow::onFriendItemClicked
 * 处理好友列表项点击事件
 * @param item 被点击的列表项
 */
void ChatMainPage::onFriendItemClicked(QListWidgetItem *item)
{
    if (!item) return;

    // 显示好友聊天页面
    friendNameLabel->setText(item->text());
    rightStackedWidget->setCurrentWidget(friendChatPage);
    // 添加示例消息
    addExampleMessages();
}

/**
 * @brief ChatMainWindow::onGroupItemClicked
 * 处理群组列表项点击事件
 * @param item 被点击的列表项
 */
void ChatMainPage::onGroupItemClicked(QListWidgetItem *item)
{
    if (!item) return;

    // 显示群聊页面
    QString groupName = item->text();
    groupNameLabel->setText(groupName + " (5)");
    memberCountLabel->setText("群成员 (5)");

    // 清空并添加示例群成员
    groupMemberList->clear();
    QPixmap avatarPix = circularAvatar(QPixmap(":/avatar.png"), 30);
    groupMemberList->addItem(new QListWidgetItem(QIcon(avatarPix), "张三 (群主)"));
    groupMemberList->addItem(new QListWidgetItem(QIcon(avatarPix), "李四"));
    groupMemberList->addItem(new QListWidgetItem(QIcon(avatarPix), "王五"));
    groupMemberList->addItem(new QListWidgetItem(QIcon(avatarPix), "赵六"));
    groupMemberList->addItem(new QListWidgetItem(QIcon(avatarPix), "清风徐来 (我)"));

    rightStackedWidget->setCurrentWidget(groupChatPage);

    // 添加示例消息
    addExampleMessages();
}
/**
 * @brief ChatMainWindow::toggleGroupMemberList
 * 切换群成员列表的显示/隐藏状态
 */
void ChatMainPage::toggleGroupMemberList()
{
    isMemberListVisible = !isMemberListVisible;

    if (isMemberListVisible) {
        // 显示成员列表，设定一个合适的左右比例，例如 7:3
        groupMemberArea->show();
        toggleMemberListBtn->setText("成员列表 ◀");

        int totalWidth = groupChatSplitter->width();
        int chatWidth = totalWidth * 0.7;
        int memberWidth = totalWidth - chatWidth;
        // 让左侧聊天区和右侧成员区分别占 70% 和 30%
        groupChatSplitter->setSizes({ chatWidth, memberWidth });

    } else {
        // 隐藏成员列表，让聊天区独占
        groupMemberArea->hide();
        toggleMemberListBtn->setText("成员列表 ▶");

        // 也可以直接把右侧宽度设置为0
        groupChatSplitter->setSizes({ groupChatSplitter->width(), 0 });
    }

    // 强制刷新聊天记录区
    groupChatHistory->doItemsLayout();
    groupChatHistory->updateGeometry();
    groupChatHistory->update();
    groupChatHistory->scrollToBottom();
}



/**
 * @brief ChatMainWindow::addExampleMessages
 * 添加示例聊天消息
 */
void ChatMainPage::addExampleMessages()
{
    // 判断当前显示的是哪个聊天页面
    QListWidget *currentChatHistory = nullptr;

    if (rightStackedWidget->currentWidget() == friendChatPage) {
        currentChatHistory = friendChatHistory;
        // 清空历史消息
        currentChatHistory->clear();

        // 添加10条示例消息
        addFriendChatMessage(currentChatHistory, false, "你好！");
        addFriendChatMessage(currentChatHistory, true, "嗨，最近怎么样？");
        addFriendChatMessage(currentChatHistory, false, "挺好的，在学习Qt开发。");
        addFriendChatMessage(currentChatHistory, true, "那很棒啊！我也在用Qt做一个项目。");
        addFriendChatMessage(currentChatHistory, false, "真的吗？是什么类型的项目？");
        addFriendChatMessage(currentChatHistory, true, "一个聊天应用，类似于我们现在用的这个。");
        addFriendChatMessage(currentChatHistory, false, "听起来很有挑战性，你是如何处理网络通信的？");
        addFriendChatMessage(currentChatHistory, true, "我使用了Qt的网络模块，主要是QTcpSocket和QTcpServer类。服务器端使用了多线程处理并发连接，客户端则使用信号槽机制处理异步通信。");
        addFriendChatMessage(currentChatHistory, false, "数据库用的什么？SQLite还是MySQL？");
        addFriendChatMessage(currentChatHistory, true, "客户端用SQLite存储本地聊天记录，服务器端用MySQL存储用户数据和离线消息。Qt的数据库模块真的很方便，QSqlQuery和QSqlTableModel让数据操作变得简单。");

        // 滚动到最新消息
        currentChatHistory->scrollToBottom();
    }
    else if (rightStackedWidget->currentWidget() == groupChatPage) {
        currentChatHistory = groupChatHistory;
        // 清空历史消息
        currentChatHistory->clear();

        // 添加10条示例消息
        addGroupChatMessage(currentChatHistory, "张三", false, "大家好，今天我们讨论一下项目进度。");
        addGroupChatMessage(currentChatHistory, "李四", false, "好的，我这边已经完成了界面设计部分。");
        addGroupChatMessage(currentChatHistory, "清风徐来", true, "我负责的后端接口也已经开发完毕，可以开始联调了。");
        addGroupChatMessage(currentChatHistory, "王五", false, "数据库设计和实现已经完成，包括用户表、消息表和群组表。");
        addGroupChatMessage(currentChatHistory, "赵六", false, "我负责的移动端适配还在进行中，预计下周完成。");
        addGroupChatMessage(currentChatHistory, "张三", false, "好的，那我们下周一开始联调测试。");
        addGroupChatMessage(currentChatHistory, "清风徐来", true, "没问题，我会准备好测试环境。");
        addGroupChatMessage(currentChatHistory, "李四", false, "我有个问题，关于消息加密的实现，我们是用什么方案？");
        addGroupChatMessage(currentChatHistory, "王五", false, "我们计划使用AES-256加密，密钥通过RSA非对称加密交换。");
        addGroupChatMessage(currentChatHistory, "张三", false, "好的，那就按这个方案实施。大家还有其他问题吗？");

        // 滚动到最新消息
        currentChatHistory->scrollToBottom();
    }
}

/** @brief ChatMainWindow::addFriendChatMessage
* 添加好友聊天消息
* @param listWidget 聊天记录列表
* @param isMe 是否是自己发送的消息
* @param message 消息内容
*/
void ChatMainPage::addFriendChatMessage(QListWidget *listWidget, bool isMe, const QString &message)
{
   QListWidgetItem *item = new QListWidgetItem;
   QWidget *bubble = new QWidget;
   QHBoxLayout *layout = new QHBoxLayout(bubble);
   layout->setContentsMargins(8, 5, 8, 8);  // 增加外部边距
   layout->setSpacing(8);  // 增加内部间距

   // 头像设置
   QLabel *avatar = new QLabel;
   avatar->setFixedSize(36, 36);
   avatar->setPixmap(circularAvatar(QPixmap(":/avatar.png"), 36));
   avatar->setAlignment(Qt::AlignTop);

   // 动态计算最大气泡宽度
   int maxBubbleWidth = qMax(int(listWidget->viewport()->width() * 0.7), 250);

   // 创建自定义文本编辑控件
   QTextEdit *msg = new QTextEdit;
   msg->setPlainText(message);
   msg->setReadOnly(true);
   msg->setFrameStyle(QFrame::NoFrame);
   msg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   msg->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   // 关键：计算适合的宽度和高度
   QFontMetrics fm(msg->font());
   QStringList lines = message.split("\n");
   int maxLineWidth = 0;

   // 找出最宽的单行长度
   foreach(const QString& line, lines) {
       int lineWidth = fm.horizontalAdvance(line);
       maxLineWidth = qMax(maxLineWidth, lineWidth);
   }

   // 确定适合的宽度
   int contentWidth;
   if (maxLineWidth < maxBubbleWidth - 30) {
       // 如果内容宽度小于最大宽度，则按内容宽度设置
       contentWidth = maxLineWidth + 30;  // 添加适当的边距
   } else {
       // 否则使用最大宽度
       contentWidth = maxBubbleWidth;
   }

   // 设置宽度和一个临时高度
   msg->setFixedWidth(contentWidth);
   msg->setMinimumHeight(1);  // 设置最小高度，后面会重新计算

   // 禁用自动格式化，避免额外边距
   msg->document()->setDocumentMargin(0);

   // 样式设置 - 适当增加内边距
   QString bubbleStyle = isMe ?
       "QTextEdit{background: #0084ff; color: white; border-radius: 12px; padding: 8px 10px;}" :
       "QTextEdit{background: white; color: #333; border: 1px solid #eee; border-radius: 12px; padding: 8px 10px;}";
   msg->setStyleSheet(bubbleStyle);

   // 布局逻辑
   if (isMe) {
       layout->addStretch();
       layout->addWidget(msg, 0, Qt::AlignRight | Qt::AlignTop);
       layout->addWidget(avatar, 0, Qt::AlignTop);
   } else {
       layout->addWidget(avatar, 0, Qt::AlignTop);
       layout->addWidget(msg, 0, Qt::AlignLeft | Qt::AlignTop);
       layout->addStretch();
   }

   listWidget->addItem(item);
   listWidget->setItemWidget(item, bubble);

   // 计算并设置准确的高度
   QTimer::singleShot(0, [=]() {
       // 获取文档高度
       int documentHeight = msg->document()->size().toSize().height();
       msg->setFixedHeight(documentHeight + 16);  // 增加垂直空间

       bubble->adjustSize();
       item->setSizeHint(bubble->sizeHint());
       listWidget->scrollToItem(item);
   });
}

/**
* @brief ChatMainWindow::addGroupChatMessage
* 添加群聊消息
* @param listWidget 聊天记录列表
* @param sender 发送者名称
* @param isMe 是否是自己发送的消息
* @param message 消息内容
*/
void ChatMainPage::addGroupChatMessage(QListWidget *listWidget, const QString &sender, bool isMe, const QString &message)
{
   QListWidgetItem *item = new QListWidgetItem;
   QWidget *bubble = new QWidget;
   QHBoxLayout *layout = new QHBoxLayout(bubble);
   layout->setContentsMargins(8, 5, 8, 8);  // 增加外部边距
   layout->setSpacing(8);  // 增加内部间距

   // ====== 头像 ======
   QLabel *avatar = new QLabel;
   avatar->setFixedSize(36, 36);
   avatar->setPixmap(circularAvatar(QPixmap(":/avatar.png"), 36));
   avatar->setAlignment(Qt::AlignTop);

   // ====== 消息容器 ======
   QWidget *msgContainer = new QWidget;
   QVBoxLayout *msgLayout = new QVBoxLayout(msgContainer);
   msgLayout->setContentsMargins(0, 0, 0, 0);  // 容器无边距
   msgLayout->setSpacing(3);  // 名称和消息间距

   // 动态计算最大气泡宽度
   int maxBubbleWidth = qMax(int(listWidget->viewport()->width() * 0.7), 250);

   // ====== 发送者名称 ======
   QLabel *nameLabel = new QLabel(sender);
   nameLabel->setStyleSheet("font: 12px 'Microsoft YaHei'; color: #666;");
   // 根据isMe调整名称对齐方式
   nameLabel->setAlignment(isMe ? Qt::AlignRight : Qt::AlignLeft);

   // ====== 消息内容 ======
   QTextEdit *msg = new QTextEdit;
   msg->setPlainText(message);
   msg->setReadOnly(true);
   msg->setFrameStyle(QFrame::NoFrame);
   msg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   msg->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   // 计算适合的宽度和高度
   QFontMetrics fm(msg->font());
   QStringList lines = message.split("\n");
   int maxLineWidth = 0;

   // 找出最宽的单行长度
   foreach(const QString& line, lines) {
       int lineWidth = fm.horizontalAdvance(line);
       maxLineWidth = qMax(maxLineWidth, lineWidth);
   }

   // 确定适合的宽度
   int contentWidth;
   if (maxLineWidth < maxBubbleWidth - 30) {
       contentWidth = maxLineWidth + 30;  // 添加适当的边距
   } else {
       contentWidth = maxBubbleWidth;
   }

   // 设置宽度和一个临时高度
   msg->setFixedWidth(contentWidth);
   msg->setMinimumHeight(1);

   // 禁用自动格式化，避免额外边距
   msg->document()->setDocumentMargin(0);

   // 样式设置 - 适当增加内边距
   QString bubbleStyle = isMe ?
       "QTextEdit{background: #0084ff; color: white; border-radius: 12px; padding: 8px 10px;}" :
       "QTextEdit{background: white; color: #333; border: 1px solid #eee; border-radius: 12px; padding: 8px 10px;}";
   msg->setStyleSheet(bubbleStyle);

   // ====== 布局组装 ======
   msgLayout->addWidget(nameLabel);
   msgLayout->addWidget(msg);

   if (isMe) {
       // 自己发送的消息: [拉伸占位][消息容器（名称右对齐）][头像]
      QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
      layout->addItem(spacer);
      layout->addWidget(msgContainer, 0, Qt::AlignRight);  // 右对齐消息容器
      layout->addWidget(avatar, 0, Qt::AlignTop);
   } else {
       // 他人发送的消息: [头像][消息容器（名称左对齐）][拉伸占位]
       layout->addWidget(avatar, 0, Qt::AlignTop);
       layout->addWidget(msgContainer);
       layout->addStretch();
   }

   // ====== 添加至列表 ======
   listWidget->addItem(item);
   listWidget->setItemWidget(item, bubble);

   // 计算并设置准确的高度
   QTimer::singleShot(0, [=]() {
       // 获取文档高度
       int documentHeight = msg->document()->size().toSize().height();
       msg->setFixedHeight(documentHeight + 16);  // 增加垂直空间

       bubble->adjustSize();
       item->setSizeHint(bubble->sizeHint());
       listWidget->scrollToItem(item);
   });
}


/**
 * @brief ChatMainWindow::initSettingsMenu
 * 初始化“设置”按钮对应的菜单
 */
void ChatMainPage::initSettingsMenu()
{
    if (!settingsMenu) {
        settingsMenu = new QMenu(this);
        settingsMenu->setStyleSheet(R"(
            QMenu {
                background: white;
                border: 1px solid #eee;
                border-radius: 4px;
                padding: 6px 0;
                min-width: 120px;
            }
            QMenu::item {
                padding: 8px 24px;
                font: 13px 'Microsoft YaHei';
                color: #666;
            }
            QMenu::item:selected {
                background: #f5f5f5;
            }
            QMenu::separator {
                height: 1px;
                background: #eee;
                margin: 4px 0;
            }
        )");

        // 添加菜单项
        editAction   = settingsMenu->addAction("✎ 编辑资料");
        pwdAction    = settingsMenu->addAction("🔒 修改密码");
        settingsMenu->addSeparator();
        logoutAction = settingsMenu->addAction("⎋ 退出登录");
        // 预加载菜单：将菜单先在屏幕外弹出后隐藏，提前计算好布局和样式
        settingsMenu->popup(QPoint(-1000, -1000));
        settingsMenu->hide();
    }
}


void ChatMainPage::initLeftSidebarPages()
{
    stackedListArea = new QStackedWidget;

    // ----- 消息页面 -----
    messageList = new QListWidget;
    QPixmap sourcePix(":/avatar.png");
    QPixmap avatarPix = circularAvatar(sourcePix, 40);
    QListWidgetItem *msgItem1 = new QListWidgetItem(QIcon(avatarPix), "张三    3条未读消息");
    QListWidgetItem *msgItem2 = new QListWidgetItem(QIcon(avatarPix), "李四    1条未读消息");
    messageList->addItem(msgItem1);
    messageList->addItem(msgItem2);
    stackedListArea->addWidget(messageList);

    // ----- 好友页面 -----
    friendWidget = new QWidget;
    QVBoxLayout *friendLayout = new QVBoxLayout(friendWidget);
    friendLayout->setContentsMargins(0, 0, 0, 0);
    friendLayout->setSpacing(0);
    friendNotifyBtn = new QPushButton("好友通知");
    friendNotifyBtn->setFixedHeight(40);
    friendNotifyBtn->setStyleSheet("text-align: left; padding-left: 10px;");
    friendLayout->addWidget(friendNotifyBtn);
    friendSeparator = new QFrame;
    friendSeparator->setFrameShape(QFrame::HLine);
    friendSeparator->setFrameShadow(QFrame::Sunken);
    friendLayout->addWidget(friendSeparator);
    friendList = new QListWidget;
    QListWidgetItem *friendItem1 = new QListWidgetItem(QIcon(avatarPix), "王五");
    QListWidgetItem *friendItem2 = new QListWidgetItem(QIcon(avatarPix), "赵六");
    friendList->addItem(friendItem1);
    friendList->addItem(friendItem2);
    friendLayout->addWidget(friendList);
    stackedListArea->addWidget(friendWidget);

    // ----- 群组页面 -----
    groupWidget = new QWidget;
    QVBoxLayout *groupLayout = new QVBoxLayout(groupWidget);
    groupLayout->setContentsMargins(0, 0, 0, 0);
    groupLayout->setSpacing(0);
    groupNotifyBtn = new QPushButton("群组通知");
    groupNotifyBtn->setFixedHeight(40);
    groupNotifyBtn->setStyleSheet("text-align: left; padding-left: 10px;");
    groupLayout->addWidget(groupNotifyBtn);
    groupSeparator = new QFrame;
    groupSeparator->setFrameShape(QFrame::HLine);
    groupSeparator->setFrameShadow(QFrame::Sunken);
    groupLayout->addWidget(groupSeparator);
    groupList = new QListWidget;
    QListWidgetItem *groupItem1 = new QListWidgetItem(QIcon(avatarPix), "技术交流群");
    QListWidgetItem *groupItem2 = new QListWidgetItem(QIcon(avatarPix), "项目组");
    groupList->addItem(groupItem1);
    groupList->addItem(groupItem2);
    groupLayout->addWidget(groupList);
    stackedListArea->addWidget(groupWidget);

    // ----- 搜索结果页面 -----
    searchWidget = new QWidget;
    QVBoxLayout *searchLayout = new QVBoxLayout(searchWidget);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(0);
    searchFriendList = new QListWidget;
    searchFriendList->addItem(new QListWidgetItem(QIcon(avatarPix), "搜索结果 - 好友: 张三"));
    searchLayout->addWidget(searchFriendList);
    searchFriendGroupSeparator = new QFrame;
    searchFriendGroupSeparator->setFrameShape(QFrame::HLine);
    searchFriendGroupSeparator->setFrameShadow(QFrame::Sunken);
    searchLayout->addWidget(searchFriendGroupSeparator);
    searchGroupList = new QListWidget;
    searchGroupList->addItem(new QListWidgetItem(QIcon(avatarPix), "搜索结果 - 群组: 技术交流群"));
    searchLayout->addWidget(searchGroupList);
    searchGroupChatSeparator = new QFrame;
    searchGroupChatSeparator->setFrameShape(QFrame::HLine);
    searchGroupChatSeparator->setFrameShadow(QFrame::Sunken);
    searchLayout->addWidget(searchGroupChatSeparator);
    searchChatList = new QListWidget;
    searchChatList->addItem(new QListWidgetItem(QIcon(avatarPix), "搜索结果 - 聊天: 李四: 你好"));
    searchLayout->addWidget(searchChatList);
    stackedListArea->addWidget(searchWidget);

    // 默认显示消息页面
    stackedListArea->setCurrentWidget(messageList);
}

/**
 * @brief ChatMainWindow::showSettingsMenu
 * 显示设置菜单
 */
void ChatMainPage::showSettingsMenu() {
    // 如果菜单已显示，隐藏之；否则在按钮下方弹出
    if (settingsMenu->isVisible()) {
         settingsMenu->hide();
    } else {
         settingsMenu->popup(settingsBtn->mapToGlobal(QPoint(0, settingsBtn->height())));
    }
}


/**
 * @brief ChatMainWindow::editProfile
 * 编辑资料功能
 */
void ChatMainPage::editProfile() {
    // 获取 idLabel 的文本
    QString text = idLabel->text();

    // 提取 id
    QString id = text.split("ID: ").value(1);
    emit editProfileRequested(id);
    if (!editProfileDlg) {
        editProfileDlg = new EditProfileDialog(this);
        connect(editProfileDlg, &EditProfileDialog::updateProfileRequest,this,&ChatMainPage::updateProfileRequest);
        connect(editProfileDlg, &EditProfileDialog::reject,[this]()
        {
            editProfileDlg->close();
        });
    }
    editProfileDlg->show();
}
void ChatMainPage::setEditProfile(const QString &name, const QString &sign, const QString &phone, const QPixmap &src)
{
    editProfileDlg->setNickname(name);
    editProfileDlg->setDeclaration(sign);
    editProfileDlg->setPhone(phone);
    editProfileDlg->setAvatar(src);
}


/**
 * @brief ChatMainWindow::changePassword
 * 修改密码功能
 */
void ChatMainPage::changePassword()
{
    qDebug() << "打开修改密码窗口...";
    // TODO: 实际应弹出密码修改窗口
}
void ChatMainPage::createGroupChat() {
    CreateGroupChatDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QString groupName = dlg.getGroupName();
        // 这里可扩展：调用创建群聊的逻辑，将 groupName 保存或发送给服务器
        qDebug() << "创建群聊:" << groupName;
    }
}

void ChatMainPage::addFriendGroup() {
    AddFriendGroupDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        //QString account = dlg.getInputAccount();
        // 这里可扩展：调用申请添加好友或群的逻辑，将 account 提交处理
        qDebug() << "申请添加:";
    }
}
void ChatMainPage::editFriendInfo() {
    // 创建好友信息对话框
    FriendInfoDialog dlg(this);

    // 设置已有的好友信息，数据可从已有控件或数据模型中获取
    // 示例中：头像使用主窗口的 avatarLabel（实际可换成好友专用头像控件），昵称取自 friendNameLabel，账号和宣言使用占位数据
    if (avatarLabel && avatarLabel->pixmap() && !avatarLabel->pixmap()->isNull()) {
        dlg.setAvatar(*avatarLabel->pixmap());
    }
    dlg.setNickname(friendNameLabel->text());
    dlg.setAccount("friend_account_001");  // 此处为示例账号
    dlg.setDeclaration("这是好友的宣言");
    dlg.setRemark("现有备注信息");

    // 显示对话框（模态）并根据返回结果处理
    if (dlg.exec() == QDialog::Accepted) {
        // 获取编辑后的备注信息
        QString newRemark = dlg.getRemark();
        qDebug() << "新的好友备注:" << newRemark;
        // TODO: 在数据模型中更新该好友的备注信息
    }
}

void ChatMainPage::editGroupInfo() {
    // 创建群聊信息对话框
    GroupInfoDialog dlg(this);

    // 设置已有的群聊信息
    if (avatarLabel && avatarLabel->pixmap() && !avatarLabel->pixmap()->isNull()) {
        dlg.setAvatar(*avatarLabel->pixmap());
    }
    dlg.setGroupName("技术交流群");      // 示例群聊名称
    dlg.setGroupID("group_123456");       // 示例群聊号
    dlg.setMemberCount("25");             // 示例群聊人数

    // 显示对话框（模态）并根据返回结果处理
    if (dlg.exec() == QDialog::Accepted) {
        qDebug() << "群聊信息对话框已确认";
        // TODO: 根据需要处理群聊信息的修改或相关操作
    }
}


