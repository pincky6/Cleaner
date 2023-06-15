#ifndef CLEANERWINDOW_H
#define CLEANERWINDOW_H

#include "MultithreadTask/taskqueue.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CleanerWindow; }
QT_END_NAMESPACE

enum class Managers
{
    ApplicationManager = 0,
    BrowserManager
};

class CleanerWindow : public QMainWindow
{
    Q_OBJECT
public:
    CleanerWindow(QWidget *parent = nullptr);
    ~CleanerWindow();
private slots:
    void deleteApplication(QString);
    void deletePath(QString, QString, QString);

    void on_applicationManagerButton_clicked();
    void on_browserManagerButton_clicked();
private:
    Ui::CleanerWindow *ui;
    TaskQueue taskQueue;
};

#endif // CLEANERWINDOW_H
