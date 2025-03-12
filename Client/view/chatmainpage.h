#ifndef CHATMAINPAGE_H
#define CHATMAINPAGE_H

#include <QMainWindow>
#include <QSplitter>
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QStackedWidget>   // 新增
#include <QButtonGroup>   // 新增
#include <QFrame>           // 新增
#include <QScrollArea>  // 新增
#include <QScrollerProperties>
#include <QEasingCurve>
#include <QScroller>
#include <QScrollBar>
#include <QWheelEvent>
#include <QTimer> // 需要添加此头文件
#include <QDialog>
#include "editprofiledialog.h"
#include "creategroupchatdialog.h"
#include "addfriendgroupdialog.h"
#include "friendinfodialog.h"
#include "groupinfodialog.h"
/**
 * @brief The ChatMainPage class
 * 聊天主页面类，包含左侧边栏和右侧聊天区。
 */
class ChatMainPage : public QMainWindow{
    Q_OBJECT
public:
    explicit ChatMainPage(QWidget *parent = nullptr);
    void setProfile(const QString name,const QString id,const QString sign,const QString status,const QPixmap &src);
    void setEditProfile(const QString &name, const QString &sign, const QString &phone, const QPixmap &src);

signals:
    //退出页面
    void backToLoginPage();
    //编辑
    void editProfileRequested(const QString &account); // 请求编辑资料
    void updateProfileRequest(const QString &nickname, const QString &declaration, const QString &phone, const QPixmap &avatar); // 发送更新请求信号
protected:
    // 重写事件过滤器，用于监听搜索框点击
    bool eventFilter(QObject *watched, QEvent *event) override;




private:

    void setupConnections();

    void initUI();
    void createLeftSidebar();
    void createRightChatArea();
    void applyStyles();

    void initSettingsMenu();
    // 新增：初始化左侧边栏动态页面
    void initLeftSidebarPages();
    // 新增：辅助函数，用于生成圆形头像
    QPixmap circularAvatar(const QPixmap &src, int diameter);

    // 新增：创建好友聊天界面
    void createFriendChatUI();
    // 新增：创建群聊界面
    void createGroupChatUI();
    // 新增：添加示例聊天消息
    void addExampleMessages();
    // 新增：添加好友聊天消息
    void addFriendChatMessage(QListWidget *listWidget, bool isMe, const QString &message);
    // 新增：添加群聊消息
    void addGroupChatMessage(QListWidget *listWidget, const QString &sender, bool isMe, const QString &message);
    // 创建好友请求页面
   void createFriendRequestPage();

   // 添加好友请求项到列表
   void addFriendRequestItem(const QString &name, bool isOutgoing, const QString &status, const QDateTime &date);

   // 更新请求项状态
   void updateFriendRequestStatus(QListWidgetItem *item, const QString &status);

   // 创建群组请求页面
   void createGroupRequestPage();

   // 添加群组请求项到列表
   void addGroupRequestItem(const QString &groupName, const QString &userName, const QString &type, const QDateTime &date);

   void updateGroupRequestStatus(QListWidgetItem *item, const QString &status);
private slots:
    void showSettingsMenu();
    void editProfile();
    void changePassword();
    // 新增：处理消息列表项点击
    void onMessageItemClicked(QListWidgetItem *item);
    // 新增：处理好友列表项点击
    void onFriendItemClicked(QListWidgetItem *item);
    // 新增：处理群组列表项点击
    void onGroupItemClicked(QListWidgetItem *item);
    // 新增：显示/隐藏群成员列表
    void toggleGroupMemberList();
    void createGroupChat();  // 点击“创建群聊”时调用
    void addFriendGroup();   // 点击“加好友/群”时调用
    void editFriendInfo(); // 好友编辑对话框槽函数
    void editGroupInfo();  // 群聊编辑对话框槽函数

private:
    // ========== 主体布局 ==========
    QSplitter   *mainSplitter;

    // ========== 左侧控件区域 ==========
    QWidget     *leftWidget;

    // 个人信息相关
    QWidget     *profileWidget;
    QWidget     *avatarContainer;
    QLabel      *avatarLabel;
    QLabel      *statusIndicator;
    QLabel      *onlineTextLabel;
    QLabel      *nameLabel;
    QLabel      *idLabel;
    QLabel      *signLabel;

    // 按钮相关
    QPushButton *settingsBtn;
    QPushButton *btnAdd;
    QPushButton *btnGroup;

    // 搜索、导航
    QLineEdit   *searchInput;
    QToolButton *btnMessage;
    QToolButton *btnContacts;
    QToolButton *btnGroups;
    // 新增：导航按钮组
    QButtonGroup *navButtonGroup;

    // ========== 左侧动态区域 ==========
    QStackedWidget *stackedListArea;
    // 消息页面（默认）
    QListWidget *messageList;
    // 好友页面
    QWidget *friendWidget;
    QPushButton *friendNotifyBtn;
    QFrame *friendSeparator;
    QListWidget *friendList;
    // 群组页面
    QWidget *groupWidget;
    QPushButton *groupNotifyBtn;
    QFrame *groupSeparator;
    QListWidget *groupList;
    // 搜索结果页面
    QWidget *searchWidget;
    QListWidget *searchFriendList;
    QFrame *searchFriendGroupSeparator;
    QListWidget *searchGroupList;
    QFrame *searchGroupChatSeparator;
    QListWidget *searchChatList;

    // ========== 右侧控件区域 ==========
    QWidget     *rightWidget;
    QStackedWidget *rightStackedWidget;  // 新增：右侧堆叠窗口

    // 空白页面
    QWidget     *emptyPage;
    QLabel      *emptyPageLabel;

    // 好友聊天页面
    QWidget     *friendChatPage;
    QWidget     *friendChatHeader;
    QLabel      *friendNameLabel;
    QPushButton *editFriendBtn;
    QListWidget *friendChatHistory;
    QWidget     *friendChatInputArea;
    QPushButton *friendEmojiBtn;
    QPushButton *friendFileBtn;
    QPushButton *friendImageBtn;
    QPushButton *friendShakeBtn;  // 新增：抖动按钮
    QTextEdit   *friendMessageInput;
    QPushButton *friendSendBtn;

    // 群聊页面
    QWidget     *groupChatPage;
    QSplitter   *groupChatSplitter;  // 新增：群聊分割器

    // 群聊左侧（聊天区）
    QWidget     *groupChatLeftArea;
    QWidget     *groupChatHeader;
    QLabel      *groupNameLabel;
    QPushButton *editGroupBtn;
    QListWidget *groupChatHistory;
    QWidget     *groupChatInputArea;
    QPushButton *groupEmojiBtn;
    QPushButton *groupFileBtn;
    QPushButton *groupImageBtn;
    QTextEdit   *groupMessageInput;
    QPushButton *groupSendBtn;

    // 群聊右侧（成员列表）
    QWidget     *groupMemberArea;
    QLabel      *memberCountLabel;
    QListWidget *groupMemberList;
    QPushButton *toggleMemberListBtn;  // 新增：切换成员列表显示的按钮
    bool        isMemberListVisible;   // 新增：成员列表是否可见

    // 在私有成员区添加
    // 好友通知页面
    QWidget     *friendRequestPage;
    QListWidget *friendRequestList;

    // 群组通知页面
    QWidget     *groupRequestPage;
    QListWidget *groupRequestList;

    // ========== 菜单 ==========
    QMenu       *settingsMenu;
    QAction *editAction;
    QAction *pwdAction ;
    QAction *logoutAction;

    // ========= 对话框 =========
    EditProfileDialog *editProfileDlg; // 编辑资料对话框
};

#endif // CHATMAINPAGE_H
