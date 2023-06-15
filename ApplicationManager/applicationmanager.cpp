#include "applicationmanager.h"
#include "ui_abstractmanager.h"
#include "applicationinfowidget.h"
#include "applicationmanagerworker.h"
#include "registryquery.h"

#include <QVBoxLayout>

ApplicationManager::ApplicationManager(AbstractManager* parent):
    AbstractManager(parent)
{
    verticalLayout = new QVBoxLayout;
    worker = new ApplicationManagerWorker(infoWidgetVector);
    connect(ui->searchWidget, &SearchWidget::updateManager, worker, &AbstractWorker::run);
    connect(dynamic_cast<ApplicationManagerWorker*>(worker), &ApplicationManagerWorker::sendNewApplicationInfo,
            this, &ApplicationManager::addWidgetToScrollArea);
    connect(dynamic_cast<ApplicationManagerWorker*>(worker), &ApplicationManagerWorker::sendDeletedApplicationWidget,
            this, &ApplicationManager::deleteWidgetFromScrollArea);
}

void ApplicationManager::initInfoWidgets()
{
    std::vector<ApplicationInfoItem*> applicationsInfo = RegistryQuery().getApplicationsInfo();
    QStringList wordList;
    for(auto applicationInfo: applicationsInfo)
    {
        wordList << applicationInfo->name;
        ApplicationInfoWidget* applicationInfoWidget = new ApplicationInfoWidget(applicationInfo);
        connect(applicationInfoWidget, &ApplicationInfoWidget::sendUninstallString, this, &ApplicationManager::deleteButtonPressed);
        infoWidgetVector.push_back(applicationInfoWidget);
        verticalLayout->addWidget(applicationInfoWidget);
    }
    ui->searchWidget->setNewStringList(wordList);
    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
}

void ApplicationManager::addWidgetToScrollArea(const std::size_t position, ApplicationInfoItem infoItem)
{
    addStringToSearchWidget(infoItem.name);
    ApplicationInfoWidget* applicationInfoWidget = new ApplicationInfoWidget(new ApplicationInfoItem(std::move(infoItem)));
    verticalLayout->insertWidget(position, applicationInfoWidget);
    infoWidgetVector.push_back(applicationInfoWidget);
    ui->scrollAreaWidgetContents->updateGeometry();
}

void ApplicationManager::deleteWidgetFromScrollArea(AbstractInfoWidget* abstractInfoWidget)
{
    deleteStringFromSearchWidget(dynamic_cast<ApplicationInfoWidget*>(abstractInfoWidget)->getName());
    verticalLayout->removeWidget(abstractInfoWidget);
    infoWidgetVector.erase(std::remove(infoWidgetVector.begin(), infoWidgetVector.end(), abstractInfoWidget));
    delete abstractInfoWidget;
}


void ApplicationManager::deleteButtonPressed(QString uninstallString)
{
    emit sendUninstallString(uninstallString);
}


ApplicationManager::~ApplicationManager()
{
}
