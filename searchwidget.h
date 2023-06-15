#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class SearchedWidget;
}

class QCompleter;

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = nullptr, const QStringList& wordList_ = QStringList());
    void keyPressEvent(QKeyEvent *event) override;
    void setNewStringList(const QStringList&);

    ~SearchWidget();
signals:
    void updateManager();
    void sendSearchString(QString);
public slots:
    void addSearchString(QString);
    void deleteSearchString(QString);
private slots:    
    void on_deletePushButton_clicked();
    void on_magnifierIcon_clicked();
    void on_updatePushButton_clicked();
private:
    Ui::SearchedWidget *ui;
    QCompleter* completer;
    QStringList wordList;
};

#endif // SEARCHWIDGET_H
