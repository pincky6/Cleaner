#include "applicationinfoitem.h"



ApplicationInfoItem::ApplicationInfoItem(const QString& applicationName_, const QString& applicationVersion_,
                                         const QString& applicationIconPath_, const QString& applicationCreators_,
                                         const QString& applicationUninstallString_):
    applicationName(applicationName_), applicationVersion(applicationVersion_),
    applicationIconPath(applicationIconPath_), applicationCreators(applicationCreators_),
    applicationUninstallString(applicationUninstallString_)

{}

bool ApplicationInfoItem::operator==(const AbstractInfoItem* other) const
{
    const ApplicationInfoItem* infoItem = dynamic_cast<const ApplicationInfoItem*>(other);
    if(infoItem == nullptr)
        throw std::logic_error("Compare difference info item type");
    return infoItem->applicationName == applicationName && infoItem->applicationCreators == applicationCreators &&
           infoItem->applicationVersion == applicationVersion && infoItem->applicationUninstallString == applicationUninstallString &&
           infoItem->applicationIconPath == applicationIconPath;
}

bool ApplicationInfoItem::operator!=(const AbstractInfoItem* other) const
{
    return !(*this == other);
}

bool ApplicationInfoItem::isEmpty() const
{
    return applicationName.isEmpty() && applicationCreators.isEmpty() &&
           applicationVersion.isEmpty() && applicationUninstallString.isEmpty() &&
             applicationIconPath.isEmpty();
}

