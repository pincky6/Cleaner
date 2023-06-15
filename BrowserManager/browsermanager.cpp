#include "browsermanagerworker.h"
#include "ui_abstractmanager.h"
#include "browserinfowidget.h"
#include "browsermanager.h"
#include "registryquery.h"

#include <QVBoxLayout>

BrowserManager::BrowserManager(AbstractCheckableManager * parent):
    AbstractCheckableManager(parent)
{
    verticalLayout = new QVBoxLayout;
    worker = new BrowserManagerWorker(infoWidgetVector);
    connect(ui->searchWidget, &SearchWidget::updateManager, worker, &AbstractWorker::run);
    connect(dynamic_cast<BrowserManagerWorker*>(worker), &BrowserManagerWorker::sendNewApplicationInfo,
            this, &BrowserManager::addWidgetToScrollArea);
    connect(dynamic_cast<BrowserManagerWorker*>(worker), &BrowserManagerWorker::sendDeletedApplicationWidget,
            this, &BrowserManager::deleteWidgetFromScrollArea);
}

void BrowserManager::initInfoWidgets()
{
    auto browsersInfo = RegistryQuery().getBrowserInfo();
    QStringList wordList;
    for(auto&& browserInfo: browsersInfo)
    {
        BrowserInfoWidget* browserInfoWidget = new BrowserInfoWidget(browserInfo);
        wordList << browserInfo->name;
        verticalLayout->addWidget(browserInfoWidget);
        infoWidgetVector.push_back(browserInfoWidget);
    }
    ui->searchWidget->setNewStringList(wordList);
    ui->scrollAreaWidgetContents->setLayout(verticalLayout);
}

void BrowserManager::addWidgetToScrollArea(const std::size_t position, BrowserInfoItem infoItem)
{
    addStringToSearchWidget(infoItem.name);
    BrowserInfoWidget* browserInfoWidget = new BrowserInfoWidget(new BrowserInfoItem(std::move(infoItem)));
    verticalLayout->insertWidget(position, browserInfoWidget);
    infoWidgetVector.push_back(browserInfoWidget);
    ui->scrollAreaWidgetContents->updateGeometry();
}

void BrowserManager::deleteWidgetFromScrollArea(AbstractInfoWidget* abstractInfoWidget)
{
    deleteStringFromSearchWidget(dynamic_cast<BrowserInfoWidget*>(abstractInfoWidget)->getName());
    verticalLayout->removeWidget(abstractInfoWidget);
    infoWidgetVector.erase(std::remove(infoWidgetVector.begin(), infoWidgetVector.end(), abstractInfoWidget));
    delete abstractInfoWidget;
}


void BrowserManager::checkAll()
{
    for(auto infoWidget: infoWidgetVector)
    {
        dynamic_cast<BrowserInfoWidget*>(infoWidget)->setCacheCheckBox(true);
        dynamic_cast<BrowserInfoWidget*>(infoWidget)->setCookiesCheckBox(true);
    }
}

void BrowserManager::deleteChecked()
{
    for(auto infoWidget: infoWidgetVector)
    {
        BrowserInfoWidget* browserInfoWidget = dynamic_cast<BrowserInfoWidget*>(infoWidget);
        QString cache;
        QString cookies;
        if(browserInfoWidget->cacheCheckBoxChecked())
            cache = browserInfoWidget->getCachePath();
        if(browserInfoWidget->cookiesCheckBoxChecked())
            cookies = browserInfoWidget->getCookiesPath();
        emit sendBrowserMember(browserInfoWidget->getName(),
                               cache, cookies);
    }
}

