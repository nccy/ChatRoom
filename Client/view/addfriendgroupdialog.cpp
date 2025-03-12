#include "addfriendgroupdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

AddFriendGroupDialog::AddFriendGroupDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("添加好友/群");
    setFixedSize(400, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 1. 搜索栏
    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("请输入搜索关键词");
    mainLayout->addWidget(searchEdit);
    connect(searchEdit, &QLineEdit::textChanged, this, &AddFriendGroupDialog::onSearchTextChanged);

    // 2. 选项区域：全部、用户、群组（互斥按钮）
    QHBoxLayout *filterLayout = new QHBoxLayout;
    allButton = new QPushButton("全部");
    userButton = new QPushButton("用户");
    groupButton = new QPushButton("群组");

    // 设置按钮为可切换状态
    allButton->setCheckable(true);
    userButton->setCheckable(true);
    groupButton->setCheckable(true);
    allButton->setChecked(true); // 默认选中全部

    filterGroup = new QButtonGroup(this);
    filterGroup->addButton(allButton, 0);
    filterGroup->addButton(userButton, 1);
    filterGroup->addButton(groupButton, 2);
    filterGroup->setExclusive(true);

    filterLayout->addWidget(allButton);
    filterLayout->addWidget(userButton);
    filterLayout->addWidget(groupButton);
    mainLayout->addLayout(filterLayout);
    connect(filterGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &AddFriendGroupDialog::onFilterChanged);

    // 3. 搜索结果列表
    resultList = new QListWidget;
    mainLayout->addWidget(resultList);

    // 初始时可以显示提示信息
    resultList->addItem("请输入关键词进行搜索");
}

void AddFriendGroupDialog::onSearchTextChanged(const QString &text)
{
    // 此处为简单示例，根据搜索关键词更新列表
    resultList->clear();
    if (text.isEmpty()) {
        resultList->addItem("请输入关键词进行搜索");
    } else {
        // 模拟搜索结果（实际应调用搜索接口或过滤数据）
        resultList->addItem("搜索结果: " + text + " - 项目 1");
        resultList->addItem("搜索结果: " + text + " - 项目 2");
        resultList->addItem("搜索结果: " + text + " - 项目 3");
    }
}

void AddFriendGroupDialog::onFilterChanged()
{
    // 根据选中的过滤选项调整搜索结果（示例中简单输出当前过滤）
    int id = filterGroup->checkedId();
    QString filter;
    switch (id) {
    case 0:
        filter = "全部";
        break;
    case 1:
        filter = "用户";
        break;
    case 2:
        filter = "群组";
        break;
    }
    // 更新列表显示当前过滤状态（实际开发中，可结合搜索关键词更新结果）
    resultList->clear();
    resultList->addItem("当前过滤: " + filter);
}
