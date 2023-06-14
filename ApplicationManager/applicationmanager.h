
#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include "abstractmanager.h"
#include "applicationinfoitem.h"




class ApplicationManager : public AbstractManager
{
    Q_OBJECT
public:
    ApplicationManager(AbstractManager* parent = nullptr);
    void initInfoWidgets() override;
    ~ApplicationManager();
private slots:
    void addWidgetToScrollArea( const std::size_t, ApplicationInfoItem);
    void deleteWidgetFromScrollArea(AbstractInfoWidget*);
signals:
    void sendUninstallString(QString);
private slots:
    void deleteButtonPressed(QString);

};

#endif // APPLICATIONMANAGER_H
