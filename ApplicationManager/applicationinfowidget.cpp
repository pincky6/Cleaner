#include "applicationinfowidget.h"
#include "ui_abstractinfowidget.h"
#include "applicationinfoitem.h"

#include <QPushButton>

ApplicationInfoWidget::ApplicationInfoWidget(ApplicationInfoItem* applicationInfoItem_, AbstractInfoWidget* parent):
    AbstractInfoWidget(applicationInfoItem_->name + "\n" +
                           applicationInfoItem_->creators + " | " + applicationInfoItem_->version,
                       applicationInfoItem_->iconPath , applicationInfoItem_, parent)

{
    QPushButton* deleteButton = new QPushButton("Delete", this);
    ui->horizontalLayout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked, this, &ApplicationInfoWidget::deleteButtonPressed);
}

AbstractInfoItem *ApplicationInfoWidget::getInfoItem()
{
    return infoItem;
}

bool ApplicationInfoWidget::compareInfoItem(const AbstractInfoItem* otherInfoItem) const
{
    return *infoItem == otherInfoItem;
}

const QString &ApplicationInfoWidget::getName() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->name;
}

const QString &ApplicationInfoWidget::getVersion() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->version;
}

const QString &ApplicationInfoWidget::getIconPath() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->iconPath;
}

const QString &ApplicationInfoWidget::getCreators() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->creators;
}

const QString &ApplicationInfoWidget::getUninstallString() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->uninstallString;
}

void ApplicationInfoWidget::deleteButtonPressed()
{
    emit sendUninstallString(dynamic_cast<ApplicationInfoItem*>(infoItem)->uninstallString);
}

