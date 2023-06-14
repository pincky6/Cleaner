#ifndef APPLICATIONINFOWIDGET_H
#define APPLICATIONINFOWIDGET_H

#include "abstractinfowidget.h"
#include "applicationinfoitem.h"

class ApplicationInfoWidget : public AbstractInfoWidget
{
    Q_OBJECT
public:
    ApplicationInfoWidget(ApplicationInfoItem*, AbstractInfoWidget* parent = nullptr);
    AbstractInfoItem* getInfoItem() override;
    bool compareInfoItem(const AbstractInfoItem*) const override;

    const QString& getName() const;
    const QString& getVersion() const;
    const QString& getIconPath() const;
    const QString& getCreators() const;
    const QString& getUninstallString() const;
signals:
    void sendUninstallString(QString);
private slots:
    void deleteButtonPressed();
};

#endif // APPLICATIONINFOWIDGET_H
