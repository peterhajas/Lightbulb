#include "homedisplay.h"
#include "ui_homedisplay.h"
#include <QDateTime>
#include <QWebFrame>
#include <QDebug>

HomeDisplay::HomeDisplay(QWidget *parent)
    : QWidget(parent), ui(new Ui::HomeDisplay)
{
    ui->setupUi(this);
    //Set up the news component of the display - we'll use Google News (very simplistic)
    ui->newsWebview->setUrl(QUrl("http://news.google.com/news?pz=1&ned=us&hl=en&hdlOnly=1"));
    //Set up the weather view. This is something written by a Redditor, but we could roll our own
    ui->weatherWebview->setUrl(QUrl("http://geoipweather.com/"));
    //Accessibility for the text on both pages
    ui->newsWebview->setTextSizeMultiplier(1.15);
    ui->weatherWebview->setTextSizeMultiplier(1.25);

    //Make the help video object invisible
    ui->helpVideo->setVisible(false);

    //Configure our time object
    time = new QDateTime();
    time->currentDateTime();

    //Set up the dateLabel
    ui->dateLabel->setText(time->toString("dddd MMMM d"));
    qDebug() << time->toString("hh:mm");
    //Set up the time label
    ui->timeLabel->setText(time->toString("hh:mm"));

    //SIGNALS
    //This will be triggered when the user presses "help" on the screen
    //connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(playHelpMovie()));
    //This is triggered when the news page finishes loading
    connect(ui->newsWebview, SIGNAL(loadFinished(bool)), this, SLOT(finishedNewsLoad()));
    connect(ui->weatherWebview, SIGNAL(loadFinished(bool)), this, SLOT(finishedWeatherLoad()));
    connect(ui->newsWebview, SIGNAL(loadProgress(int)), this, SLOT(newsIsLoading(int)));
    connect(ui->weatherWebview, SIGNAL(loadProgress(int)), this, SLOT(weatherIsLoading(int)));

    //Down here, we should potentially detect whether or not this is the first time Home has been run, and if so, play the first time video?
}

HomeDisplay::~HomeDisplay()
{
    delete ui;
}

void HomeDisplay::playHelpMovie()
{
    ui->helpVideo->setVisible(true);
    //ui->helpVideo->load("help.avi");
    ui->helpVideo->play();
    this->postHelpMovie();
}

void HomeDisplay::postHelpMovie()
{
    while(ui->helpVideo->isPlaying())
    {
        sleep(500);
    }
    ui->helpVideo->setVisible(false);
}

void HomeDisplay::finishedNewsLoad()
{
    ui->newsWebview->page()->mainFrame()->setScrollPosition((ui->newsWebview->page()->mainFrame()->scrollPosition()) + QPoint(-500, -500));
}

void HomeDisplay::finishedWeatherLoad()
{
    ui->weatherWebview->page()->mainFrame()->setScrollPosition(QPoint(0, 500));
}

void HomeDisplay::newsIsLoading(int value)
{
    ui->loadProgress->setValue(value);
}

void HomeDisplay::weatherIsLoading(int value)
{

}
