/********************************************************************************
** Form generated from reading UI file 'QtAudio.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTAUDIO_H
#define UI_QTAUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_QtAudioClass
{
public:
    QChartView *widget;

    void setupUi(QWidget *QtAudioClass)
    {
        if (QtAudioClass->objectName().isEmpty())
            QtAudioClass->setObjectName(QString::fromUtf8("QtAudioClass"));
        QtAudioClass->resize(600, 400);
        widget = new QChartView(QtAudioClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(80, 30, 431, 271));

        retranslateUi(QtAudioClass);

        QMetaObject::connectSlotsByName(QtAudioClass);
    } // setupUi

    void retranslateUi(QWidget *QtAudioClass)
    {
        QtAudioClass->setWindowTitle(QApplication::translate("QtAudioClass", "QtAudio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtAudioClass: public Ui_QtAudioClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAUDIO_H
