#include "abstractcheckablemanager.h"
#include "ui_abstractmanager.h"

#include <QPushButton>

AbstractCheckableManager::AbstractCheckableManager(AbstractManager* parent):
    AbstractManager(parent)
{
    QPushButton* checkAllButton = new QPushButton("Check All");
    QPushButton* deleteButton = new QPushButton("Delete");

    connect(checkAllButton, &QPushButton::clicked, this, &AbstractCheckableManager::checkAllItems);
    connect(deleteButton, &QPushButton::clicked, this, &AbstractCheckableManager::deleteCheckedPaths);

    ui->verticalLayout->addWidget(checkAllButton);
    ui->verticalLayout->addWidget(deleteButton);
}

void AbstractCheckableManager::checkAllItems()
{
    checkAll();
}

void AbstractCheckableManager::deleteCheckedPaths()
{
    deleteChecked();
}

