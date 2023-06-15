#ifndef BROWSERINFOITEM_H
#define BROWSERINFOITEM_H

#include "abstractinfoitem.h"

#include <QString>

class BrowserInfoItem: public AbstractInfoItem
{
public:
    BrowserInfoItem(const QString&, const QString&,
                    const QString&, const QString&);

    bool operator==(const AbstractInfoItem*) const override;
    bool operator!=(const AbstractInfoItem*) const override;

    bool isEmpty() const override;
public:
    QString name;
    QString cachePath;
    QString cookiesPath;
    QString iconPath;
};

#endif // BROWSERINFOITEM_H
