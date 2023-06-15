#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H

#include "abstractworker.h"
#include "abstractinfowidget.h"

#include <QWidget>
#include <vector>

namespace Ui {
class AbstractManager;
}

class QVBoxLayout;

class AbstractManager : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractManager(QWidget *parent = nullptr);
    virtual ~AbstractManager();
protected:
    virtual void initInfoWidgets() = 0;

    void addStringToSearchWidget(QString);
    void deleteStringFromSearchWidget(QString);

    void setWorker(AbstractWorker*);

    virtual void search(QString);
private:
    void stopThread();
protected slots:
    void findInputString(QString);
signals:
    void sendNewSearchString(QString);
    void sendDeletedSearchString(QString);
protected:
    std::vector<AbstractInfoWidget*> infoWidgetVector;
    Ui::AbstractManager *ui;
    AbstractWorker* worker;
};

#endif // ABSTRACTMANAGER_H
