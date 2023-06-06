#ifndef APPLICATIONINFOWIDGET_H
#define APPLICATIONINFOWIDGET_H

#include <QWidget>
#include "applicationInfoItem.h"

namespace Ui {
class ApplicationInfoWidget;
}

class ApplicationInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationInfoWidget(const ApplicationInfoItem&, QWidget *parent = nullptr);
    QString getApplicationInfo() const;
    const QString& getApplicationName() const;
    const ApplicationInfoItem& getApplicationInfoItem() const;
    bool compareApplicationInfo(const ApplicationInfoItem&) const;
    ~ApplicationInfoWidget();
signals:
    void deleteButtonPressedSignal(QString);
private slots:
    void on_deletePushButton_clicked();

private:
    Ui::ApplicationInfoWidget *ui;
    ApplicationInfoItem applicationInfoItem_;
};

#endif // APPLICATIONINFOWIDGET_H
