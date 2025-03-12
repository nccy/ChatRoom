#ifndef ADDFRIENDGROUPDIALOG_H
#define ADDFRIENDGROUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QButtonGroup>

class AddFriendGroupDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddFriendGroupDialog(QWidget* parent = nullptr);

private slots:
    void onSearchTextChanged(const QString &text);
    void onFilterChanged();

private:
    QLineEdit *searchEdit;
    QPushButton *allButton;
    QPushButton *userButton;
    QPushButton *groupButton;
    QButtonGroup *filterGroup;
    QListWidget *resultList;
};

#endif // ADDFRIENDGROUPDIALOG_H
