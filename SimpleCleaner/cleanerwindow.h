#ifndef CLEANERWINDOW_H
#define CLEANERWINDOW_H

#include <QMainWindow>
#include "MultithreadTasks/taskqueue.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CleanerWindow; }
QT_END_NAMESPACE

class CleanerWindow;
class QProgressBar;

struct DeleteApplicationTask
{
    void operator()(QString);
};
struct DeleteDirTask
{
    void operator()(QString);
};

class CleanerWindow : public QMainWindow
{
    Q_OBJECT
public:
    CleanerWindow(QWidget *parent = nullptr);
    ~CleanerWindow();
private slots:
    void deleteApplication(QString);
private:
    Ui::CleanerWindow *ui;
    TaskQueue taskQueue;
};

#endif // CLEANERWINDOW_H
