#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebEngineHistory>
#include <QSplitter>
#include <QPushButton>
#include <QProgressBar>
#include <QTimerEvent>
#include <QVBoxLayout>
#include <QApplication>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        QPushButton *button(QIcon icon);
        void Layout();

protected:
            virtual void timerEvent(QTimerEvent *event);

private:
        QWebEngineView *view;
        QPushButton *back, *forward, *exit;

private slots:
            void FinishLoad(bool status);
};

#endif // WINDOW_H
