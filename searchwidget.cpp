#include "searchwidget.h"
#include "ui_searchwidget.h"

#include <QCompleter>
#include <QKeyEvent>
#include <QStringListModel>

SearchWidget::SearchWidget(QWidget *parent, const QStringList& wordList_) :
    QWidget(parent),
    ui(new Ui::SearchedWidget),
    wordList(wordList_)
{
    ui->setupUi(this);
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseSensitive);
    setNewStringList(wordList);
    ui->searchLineEdit->setCompleter(completer);

}

void SearchWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() != Qt::Key_Enter && event->key() != Qt::Key_Return)
    {
        return;
    }
    emit sendSearchString(ui->searchLineEdit->text());
}

void SearchWidget::setNewStringList(const QStringList &newWordList)
{
    wordList = newWordList;
    completer->setModel(new QStringListModel(wordList));
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::addSearchString(QString newSearchString)
{
    wordList << newSearchString;
    completer->setModel(new QStringListModel(wordList));
}

void SearchWidget::deleteSearchString(QString deletedSearchString)
{
    wordList.removeOne(deletedSearchString);
    completer->setModel(new QStringListModel(wordList));
}

void SearchWidget::on_deletePushButton_clicked()
{
    ui->searchLineEdit->backspace();
}

void SearchWidget::on_magnifierIcon_clicked()
{
    emit sendSearchString(ui->searchLineEdit->text());
}

void SearchWidget::on_updatePushButton_clicked()
{
    emit updateManager();
}

