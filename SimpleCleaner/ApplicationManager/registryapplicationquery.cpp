#include "registryapplicationquery.h"
#include <QDebug>
#include <QSettings>
#include <algorithm>
#include <iterator>

RegistryApplicationsQuery::RegistryApplicationsQuery()
{}

std::vector<ApplicationInfoItem> RegistryApplicationsQuery::getApplicationsInfo()
{
    ApplicationsInfoVector ApplicationsInfo;
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", ApplicationsInfo);
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall", ApplicationsInfo);
    registryApplicationQuery("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", ApplicationsInfo);
    qDebug() << std::count_if(ApplicationsInfo.begin(), ApplicationsInfo.end(), [](auto&& tmp){return tmp.applicationUninstallString_.isEmpty();});
    qDebug() << ApplicationsInfo.size();
    return ApplicationsInfo;
}

void RegistryApplicationsQuery::registryApplicationQuery(const QString& queryPath, std::vector<ApplicationInfoItem>& applicationsVector)
{
    QSettings query(queryPath, QSettings::NativeFormat);
    QStringList applicationsList = query.childGroups();
    QString applicationIconPath;
    QString applicationInstallPath;
    QString applicationName;
    QString applicationVersion;
    QString applicationUninstallString;
    QString applicationCompany;
    for(auto&& application: applicationsList)
    {
        query.beginGroup(application);
        applicationIconPath = query.value("DisplayIcon").toString();
        qsizetype pos = applicationIconPath.indexOf(".exe");
        if(pos != -1)
        {
            applicationIconPath.remove(pos + 4, applicationIconPath.length() - pos);
        }
        applicationInstallPath = query.value("InstallLocation").toString();
        applicationName = query.value("DisplayName").toString();
        applicationVersion = query.value("DisplayVersion").toString();
        applicationUninstallString = query.value("UninstallString").toString();
        applicationCompany = query.value("Publisher").toString();
        ApplicationInfoItem item(applicationIconPath, applicationInstallPath, applicationName,
                                 applicationVersion, applicationUninstallString, applicationCompany);
        if(!item.applicationUninstallString_.contains("MsiExec.exe") && !item.isEmpty() && !applicationUninstallString.isEmpty())
        {
            applicationsVector.push_back(item);
        }
        query.endGroup();
    }
}
