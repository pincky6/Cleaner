#include "applicationinfoitem.h"



ApplicationInfoItem::ApplicationInfoItem(const QString& name_, const QString& version_,
                                         const QString& iconPath_, const QString& creators_,
                                         const QString& uninstallString_):
    name(name_), version(version_),
    iconPath(iconPath_), creators(creators_),
    uninstallString(uninstallString_)

{}

bool ApplicationInfoItem::operator==(const AbstractInfoItem* other) const
{
    const ApplicationInfoItem* infoItem = dynamic_cast<const ApplicationInfoItem*>(other);
    if(infoItem == nullptr)
        throw std::logic_error("Compare difference info item type");
    return infoItem->name == name && infoItem->creators == creators &&
           infoItem->version == version && infoItem->uninstallString == uninstallString &&
           infoItem->iconPath == iconPath;
}

bool ApplicationInfoItem::operator!=(const AbstractInfoItem* other) const
{
    return !(*this == other);
}


bool ApplicationInfoItem::isEmpty() const
{
    return name.isEmpty() && creators.isEmpty() &&
           version.isEmpty() && uninstallString.isEmpty() &&
             iconPath.isEmpty();
}

