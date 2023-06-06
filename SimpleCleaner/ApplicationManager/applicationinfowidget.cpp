#include "applicationinfowidget.h"
#include "ui_applicationinfowidget.h"
#include <QSettings>
#include <QFileIconProvider>
#include <QFileInfo>


ApplicationInfoWidget::ApplicationInfoWidget(const ApplicationInfoItem& applicationInfoItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationInfoWidget), applicationInfoItem_(applicationInfoItem)
{
    ui->setupUi(this);
    QFileIconProvider provider;
    QFileInfo fileInfo(applicationInfoItem.applicationIconPath_);
    QIcon icon = provider.icon(fileInfo);
    QImage image = icon.pixmap(50, 50).toImage();
    ui->iconLabel->setPixmap(QPixmap::fromImage(image.scaled(QSize(50, 50))));
    ui->applicationInfo->setText(applicationInfoItem.applicationName_ + "\n" +
                                 applicationInfoItem.applicationCompany_ + " | " + applicationInfoItem.applicationVersion_);

}

QString ApplicationInfoWidget::getApplicationInfo() const
{
    return ui->applicationInfo->text();
}

const QString& ApplicationInfoWidget::getApplicationName() const
{
    return applicationInfoItem_.applicationName_;
}

const ApplicationInfoItem &ApplicationInfoWidget::getApplicationInfoItem() const
{
    return applicationInfoItem_;
}

bool ApplicationInfoWidget::compareApplicationInfo(const ApplicationInfoItem& other) const
{
    return applicationInfoItem_ == other;
}

ApplicationInfoWidget::~ApplicationInfoWidget()
{
    delete ui;
}

void ApplicationInfoWidget::on_deletePushButton_clicked()
{
    emit deleteButtonPressedSignal(applicationInfoItem_.applicationUninstallString_);
}

