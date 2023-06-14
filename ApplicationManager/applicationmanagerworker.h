
#ifndef APPLICATIONMANAGERWORKER_H
#define APPLICATIONMANAGERWORKER_H

#include "abstractworker.h"
#include "abstractinfowidget.h"
#include "applicationinfoitem.h"
#include <vector>

class ApplicationManagerWorker : public AbstractWorker
{
    Q_OBJECT
public:
    ApplicationManagerWorker(const std::vector<AbstractInfoWidget*>&, AbstractWorker* parent = nullptr);
signals:
    void sendNewApplicationInfo(const std::size_t, ApplicationInfoItem);
    void sendDeletedApplicationWidget(AbstractInfoWidget*);
private:
    void work() override;

    template<typename FirstCont, typename SecondCont, typename Fn>
    int findIndex(FirstCont && firstCont, SecondCont && secondCont, Fn func, int& index);
    void addNewApplicationWidget(const std::vector<AbstractInfoWidget*>&,  const std::vector<ApplicationInfoItem*>&);
    void deleteApplicationWidget(const std::vector<AbstractInfoWidget*>&,  const std::vector<ApplicationInfoItem*>&);
    void clear(std::vector<ApplicationInfoItem*>&);
public:
    const std::vector<AbstractInfoWidget*>& infoWidgetVector;
};


template<typename FirstCont, typename SecondCont, typename Fn>
int ApplicationManagerWorker::findIndex(FirstCont && firstCont, SecondCont && secondCont, Fn func, int& index)
{
    for(std::size_t i = 0; i < firstCont.size(); i++)
    {
        auto it = std::find_if(secondCont.begin(), secondCont.end(), func);
        index++;
        if(it != secondCont.end())
            continue;
        return i;
    }
    return -1;
}


#endif // APPLICATIONMANAGERWORKER_H
