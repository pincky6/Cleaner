#ifndef APPLICATIONINFOITEM_H
#define APPLICATIONINFOITEM_H

#include "abstractinfoitem.h"

#include <QString>

struct ApplicationInfoItem: public AbstractInfoItem
{
public:
    ApplicationInfoItem(const QString&, const QString&,
                        const QString&, const QString&,
                        const QString&);
//    ApplicationInfoItem(const ApplicationInfoItem&);
    bool operator==(const AbstractInfoItem*) const override;
    bool operator!=(const AbstractInfoItem*) const override;

    bool isEmpty() const override;
public:
    QString name;
    QString version;
    QString iconPath;
    QString creators;
    QString uninstallString;
};

#endif // APPLICATIONINFOITEM_H
