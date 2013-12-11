#ifndef SEAFILE_CLIENT_INIT_VDRIVE_DIALOG_H
#define SEAFILE_CLIENT_INIT_VDRIVE_DIALOG_H

#include <QDialog>
#include "ui_init-vdrive-dialog.h"
#include "account.h"
#include "api/requests.h"

class LocalRepo;
class QTimer;

class InitVirtualDriveDialog : public QDialog,
                               public Ui::InitVirtualDriveDialog
{
    Q_OBJECT
public:
    InitVirtualDriveDialog(const Account& account, QWidget *parent=0);

private slots:
    void onGetDefaultRepoSuccess(const QString& repo_id);
    void onGetDefaultRepoFailure(int code);
    void onDownloadRepoSuccess(const RepoDownloadInfo& info);
    void onDownloadRepoFailure(int code);
    void checkDownloadProgress();

private:
    Q_DISABLE_COPY(InitVirtualDriveDialog)

    void createLoadingView();
    void setStatusText(const QString& status);
    void setVDrive(const LocalRepo& repo);
    void fail(const QString& reason);
    void getDefaultRepo();

    GetDefaultRepoRequest *get_default_repo_req_;
    DownloadRepoRequest *download_default_repo_req_;

    QString default_repo_id_;
    RepoDownloadInfo default_repo_info_;

    Account account_;

    QTimer *check_download_timer_;
};

#endif // SEAFILE_CLIENT_INIT_VDRIVE_DIALOG_H
