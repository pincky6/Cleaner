#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

class QCompleter;

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent  *event);
    void setCompleterWords(const QStringList&);
    ~SearchWidget();
signals:
    void sendSearchedString(QString);
private:
    Ui::SearchWidget *ui;
    QCompleter* completer;
};

#endif // SEARCHWIDGET_H
