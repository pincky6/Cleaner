
#ifndef ABSTRACTCHECKABLEMANAGER_H
#define ABSTRACTCHECKABLEMANAGER_H

#include "abstractmanager.h"



class AbstractCheckableManager : public AbstractManager
{
    Q_OBJECT
public:
    AbstractCheckableManager(AbstractManager* parent = nullptr);
    virtual void checkAll() = 0;
    virtual void deleteChecked() = 0;
public slots:
    void checkAllItems();
    void deleteCheckedPaths();
};

#endif // ABSTRACTCHECKABLEMANAGER_H
