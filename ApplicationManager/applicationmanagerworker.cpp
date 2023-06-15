#include "applicationmanagerworker.h"
#include "applicationinfoitem.h"
#include "registryquery.h"

ApplicationManagerWorker::ApplicationManagerWorker(const std::vector<AbstractInfoWidget*>& infoWidgetVector_, AbstractWorker* parent):
    AbstractWorker(parent), infoWidgetVector(infoWidgetVector_)
{
    connect(&thread, &QThread::started, this, &ApplicationManagerWorker::whileRun);
    connect(this, &ApplicationManagerWorker::finished, &thread, &QThread::quit);
    moveToThread(&thread);
    thread.start();
}

void ApplicationManagerWorker::work()
{
    if(infoWidgetVector.empty())
    {
        return;
    }
    std::vector<ApplicationInfoItem*> applicationsInfoVector = RegistryQuery().getApplicationsInfo();
    if(applicationsInfoVector.size() == infoWidgetVector.size())
    {
        return;
    }
    else if(applicationsInfoVector.size() > infoWidgetVector.size())
    {
        addNewApplicationWidget(infoWidgetVector, applicationsInfoVector);
    }
    else if(applicationsInfoVector.size() < infoWidgetVector.size())
    {
        deleteApplicationWidget(infoWidgetVector, applicationsInfoVector);
    }
    clear(applicationsInfoVector);
}

void ApplicationManagerWorker::addNewApplicationWidget(const std::vector<AbstractInfoWidget *>& infoWidgetVector,
                                                       const std::vector<ApplicationInfoItem*>& applicationsInfoVector)
{
    qDebug() <<"Add";
    int index = 0;
    int pos = findIndex(applicationsInfoVector, infoWidgetVector, [&applicationsInfoVector, &index]
        (auto&& widget) mutable
        {
            return widget->compareInfoItem(applicationsInfoVector[index]);;
        }, index);
    if(pos > -1)
    {
        emit sendNewApplicationInfo(pos, *applicationsInfoVector[pos]);
    }
}

void ApplicationManagerWorker::deleteApplicationWidget(const std::vector<AbstractInfoWidget *>& infoWidgetVector,
                                                       const std::vector<ApplicationInfoItem*>& applicationsInfoVector)
{
    qDebug() <<"Delete";
    int index = 0;
    int pos = findIndex(infoWidgetVector, applicationsInfoVector, [&infoWidgetVector, &index]
        (auto&& applicationInfo) mutable
        {
            return infoWidgetVector[index]->compareInfoItem(applicationInfo);;
        }, index);
    if(pos > -1)
    {
        emit sendDeletedApplicationWidget(infoWidgetVector[pos]);
    }
}

void ApplicationManagerWorker::clear(std::vector<ApplicationInfoItem*>& applicationsInfoVector)
{
    for(auto applicationInfo: applicationsInfoVector)
    {
        delete applicationInfo;
    }
}

