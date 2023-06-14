
#ifndef REGISTRYQUERY_H
#define REGISTRYQUERY_H

#include <QString>
#include <vector>
#include <map>

class ApplicationInfoItem;
class BrowserInfoItem;

class RegistryQuery
{
public:
    std::vector<ApplicationInfoItem*> getApplicationsInfo();
    std::vector<BrowserInfoItem*> getBrowserInfo();
private:
    void registryApplicationQuery(const QString&, std::vector<ApplicationInfoItem*>&);

    std::vector<BrowserInfoItem*> getBrowsersPath();
    std::map<QString, QString> getBrowserIconPath();
};

#endif // REGISTRYQUERY_H
