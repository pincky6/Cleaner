#include "browsermanagerworker.h"
#include "browserinfoitem.h"
#include "registryquery.h"

BrowserManagerWorker::BrowserManagerWorker(const std::vector<AbstractInfoWidget*>& infoWidgetVector_, AbstractWorker* parent):
    AbstractWorker(parent), infoWidgetVector(infoWidgetVector_)
{
    connect(&thread, &QThread::started, this, &BrowserManagerWorker::whileRun);
    connect(this, &BrowserManagerWorker::finished, &thread, &QThread::quit);
    moveToThread(&thread);
    thread.start();
}

void BrowserManagerWorker::work()
{
    if(infoWidgetVector.empty())
    {
        return;
    }
    std::vector<BrowserInfoItem*> browserInfoVector = RegistryQuery().getBrowserInfo();
    if(browserInfoVector.size() == infoWidgetVector.size())
    {
        return;
    }
    else if(browserInfoVector.size() > infoWidgetVector.size())
    {
        addNewApplicationWidget(infoWidgetVector, browserInfoVector);
    }
    else if(browserInfoVector.size() < infoWidgetVector.size())
    {
        deleteApplicationWidget(infoWidgetVector, browserInfoVector);
    }
    clear(browserInfoVector);
}

void BrowserManagerWorker::addNewApplicationWidget(const std::vector<AbstractInfoWidget *>& infoWidgetVector,
                                                       const std::vector<BrowserInfoItem*>& browsersInfoVector)
{
    qDebug() <<"Add";
    int index = 0;
    int pos = findIndex(browsersInfoVector, infoWidgetVector, [&browsersInfoVector, &index]
        (auto&& widget) mutable
        {
            return widget->compareInfoItem(browsersInfoVector[index]);;
        }, index);
    if(pos > -1)
    {
        emit sendNewApplicationInfo(pos, *browsersInfoVector[pos]);
    }
}

void BrowserManagerWorker::deleteApplicationWidget(const std::vector<AbstractInfoWidget *>& infoWidgetVector,
                                                       const std::vector<BrowserInfoItem*>& browsersInfoVector)
{
    qDebug() <<"Delete";
    int index = 0;
    int pos = findIndex(infoWidgetVector, browsersInfoVector, [&infoWidgetVector, &index]
        (auto&& applicationInfo) mutable
        {
            return infoWidgetVector[index]->compareInfoItem(applicationInfo);;
        }, index);
    if(pos > -1)
    {
        emit sendDeletedApplicationWidget(infoWidgetVector[pos]);
    }
}

void BrowserManagerWorker::clear(std::vector<BrowserInfoItem*>& browsersInfoVector)
{
    for(auto browserInfo: browsersInfoVector)
    {
        delete browserInfo;
    }
}

