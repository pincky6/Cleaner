#include "applicationinfowidget.h"
#include "ui_abstractinfowidget.h"

#include <QPushButton>

ApplicationInfoWidget::ApplicationInfoWidget(ApplicationInfoItem* applicationInfoItem_, AbstractInfoWidget* parent):
    AbstractInfoWidget(applicationInfoItem_->applicationName + "\n" +
                           applicationInfoItem_->applicationCreators + " | " + applicationInfoItem_->applicationVersion,
                       applicationInfoItem_->applicationIconPath , applicationInfoItem_, parent)

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
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationName;
}

const QString &ApplicationInfoWidget::getVersion() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationVersion;
}

const QString &ApplicationInfoWidget::getIconPath() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationIconPath;
}

const QString &ApplicationInfoWidget::getCreators() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationCreators;
}

const QString &ApplicationInfoWidget::getUninstallString() const
{
    return dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationUninstallString;
}

void ApplicationInfoWidget::deleteButtonPressed()
{
    emit sendUninstallString(dynamic_cast<ApplicationInfoItem*>(infoItem)->applicationUninstallString);
}

