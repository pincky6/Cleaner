
#ifndef BROWSERMANAGER_H
#define BROWSERMANAGER_H

#include "abstractcheckablemanager.h"
#include "browserinfoitem.h"
#include <QString>

class QVBoxLayout;

class BrowserManager : public AbstractCheckableManager
{
    Q_OBJECT
public:
    BrowserManager(AbstractCheckableManager * parent = nullptr);
    void initInfoWidgets() override;
    void checkAll() override;
    void deleteChecked() override;
signals:
    void sendBrowserMembers(QString, QString, QString);
private slots:
    void addWidgetToScrollArea( const std::size_t, BrowserInfoItem);
    void deleteWidgetFromScrollArea(AbstractInfoWidget*);
private:
    QVBoxLayout* verticalLayout;
};

#endif // BROWSERMANAGER_H
