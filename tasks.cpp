#include "tasks.h"

#include <QDir>
#include <QProcess>
#include <QFileInfo>
#include <QStringList>

void DeleteApplicationTask::operator()(QString uninstallString)
{
    if(!uninstallString.isEmpty())
    {
        QProcess process;
        process.startDetached(uninstallString);
        return;
    }
}

void DeleteBrowserMemberTask::operator()(QString browserName,
                                         QString deleteCachePath, QString deleteCookiesPath)
{
    if(browserName == "Mozilla Firefox")
    {
        MozillaFirefoxMemberDelete(deleteCachePath, deleteCookiesPath);
    }
    else
    {
        defaultBrowserMemberDelete(deleteCachePath, deleteCookiesPath);
    }
}

void DeleteBrowserMemberTask::defaultBrowserMemberDelete(const QString & deleteCachePath,
                                                         const QString &deleteCookiesPath)
{
    deleteMember(deleteCachePath);
    deleteMember(deleteCookiesPath);
}

void DeleteBrowserMemberTask::MozillaFirefoxMemberDelete(const QString &deleteCachePath,
                                                         const QString &deleteCookiesPath)
{
    QDir cacheDir(deleteCachePath), cookiesDir(deleteCookiesPath);
    QStringList cacheSubdirs = cacheDir.entryList(QDir::Dirs), cookiesSubdirs = cookiesDir.entryList(QDir::Dirs);
    for(auto&& subdir: cacheSubdirs)
    {
        deleteMember(deleteCachePath + "\\" + subdir + "\\cache2");
    }
    for(auto&& subdir: cookiesSubdirs)
    {
        deleteMember(deleteCookiesPath + "\\" + subdir + "\\cookies.sqlite");
    }

}

void DeleteBrowserMemberTask::deleteMember(const QString& deletePath)
{
    QFileInfo fileInfo(deletePath);
    if(fileInfo.exists(deletePath) && fileInfo.isFile())
    {
        QFile file(deletePath);
        file.remove();
    }
    if(fileInfo.exists(deletePath) && fileInfo.isDir())
    {
        QDir dir(deletePath);
        dir.removeRecursively();
    }
}

