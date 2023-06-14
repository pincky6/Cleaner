#include "registryquery.h"

#include "ApplicationManager/applicationinfoitem.h"

#include <QSettings>

std::vector<ApplicationInfoItem*> RegistryQuery::getApplicationsInfo()
{
    std::vector<ApplicationInfoItem*> applicationsInfo;
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    registryApplicationQuery("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    return applicationsInfo;
}

void RegistryQuery::registryApplicationQuery(const QString& queryPath, std::vector<ApplicationInfoItem*>& applicationsInfo)
{
    QSettings query(queryPath, QSettings::NativeFormat);
    QStringList applicationsList = query.childGroups();
    QString applicationName;
    QString applicationVersion;
    QString applicationIconPath;
    QString applicationCreators;
    QString applicationUninstallString;
    int offset = 4;
    for(auto&& application: applicationsList)
    {
        query.beginGroup(application);
        applicationName = query.value("DisplayName").toString();
        applicationIconPath = query.value("DisplayIcon").toString();
        qsizetype pos = applicationIconPath.indexOf(".exe");
        if(pos != -1)
        {
            applicationIconPath.remove(pos + offset, applicationIconPath.length() - pos);
        }

        applicationVersion = query.value("DisplayVersion").toString();
        applicationUninstallString = query.value("UninstallString").toString();
        applicationUninstallString.replace("/uninstall", "--uninstall");

        applicationCreators = query.value("Publisher").toString();
        ApplicationInfoItem* item = new ApplicationInfoItem(applicationName, applicationVersion,
                                                            applicationIconPath, applicationCreators,
                                                            applicationUninstallString);
        if(!applicationUninstallString.contains("MsiExec.exe") && !applicationName.isEmpty() && !applicationUninstallString.isEmpty())
        {
            applicationsInfo.push_back(item);
        }
        query.endGroup();
    }
}
