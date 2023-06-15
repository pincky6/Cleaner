
#ifndef BROWSERMANAGERWORKER_H
#define BROWSERMANAGERWORKER_H

#include "abstractworker.h"
#include "abstractinfowidget.h"
#include "browserinfoitem.h"


class BrowserManagerWorker : public AbstractWorker
{
    Q_OBJECT
public:
    BrowserManagerWorker(const std::vector<AbstractInfoWidget*>&, AbstractWorker* parent = nullptr);
signals:
    void sendNewApplicationInfo(const std::size_t, BrowserInfoItem);
    void sendDeletedApplicationWidget(AbstractInfoWidget*);
private:
    void work() override;

    template<typename FirstCont, typename SecondCont, typename Fn>
    int findIndex(FirstCont && firstCont, SecondCont && secondCont, Fn func, int& index);
    void addNewApplicationWidget(const std::vector<AbstractInfoWidget*>&,  const std::vector<BrowserInfoItem*>&);
    void deleteApplicationWidget(const std::vector<AbstractInfoWidget*>&,  const std::vector<BrowserInfoItem*>&);
    void clear(std::vector<BrowserInfoItem*>&);
public:
    const std::vector<AbstractInfoWidget*>& infoWidgetVector;
};

template<typename FirstCont, typename SecondCont, typename Fn>
int BrowserManagerWorker::findIndex(FirstCont && firstCont, SecondCont && secondCont, Fn func, int& index)
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

#endif // BROWSERMANAGERWORKER_H
