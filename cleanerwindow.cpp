#include "cleanerwindow.h"
#include "ui_cleanerwindow.h"
#include "tasks.h"

CleanerWindow::CleanerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CleanerWindow),
    taskQueue(4)
{
    ui->setupUi(this);
//    connect() для taskQueue
    connect(ui->applicationManager, &ApplicationManager::sendUninstallString, this, &CleanerWindow::deleteApplication);
    connect(ui->browserManager, &BrowserManager::sendBrowserMembers, this, &CleanerWindow::deletePath);
    ui->applicationManager->initInfoWidgets();
    ui->browserManager->initInfoWidgets();
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

void CleanerWindow::deletePath(QString browserName, QString deleteCachePath, QString deleteCookiesPath)
{
    taskQueue.push(new Task(&DeleteBrowserMemberTask::operator(), DeleteBrowserMemberTask(),
                            browserName, deleteCachePath, deleteCookiesPath));
}

void CleanerWindow::on_applicationManagerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Managers::ApplicationManager);
}

void CleanerWindow::on_browserManagerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Managers::BrowserManager);
}

