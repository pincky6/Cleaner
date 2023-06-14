#include "abstractinfowidget.h"
#include "ui_abstractinfowidget.h"

#include <QFileIconProvider>

AbstractInfoWidget::AbstractInfoWidget(const QString& info, const QString& iconPath,
                                       AbstractInfoItem* infoItem_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractInfoWidget),
    infoItem(infoItem_)
{
    ui->setupUi(this);
    QFileIconProvider provider;
    QFileInfo fileInfo(iconPath);
    QIcon icon = provider.icon(fileInfo);
    QImage image = icon.pixmap(50, 50).toImage();
    ui->iconLabel->setPixmap(QPixmap::fromImage(image.scaled(QSize(50, 50))));
    ui->infoLabel->setText(info);
}

QString AbstractInfoWidget::getInfo()
{
    return ui->infoLabel->text();
}

AbstractInfoWidget::~AbstractInfoWidget()
{
    delete infoItem;
    delete ui;
}
