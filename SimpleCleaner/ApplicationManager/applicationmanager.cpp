#include "applicationmanager.h"
#include "registryapplicationquery.h"
#include "applicationinfowidget.h"
#include "ui_applicationmanager.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QStringList>

ApplicationManager::ApplicationManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationManager)
{
    ui->setupUi(this);
    verticalBox = new QVBoxLayout();
    ApplicationsInfoVector applicationsInfoVector = RegistryApplicationsQuery().getApplicationsInfo();
    for(auto&& applicationInfo: applicationsInfoVector)
    {
        ApplicationInfoWidget* applicationInfoWidget = new ApplicationInfoWidget(applicationInfo);
        applicationWidgetVector.push_back(applicationInfoWidget);
        verticalBox->addWidget(applicationInfoWidget);
        wordList << applicationInfo.applicationName_;
        QObject::connect(applicationInfoWidget, &ApplicationInfoWidget::deleteButtonPressedSignal,
                         this, &ApplicationManager::sendUninstallStringSlot);
    }
    ui->scrollAreaWidgetContents->setLayout(verticalBox);
    ui->searchWidget->setCompleterWords(wordList);
    connect(ui->searchWidget, &SearchWidget::sendSearchedString, this, &ApplicationManager::findSearchedString);

    managerCleaner = new ManagerCleaner;
    clearThread = new QThread(this);
    managerCleaner->moveToThread(clearThread);
    connect(clearThread, &QThread::started, managerCleaner, [this](){
        managerCleaner->checkManagerWidgetList(applicationWidgetVector);
    });
    connect(clearThread, &QThread::finished, clearThread, &QThread::deleteLater);
    connect(managerCleaner, &ManagerCleaner::destroyed, clearThread, &QThread::quit);
    connect(managerCleaner, &ManagerCleaner::destroyed, managerCleaner, &ManagerCleaner::deleteLater);
    connect(clearThread, &QThread::finished, clearThread, &QThread::deleteLater);
    clearThread->start();

    connect(managerCleaner, &ManagerCleaner::sendNewApplicationInfo, this, &ApplicationManager::getApplicationWidgetInfo);
    connect(managerCleaner, &ManagerCleaner::sendDeleteApplicationWidget, this, &ApplicationManager::getDeleteApplicationWidget);

}

void ApplicationManager::addApplicationInfoWidget(ApplicationInfoWidget * newApplicationInfoWidget, const std::size_t i)
{
    verticalBox->insertWidget(i, newApplicationInfoWidget);
    ui->scrollAreaWidgetContents->updateGeometry();
}

void ApplicationManager::deleteApplicationInfoWidget(ApplicationInfoWidget * applicationInfoWidget)
{


    verticalBox->removeWidget(applicationInfoWidget);
    applicationWidgetVector.erase(std::remove(applicationWidgetVector.begin(), applicationWidgetVector.end(), applicationInfoWidget));
    delete applicationInfoWidget;
}

void ApplicationManager::addNewApplicationNameIntoWordList(const QString& newApplication)
{
    wordList << newApplication;
    ui->searchWidget->setCompleterWords(wordList);
}

void ApplicationManager::deleteApplicationNameFromWordList(const QString &applicationName)
{
    wordList.removeOne(applicationName);
    ui->searchWidget->setCompleterWords(wordList);
}


ApplicationManager::~ApplicationManager()
{
    managerCleaner->stop();
    clearThread->wait(10000);
    clearThread->quit();
    delete managerCleaner;
    delete clearThread;
    delete ui;
}

void ApplicationManager::findSearchedString(QString searchedString)
{
    qDebug() << searchedString;
    for (auto applicationInfoWidget : ui->scrollArea->findChildren<ApplicationInfoWidget*>())
    {
        if (applicationInfoWidget->getApplicationInfo().contains(searchedString))
        {
            ui->scrollArea->ensureWidgetVisible(applicationInfoWidget, 0, 0);
            break;
        }
    }
}

void ApplicationManager::sendUninstallStringSlot(QString uninstallString)
{
    emit sendUninstallString(uninstallString);
}

void ApplicationManager::getApplicationWidgetInfo(ApplicationInfoItem applicationInfoItem, const std::size_t i)
{
    ApplicationInfoWidget* applicationInfoWidget = new ApplicationInfoWidget(applicationInfoItem);
    applicationWidgetVector.push_back(applicationInfoWidget);
    addApplicationInfoWidget(applicationInfoWidget, i);
    addNewApplicationNameIntoWordList(applicationInfoWidget->getApplicationName());
    QObject::connect(applicationInfoWidget, &ApplicationInfoWidget::deleteButtonPressedSignal,
                     this, &ApplicationManager::sendUninstallStringSlot);
}

void ApplicationManager::getDeleteApplicationWidget(ApplicationInfoItem applicationInfoWidget)
{
    auto it = std::find_if(applicationWidgetVector.begin(), applicationWidgetVector.end(),
                           [&applicationInfoWidget](auto&& widget){return widget->compareApplicationInfo(applicationInfoWidget);});
    deleteApplicationNameFromWordList((*it)->getApplicationName());
    deleteApplicationInfoWidget(*it);
}


void ManagerCleaner::stop()
{
    work = false;

}

void ManagerCleaner::checkManagerWidgetList(std::vector<ApplicationInfoWidget *> &applicationsWidgetVector)
{
    if(applicationsWidgetVector.empty())
    {
        QThread::currentThread()->sleep(5);
    }
    while(work)
    {
        std::vector<ApplicationInfoItem> applicationsInfoVector = RegistryApplicationsQuery().getApplicationsInfo();
        if(applicationsInfoVector.size() == applicationsWidgetVector.size())
        {
            QThread::currentThread()->sleep(5);
        }
        else if(applicationsInfoVector.size() > applicationsWidgetVector.size())
        {
            addNewApplicationWidget(applicationsWidgetVector, applicationsInfoVector);
        }
        else
        {
            deleteApplicationWidget(applicationsWidgetVector, applicationsInfoVector);
        }
        QThread::currentThread()->sleep(5);
    }
}

void ManagerCleaner::addNewApplicationWidget(std::vector<ApplicationInfoWidget *>& applicationsWidgetVector,
                                             const std::vector<ApplicationInfoItem>& applicationsInfoVector)
{
    for(std::size_t i = 0; i < applicationsInfoVector.size(); i++)
    {
        auto it = std::find_if(applicationsWidgetVector.begin(), applicationsWidgetVector.end(),
                     [&applicationsInfoVector, &i](auto&& widget){return widget->compareApplicationInfo(applicationsInfoVector[i]);});
        if(it != applicationsWidgetVector.end())
            continue;
        emit sendNewApplicationInfo(applicationsInfoVector[i], i);
        break;
    }
}

void ManagerCleaner::deleteApplicationWidget(std::vector<ApplicationInfoWidget *>& applicationsWidgetVector,
                                             const std::vector<ApplicationInfoItem>& applicationsInfoVector)
{
    for(std::size_t i = 0; i < applicationsWidgetVector.size(); i++)
    {
        auto it = std::find_if(applicationsInfoVector.begin(), applicationsInfoVector.end(),
                               [&applicationsWidgetVector, &i](auto&& applicationInfo)
                               {return applicationsWidgetVector[i]->compareApplicationInfo(applicationInfo);});
        if(it != applicationsInfoVector.end())
            continue;
        emit sendDeleteApplicationWidget(applicationsWidgetVector[i]->getApplicationInfoItem());
        break;
    }
}
