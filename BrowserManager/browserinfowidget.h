
#ifndef BROWSERINFOWIDGET_H
#define BROWSERINFOWIDGET_H

#include "abstractinfowidget.h"
#include "browserinfoitem.h"

class QCheckBox;

class BrowserInfoWidget : public AbstractInfoWidget
{
    Q_OBJECT
public:
    BrowserInfoWidget(BrowserInfoItem*, AbstractInfoWidget* parent = nullptr);
    AbstractInfoItem* getInfoItem() override;
    bool compareInfoItem(const AbstractInfoItem*) const override;

    const QString& getName() const;
    const QString& getCachePath() const;
    const QString& getCookiesPath() const;
    bool cacheCheckBoxChecked() const;
    bool cookiesCheckBoxChecked() const;
    void setCacheCheckBox(bool);
    void setCookiesCheckBox(bool);
private:
    QCheckBox* deleteCache;
    QCheckBox* deleteCookies;
};

#endif // BROWSERINFOWIDGET_H
