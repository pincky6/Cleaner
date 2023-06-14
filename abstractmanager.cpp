#include "abstractmanager.h"
#include "ui_abstractmanager.h"

#include <QVBoxLayout>

AbstractManager::AbstractManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractManager)
{
    ui->setupUi(this);
    verticalLayout = new QVBoxLayout;
    connect(this, &AbstractManager::sendNewSearchString, ui->searchWidget, &SearchWidget::addSearchString);
    connect(this, &AbstractManager::sendDeletedSearchString, ui->searchWidget, &SearchWidget::deleteSearchString);
    connect(ui->searchWidget, &SearchWidget::sendSearchString, this, &AbstractManager::findInputString);
}


AbstractManager::~AbstractManager()
{
    delete worker;
    delete ui;
}

void AbstractManager::addStringToSearchWidget(QString name)
{
    emit sendNewSearchString(name);
}

void AbstractManager::deleteStringFromSearchWidget(QString name)
{
    emit sendDeletedSearchString(name);
}

void AbstractManager::setWorker(AbstractWorker *newWorker)
{
    worker = newWorker;
}

void AbstractManager::search(QString searchedString)
{
    for (auto abstractInfoWidget : ui->scrollArea->findChildren<AbstractInfoWidget*>())
    {
        if (abstractInfoWidget->getInfo().contains(searchedString))
        {
            ui->scrollArea->ensureWidgetVisible(abstractInfoWidget, 0, 0);
            break;
        }
    }
}
void AbstractManager::findInputString(QString searchString)
{
    search(searchString);
}
