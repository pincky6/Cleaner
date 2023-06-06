#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QWidget>
#include <QThread>
#include <vector>
#include <QVBoxLayout>
#include "applicationInfoItem.h"

namespace Ui {
class ApplicationManager;
}
class ApplicationManager;

class ApplicationInfoWidget;

class ManagerCleaner:public QObject
{
    Q_OBJECT
public:
    ManagerCleaner(QObject* parent = nullptr): QObject(parent), work(true){}
    void stop();
public slots:
    void checkManagerWidgetList(std::vector<ApplicationInfoWidget*>&);
signals:
    void sendNewApplicationInfo(ApplicationInfoItem, const std::size_t);
     void sendDeleteApplicationWidget(ApplicationInfoItem);
private:
    void addNewApplicationWidget(std::vector<ApplicationInfoWidget*>&,  const std::vector<ApplicationInfoItem>&);
    void deleteApplicationWidget(std::vector<ApplicationInfoWidget*>&,  const std::vector<ApplicationInfoItem>&);
private:
    bool work;
};

class ApplicationManager : public QWidget
{
    Q_OBJECT
using ApplicationsInfoVector = std::vector<ApplicationInfoItem>;
public:
explicit ApplicationManager(QWidget *parent = nullptr);
    void addApplicationInfoWidget(ApplicationInfoWidget*, const std::size_t);
    void deleteApplicationInfoWidget(ApplicationInfoWidget*);

    void addNewApplicationNameIntoWordList(const QString&);
    void deleteApplicationNameFromWordList(const QString&);
    ~ApplicationManager();
signals:
    void sendUninstallString(QString);
public slots:
    void findSearchedString(QString);
    void sendUninstallStringSlot(QString);
    void getApplicationWidgetInfo(ApplicationInfoItem, const std::size_t);
    void getDeleteApplicationWidget(ApplicationInfoItem);
private:
    std::vector<ApplicationInfoWidget*> applicationWidgetVector;
    ManagerCleaner* managerCleaner;
    Ui::ApplicationManager *ui;
    QThread* clearThread;
    QVBoxLayout* verticalBox;
    QStringList wordList;
};

#endif // APPLICATIONMANAGER_H
