
#ifndef ABSTRACTINFOITEM_H
#define ABSTRACTINFOITEM_H




class AbstractInfoItem
{
public:
    AbstractInfoItem();

    virtual bool operator==(const AbstractInfoItem*) const = 0;
    virtual bool operator!=(const AbstractInfoItem*) const = 0;

    virtual bool isEmpty() const = 0;

    virtual ~AbstractInfoItem();
};

#endif // ABSTRACTINFOITEM_H
