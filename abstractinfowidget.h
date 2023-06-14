#ifndef ABSTRACTINFOWIDGET_H
#define ABSTRACTINFOWIDGET_H

#include "abstractinfoitem.h"

#include <QWidget>

namespace Ui {
class AbstractInfoWidget;
}

//class UniqueInfoItemPtr
//{
//public:
//    UniqueInfoItemPtr(AbstractInfoItem*);

//    UniqueInfoItemPtr(const UniqueInfoItemPtr&) = delete;
//    UniqueInfoItemPtr(UniqueInfoItemPtr&&) noexcept;

//    UniqueInfoItemPtr& operator=(const UniqueInfoItemPtr&) = delete;
//    UniqueInfoItemPtr& operator=(UniqueInfoItemPtr&&) noexcept;

//    AbstractInfoItem* get();
//    const AbstractInfoItem* get() const;

//    ~UniqueInfoItemPtr();
//};

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
