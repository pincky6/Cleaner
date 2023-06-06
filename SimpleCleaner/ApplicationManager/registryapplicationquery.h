#ifndef REGISTRYAPPLICATIONQUERY_H
#define REGISTRYAPPLICATIONQUERY_H

#include <vector>
#include "applicationInfoItem.h"

class RegistryApplicationsQuery
{
    using ApplicationsInfoVector = std::vector<ApplicationInfoItem>;
public:
    RegistryApplicationsQuery();
    ApplicationsInfoVector getApplicationsInfo();
    bool registerApplicationInfoCheck(ApplicationInfoItem);
private:
    void registryApplicationQuery(const QString&, ApplicationsInfoVector&);
};

#endif // REGISTRYAPPLICATIONQUERY_H
