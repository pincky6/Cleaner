#include "applicationInfoItem.h"

ApplicationInfoItem::ApplicationInfoItem(const QString& applicationIconPath, const QString& applicationInstallPath,
                                         const QString& applicationName, const QString& applicationVersion,
                                         const QString& applicationUninstallString, const QString& applicationCompany):
                                applicationIconPath_(applicationIconPath), applicationInstallPath_(applicationInstallPath),
                                applicationName_(applicationName), applicationVersion_(applicationVersion),
                                applicationUninstallString_(applicationUninstallString), applicationCompany_(applicationCompany)
{}

bool ApplicationInfoItem::operator==(const ApplicationInfoItem& other) const
{
    return applicationIconPath_ == other.applicationIconPath_ && applicationInstallPath_ == other.applicationInstallPath_  &&
           applicationName_ == other.applicationName_ && applicationVersion_ == other.applicationVersion_ &&
           applicationUninstallString_ == other.applicationUninstallString_ && applicationCompany_ == other.applicationCompany_;
}

bool ApplicationInfoItem::operator!=(const ApplicationInfoItem& other) const
{
    return !(*this == other);
}

bool ApplicationInfoItem::isEmpty() const
{
    return applicationIconPath_.isEmpty() && applicationName_.isEmpty()
            && applicationVersion_.isEmpty() && applicationCompany_.isEmpty() &&
            (applicationUninstallString_.isEmpty() && applicationInstallPath_.isEmpty());
}
