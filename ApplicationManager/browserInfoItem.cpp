#include "browserinfoitem.h"

BrowserInfoItem::BrowserInfoItem(const QString& browserName, const QString& browserIconPath,
                                 const QString& browserCookiePath, const QString& browserCachePath):
                        browserName_(browserName), browserIconPath_(browserIconPath),
                        browserCachePath_(browserCachePath), browserCookiePath_(browserCookiePath)
{}

