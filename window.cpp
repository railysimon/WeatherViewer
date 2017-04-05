#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    view = new QWebEngineView;
    view->load(QUrl("https://www.windytv.com"));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(FinishLoad(bool)));
    this->startTimer(100);

    Layout();
}

Window::~Window()
{

}

QPushButton *Window::button(QIcon icon)
{
    QPushButton *btn = new QPushButton;
    btn->setIcon(icon);
    btn->setMaximumHeight(10);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet("QPushButton { background-color: rgb(150, 145, 219)} "
                       "QPushButton:hover {background-color: rgb(85, 202, 128)}");

    return btn;
}

void Window::Layout()
{
    QProgressBar *bar = new QProgressBar;
    bar->setMaximumHeight(10);
    connect(view, SIGNAL(loadProgress(int)), bar, SLOT(setValue(int)));

    back = button(QIcon(QPixmap("back.png")));
    connect(back, SIGNAL(clicked(bool)), view, SLOT(back()));

    forward = button(QIcon(QPixmap("forward.png")));
    connect(forward, SIGNAL(clicked(bool)), view, SLOT(forward()));

    exit = button(QIcon(QPixmap("exit.png")));
    connect(exit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));

    QHBoxLayout *control = new QHBoxLayout;
    control->addSpacing(5);
    control->addWidget(exit);
    control->addWidget(back);
    control->addWidget(forward);
    control->addWidget(bar);
    control->addSpacing(5);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addSpacing(5);
    layout->addLayout(control);
    layout->addWidget(view);
    this->setLayout(layout);
}

void Window::timerEvent(QTimerEvent *event)
{
    back->setEnabled(view->page()->history()->canGoBack());
    forward->setEnabled(view->page()->history()->canGoForward());

    Q_UNUSED(event);
}

void Window::FinishLoad(bool status)
{
    if(!status)
        view->setHtml("<html><h1>Server didn't respond!</h1></html>");
}
