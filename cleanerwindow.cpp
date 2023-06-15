#include "cleanerwindow.h"
#include "ui_cleanerwindow.h"


CleanerWindow::CleanerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CleanerWindow)
{
    ui->setupUi(this);
//    connect() для taskQueue
    ui->applicationManager->initInfoWidgets();
    ui->browserManager->initInfoWidgets();
}

CleanerWindow::~CleanerWindow()
{
    delete ui;
}

void CleanerWindow::on_applicationManagerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Managers::ApplicationManager);
}

void CleanerWindow::on_browserManagerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex((int)Managers::BrowserManager);
}

