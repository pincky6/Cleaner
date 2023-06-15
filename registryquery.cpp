#include "registryquery.h"

#include "ApplicationManager/applicationinfoitem.h"
#include "BrowserManager/browserinfoitem.h"

#include <QRegularExpression>
#include <QStandardPaths>
#include <QSettings>
#include <QFile>

std::vector<ApplicationInfoItem*> RegistryQuery::getApplicationsInfo()
{
    std::vector<ApplicationInfoItem*> applicationsInfo;
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    registryApplicationQuery("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    registryApplicationQuery("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", applicationsInfo);
    return applicationsInfo;
}

std::vector<BrowserInfoItem *> RegistryQuery::getBrowserInfo()
{
    QFile file(":/browserPaths");
    if(!file.exists())
    {
        abort();
    }
    file.open(QIODevice::ReadOnly);
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString windowsUserName = homePath[0].split("/").last();
    QRegularExpression regExpr("\r\n|,");
    QStringList browsersInfo = QString::fromStdString(file.readAll().toStdString()).split(regExpr);
    std::map<QString, QString> browsersIconPath = getBrowserIconPath();
    std::vector<BrowserInfoItem*> browserInfoItemVector;
    for(int i = 0; i < browsersInfo.size() - 1; i += 3)
    {
        QString cachePath = browsersInfo[i + 1].arg(windowsUserName);
        QString cookiesPath = browsersInfo[i + 2].arg(windowsUserName);
        if(browsersIconPath.find(browsersInfo[i]) != browsersIconPath.end())
        {
            browserInfoItemVector.push_back(new BrowserInfoItem(browsersInfo[i],
                                                                cachePath, cookiesPath,
                                                                browsersIconPath[browsersInfo[i]]));
        }
    }
    return browserInfoItemVector;
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
        if(!applicationUninstallString.contains("MsiExec.exe") && !applicationName.isEmpty() && !applicationUninstallString.isEmpty())
        {
            applicationsInfo.push_back(new ApplicationInfoItem(applicationName, applicationVersion,
                                                               applicationIconPath, applicationCreators,
                                                               applicationUninstallString));
        }
        query.endGroup();
    }
}

std::map<QString, QString> RegistryQuery::getBrowserIconPath()
{
    QString registerBrowserPath = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Clients\\StartMenuInternet";
    QSettings query(registerBrowserPath, QSettings::NativeFormat);
    std::map<QString, QString> browsersIconPath;
    auto installedBrowsers = query.childGroups();
    int offset = 4;
    for(auto&& installedBrowser: installedBrowsers)
    {
        query.beginGroup(installedBrowser);
        QSettings browserNameQuery(registerBrowserPath + "\\" + installedBrowser, QSettings::NativeFormat);
        auto browserChildGroups = browserNameQuery.childGroups();
        if(!browserChildGroups.contains("DefaultIcon"))
        {
            continue;
        }
        browserNameQuery.beginGroup("DefaultIcon");
        QString iconPath = browserNameQuery.value(".").toString();
        qsizetype pos = iconPath.indexOf(".exe");
        if(pos != -1)
        {
            iconPath.remove(pos + offset, iconPath.length() - pos);
        }

        browsersIconPath[query.value(".").toString()] = iconPath;
        browserNameQuery.endGroup();
        query.endGroup();
    }
    return browsersIconPath;
}
