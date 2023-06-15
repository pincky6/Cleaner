#include "browsermanager.h"
#include "browserinfowidget.h"
#include "registryquery.h"
#include "ui_abstractmanager.h"

#include <QVBoxLayout>

BrowserManager::BrowserManager(AbstractCheckableManager * parent):
    AbstractCheckableManager(parent)
{
    verticalLayout = new QVBoxLayout;
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

