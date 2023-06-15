
#include "browserinfoitem.h"

BrowserInfoItem::BrowserInfoItem(const QString& name_,
                                 const QString& cachePath_,
                                 const QString& cookiesPath_,
                                 const QString& iconPath_):
    name(name_),
    cachePath(cachePath_),
    cookiesPath(cookiesPath_),
    iconPath(iconPath_)
{

}

bool BrowserInfoItem::operator==(const AbstractInfoItem* other) const
{
    const BrowserInfoItem* infoItem = dynamic_cast<const BrowserInfoItem*>(other);
    if(infoItem == nullptr)
        throw std::logic_error("Compare difference info item type");
    return infoItem->name == name && infoItem->cachePath == cachePath&&
           infoItem->cookiesPath == cookiesPath && infoItem->iconPath == iconPath;
}

bool BrowserInfoItem::operator!=(const AbstractInfoItem* other) const
{
    return !(*this == other);
}


bool BrowserInfoItem::isEmpty() const
{
    return name.isEmpty() && cachePath.isEmpty() &&
           cookiesPath.isEmpty() && iconPath.isEmpty();
}
