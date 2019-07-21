#ifndef DIALOG_H
#define DIALOG_H
#pragma once
#include <QtWidgets/QDialog>
#include <QtCharts>
#include "ui_QtAudio2.h"
QT_CHARTS_USE_NAMESPACE
class QtAudio2 : public QDialog
{
	Q_OBJECT

public:
	QtAudio2(QWidget *parent = Q_NULLPTR);
	void setupPlot();
	~QtAudio2();
private slots:
	void reset_chart_click();
	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);
	void xAxisChanged(QCPRange range);
	void yAxisChanged(QCPRange range);
private:
	Ui::Dialog ui;
	double* buf;
	QPoint dragPosition;
	QCPGraph *pGraph;
	double samplerate;//������
	double frames; //�����㣨�������ȣ�
	double channels;
};
#endif
