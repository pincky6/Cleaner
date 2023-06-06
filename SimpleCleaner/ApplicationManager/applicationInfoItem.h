#ifndef APPLICATIONINFOITEM_H
#define APPLICATIONINFOITEM_H
#include <QString>

struct ApplicationInfoItem
{
public:
    ApplicationInfoItem(const QString&, const QString&, const QString&,
                        const QString&, const QString&, const QString&);
    bool operator==(const ApplicationInfoItem&) const;
    bool operator!=(const ApplicationInfoItem&) const;
    bool isEmpty() const;
public:
    QString applicationIconPath_;
    QString applicationInstallPath_;
    QString applicationName_;
    QString applicationVersion_;
    QString applicationUninstallString_;
    QString applicationCompany_;
};
#endif //APPLICATIONINFOITEM_H
