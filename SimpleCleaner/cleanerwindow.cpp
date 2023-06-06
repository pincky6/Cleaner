#include "cleanerwindow.h"
#include "ui_cleanerwindow.h"
#include "ApplicationManager/applicationmanager.h"
#include <QDir>
#include <QProcess>

void DeleteApplicationTask::operator()(QString uninstallString)
{
    if(!uninstallString.isEmpty())
    {
        QProcess process;
        process.startDetached(uninstallString);
        return;
    }
}

void DeleteDirTask::operator()(QString dirPath)
{
    QDir(dirPath).removeRecursively();
}

CleanerWindow::CleanerWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::CleanerWindow),
    taskQueue(4)
{
    ui->setupUi(this);
    QObject::connect(ui->applicationManager, &ApplicationManager::sendUninstallString, this, &CleanerWindow::deleteApplication);
}


CleanerWindow::~CleanerWindow()
{
    taskQueue.stop();

    delete ui;
}


void CleanerWindow::deleteApplication(QString uninstallString)
{
    taskQueue.push(new Task(&DeleteApplicationTask::operator(), DeleteApplicationTask(),
                            uninstallString));
}


