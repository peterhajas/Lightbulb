/********************************************************************************
** Form generated from reading ui file 'homedisplay.ui'
**
** Created: Fri Dec 11 01:23:32 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_HOMEDISPLAY_H
#define UI_HOMEDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include <phonon/videoplayer.h>

QT_BEGIN_NAMESPACE

class Ui_HomeDisplay
{
public:
    QWebView *newsWebview;
    QLabel *dateLabel;
    Phonon::VideoPlayer *helpVideo;
    QWebView *weatherWebview;
    QLabel *timeLabel;
    QProgressBar *loadProgress;

    void setupUi(QWidget *HomeDisplay)
    {
        if (HomeDisplay->objectName().isEmpty())
            HomeDisplay->setObjectName(QString::fromUtf8("HomeDisplay"));
        HomeDisplay->resize(800, 600);
        HomeDisplay->setMinimumSize(QSize(800, 600));
        newsWebview = new QWebView(HomeDisplay);
        newsWebview->setObjectName(QString::fromUtf8("newsWebview"));
        newsWebview->setGeometry(QRect(10, 110, 541, 481));
        newsWebview->setUrl(QUrl("about:blank"));
        dateLabel = new QLabel(HomeDisplay);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
        dateLabel->setGeometry(QRect(10, 0, 531, 91));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica"));
        font.setPointSize(45);
        dateLabel->setFont(font);
        helpVideo = new Phonon::VideoPlayer(HomeDisplay);
        helpVideo->setObjectName(QString::fromUtf8("helpVideo"));
        helpVideo->setEnabled(true);
        helpVideo->setGeometry(QRect(10, 100, 781, 191));
        weatherWebview = new QWebView(HomeDisplay);
        weatherWebview->setObjectName(QString::fromUtf8("weatherWebview"));
        weatherWebview->setGeometry(QRect(559, 110, 231, 481));
        weatherWebview->setUrl(QUrl("about:blank"));
        timeLabel = new QLabel(HomeDisplay);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setGeometry(QRect(541, 1, 251, 101));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Helvetica"));
        font1.setPointSize(100);
        timeLabel->setFont(font1);
        loadProgress = new QProgressBar(HomeDisplay);
        loadProgress->setObjectName(QString::fromUtf8("loadProgress"));
        loadProgress->setGeometry(QRect(10, 90, 781, 23));
        loadProgress->setValue(24);

        retranslateUi(HomeDisplay);

        QMetaObject::connectSlotsByName(HomeDisplay);
    } // setupUi

    void retranslateUi(QWidget *HomeDisplay)
    {
        HomeDisplay->setWindowTitle(QApplication::translate("HomeDisplay", "HomeDisplay", 0, QApplication::UnicodeUTF8));
        dateLabel->setText(QApplication::translate("HomeDisplay", "saturday september 5th", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("HomeDisplay", "09:44", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(HomeDisplay);
    } // retranslateUi

};

namespace Ui {
    class HomeDisplay: public Ui_HomeDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEDISPLAY_H
