#include "searchwidget.h"
#include "ui_searchwidget.h"
#include <QCompleter>
#include <QComboBox>
#include <QKeyEvent>
#include <QStringListModel>

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseSensitive);
    ui->searchLineEdit->setCompleter(completer);

}

void SearchWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() != Qt::Key_Enter && event->key() != Qt::Key_Return)
    {
        return;
    }
    emit sendSearchedString(ui->searchLineEdit->text());
}

void SearchWidget::setCompleterWords(const QStringList &newWordList)
{
    completer->setModel(new QStringListModel(newWordList));
}

SearchWidget::~SearchWidget()
{
    delete ui;
}
