#include "browserinfowidget.h"
#include "ui_abstractinfowidget.h"

#include <QCheckBox>
#include <QVBoxLayout>

BrowserInfoWidget::BrowserInfoWidget(BrowserInfoItem* browserInfoItem, AbstractInfoWidget* parent):
    AbstractInfoWidget(browserInfoItem->name,
                       browserInfoItem->iconPath , browserInfoItem, parent)
{
    deleteCache = new QCheckBox("Delete cache");
    deleteCookies = new QCheckBox("Delete cookies");
    QVBoxLayout* verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(deleteCache);
    verticalLayout->addWidget(deleteCookies);
    ui->horizontalLayout->addLayout(verticalLayout);
}

AbstractInfoItem *BrowserInfoWidget::getInfoItem()
{
    return infoItem;
}

bool BrowserInfoWidget::compareInfoItem(const AbstractInfoItem* otherInfoItem) const
{
    return *infoItem == otherInfoItem;
}

const QString &BrowserInfoWidget::getName() const
{
    return dynamic_cast<BrowserInfoItem*>(infoItem)->name;
}

const QString &BrowserInfoWidget::getCachePath() const
{
    return dynamic_cast<BrowserInfoItem*>(infoItem)->cachePath;
}

const QString &BrowserInfoWidget::getCookiesPath() const
{
    return dynamic_cast<BrowserInfoItem*>(infoItem)->cookiesPath;
}

bool BrowserInfoWidget::cacheCheckBoxChecked() const
{
    return deleteCache->isChecked();
}

bool BrowserInfoWidget::cookiesCheckBoxChecked() const
{
    return deleteCookies->isChecked();
}

void BrowserInfoWidget::setCacheCheckBox(bool flag)
{
    deleteCache->setChecked(flag);
}

void BrowserInfoWidget::setCookiesCheckBox(bool flag)
{
    deleteCookies->setChecked(flag);
}




