#pragma once
#ifndef DIALOG_H
#define DIALOG_H
#include <QtWidgets/QWidget>
#include "ui_QtAudio.h"
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

class QtAudio : public QWidget
{
	Q_OBJECT

public:
	QtAudio(QWidget *parent = Q_NULLPTR);
	~QtAudio();
private:
	Ui::QtAudioClass ui;
	QChart * m_chart;
};
#endif
