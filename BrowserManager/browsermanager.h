
#ifndef BROWSERMANAGER_H
#define BROWSERMANAGER_H

#include "abstractcheckablemanager.h"

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
    void sendBrowserMember(QString, QString, QString);
private:
    QVBoxLayout* verticalLayout;
};

#endif // BROWSERMANAGER_H
