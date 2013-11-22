#ifndef SEAFILE_CLIENT_CLOUD_VIEW_H
#define SEAFILE_CLIENT_CLOUD_VIEW_H

#include <QWidget>
#include "account.h"
#include "ui_cloud-view.h"
class QPoint;
class QMenu;
class QTimer;
class QShowEvent;
class QHideEvent;
class QToolButton;
class QToolBar;

class ListReposRequest;
class GetEventsRequest;
class ServerRepo;
class RepoTreeView;
class RepoTreeModel;
class CloneTasksDialog;
class SeahubMessagesMonitor;
class CloneTasksDialog;
class ActivitiesView;
class ActivitiesModel;
class SeafileEvents;

class CloudView : public QWidget,
                  public Ui::CloudView
{
    Q_OBJECT
public:
    CloudView(QWidget *parent=0);
    const Account& currentAccount() { return current_account_; }

    CloneTasksDialog* cloneTasksDialog();

    QToolButton *seahubMessagesBtn() const { return mSeahubMessagesBtn; }

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
public slots:
    void showAddAccountDialog();
    void deleteAccount();
    void showCloneTasksDialog();

private slots:
    void refreshRepos();
    void refreshRepos(const std::vector<ServerRepo>& repos);
    void getEvents(const SeafileEvents& events);
    void refreshReposFailed();
    void getEventsFailed();
    void setCurrentAccount(const Account&account);
    void updateAccountMenu();
    void onAccountItemClicked();
    void refreshStatusBar();
    void showCreateRepoDialog();
    void showServerStatusDialog();
    void onRefreshClicked();

    void loadMoreActivities(int value);
private:
    Q_DISABLE_COPY(CloudView)

    void createLoadingView();
    void createRepoModelView();
    void createActivitiesView();
    void prepareAccountButtonMenu();
    void createToolBar();
    void updateAccountInfoDisplay();
    QAction *makeAccountAction(const Account& account);
    void showLoadingView();
    void showRepos();
    bool hasAccount();
    void refreshServerStatus();
    void refreshTasksInfo();
    void refreshTransferRate();

    bool in_refresh_;
    QTimer *refresh_timer_;

    QTimer *refresh_status_bar_timer_;

    RepoTreeModel *repos_model_;

    RepoTreeView *repos_tree_;
    QWidget *loading_view_;

    ListReposRequest *list_repo_req_;
    GetEventsRequest *get_events_req_;

    // Toolbar and actions
    QToolBar *tool_bar_;
    QAction *refresh_action_;
    QAction *create_repo_action_;

    // FolderDropArea *drop_area_;
    Account current_account_;

    // Account operations
    QAction *add_account_action_;
    QAction *delete_account_action_;
    QAction *switch_account_action_;
    QMenu *account_menu_;

    CloneTasksDialog* clone_task_dialog_;

    SeahubMessagesMonitor *seahub_messages_monitor_;

    ActivitiesView* activities_view_;
    ActivitiesModel* activities_model_;
};


#endif  // SEAFILE_CLIENT_CLOUD_VIEW_H
