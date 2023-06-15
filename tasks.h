
#ifndef TASKS_H
#define TASKS_H

#include <QString>

struct DeleteApplicationTask
{
    void operator()(QString);
};
struct DeleteBrowserMemberTask
{
    void operator()(QString, QString, QString);
private:
    void defaultBrowserMemberDelete(const QString&, const QString&);
    void MozillaFirefoxMemberDelete(const QString&, const QString&);
    void deleteMember(const QString&);
};





#endif // TASKS_H
