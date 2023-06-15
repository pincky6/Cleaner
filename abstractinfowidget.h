#ifndef ABSTRACTINFOWIDGET_H
#define ABSTRACTINFOWIDGET_H

#include "abstractinfoitem.h"

#include <QWidget>

namespace Ui {
class AbstractInfoWidget;
}



class AbstractInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractInfoWidget(const QString&, const QString&,
                                AbstractInfoItem*, QWidget *parent = nullptr);
    QString getInfo();
    virtual AbstractInfoItem* getInfoItem() = 0;
    virtual bool compareInfoItem(const AbstractInfoItem*) const = 0;
    virtual ~AbstractInfoWidget();
protected:
    Ui::AbstractInfoWidget *ui;
    AbstractInfoItem* infoItem;
};

#endif // ABSTRACTINFOWIDGET_H
