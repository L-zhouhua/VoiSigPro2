#include "QtAudio2.h"
#include<AudioPoint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;
QtAudio2::QtAudio2(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setupPlot();
	ui.horizontalScrollBar->setRange(-10, 100);
	ui.verticalScrollBar->setRange(-10, 10);

	connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
	connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
	connect(ui.widget->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
	connect(ui.widget->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
	connect(ui.pushButton, &QCheckBox::clicked, this, &QtAudio2::reset_chart_click);

}
void QtAudio2::setupPlot()
{
	SF_INFO sf_info;
	AudioPoint ap;
	sf_info = ap.getAudioPoint();
	samplerate = sf_info.samplerate;
	channels = sf_info.channels;
	frames = sf_info.frames;
	//��ȡwav��д��dat�ļ�
	buf = new double[sf_info.frames];
	ifstream infile;
	infile.open("double.dat");
	string s;
	int i = 0;
	//��ȡdat������buf��
	QVector<double> x(sf_info.frames), y(sf_info.frames);
	while (getline(infile, s))
	{
		y[i++] = stod(s);
	}
	for (int j = 0; j < sf_info.frames; j++)
	{
		x[j] = (double)j / sf_info.samplerate;
	}
	//�ر���
	infile.close();
	// ����ϵ��-����
	//series = new QSplineSeries();
	//// Ϊϵ����������
	//connect(ui.pushButton, &QCheckBox::clicked, this, &QtAudio2::reset_chart_click);
	////connect(ui.checkBox_2, &QCheckBox::clicked, this, &QtAudio2::on_changefrequency_click);
	//double samplerate = sf_info.samplerate;
	//for (int i = 0; i < sf_info.frames; i++) {
	//	series->append(i / samplerate, buf[i]);
	//}
	//// ����ͼ��
	//m_chart = new QChart();
	//series->setUseOpenGL(true);//�������ܣ�������ûʲô��...
	//// ���ϵ��
	//m_chart->addSeries(series);
	//
	////����x��
	//x = new QValueAxis();
	//x->setRange(0, sf_info.frames/ samplerate);
	//x->setLabelFormat("%g");
	//x->setTickCount(1);
	//x->setTitleText("X");
	////����y��
	//y = new QValueAxis();
	//y->setRange(-1, 1);
	//y->setLabelFormat("%g");
	//y->setTickCount(1);
	//y->setTitleText("Y");
	////m_chart->createDefaultAxes();		// ��������ӵ�ͼ��� series ������Ĭ�ϵ�������
	//m_chart->legend()->hide(); // ����ͼ��
	//m_chart->setAxisX(x, series);
	//m_chart->setAxisY(y, series);
	//m_chart->setTheme(QChart::ChartThemeDark);// ��������
	//// ��ͼ��󶨵���ͼ
	////ui.widget->setChart(m_chart);
	pGraph = ui.widget->addGraph();
	pGraph->setPen(QPen(QColor(32, 178, 170)));//��������ɫ
	ui.widget->xAxis->setRange(0.0, (double)frames / samplerate);//����x�᷶Χ
	ui.widget->yAxis->setRange(-1, 1);//����y�᷶Χ
	ui.widget->axisRect()->setupFullAxesBox(true);
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//ƽ�ơ��Ŵ���С
	ui.widget->graph(0)->setData(x, y);
	ui.widget->xAxis->setLabel("x");//x������
	ui.widget->yAxis->setLabel("y");//y������ 
}
void QtAudio2::reset_chart_click()
{
	
}
void QtAudio2::horzScrollBarChanged(int value)
{
	if (qAbs(ui.widget->xAxis->range().center() - value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		ui.widget->xAxis->setRange(value / 100.0, ui.widget->xAxis->range().size(), Qt::AlignCenter);
		ui.widget->replot();
	}
}

void QtAudio2::vertScrollBarChanged(int value)
{
	if (qAbs(ui.widget->yAxis->range().center() + value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		ui.widget->yAxis->setRange(-value / 100.0, ui.widget->yAxis->range().size(), Qt::AlignCenter);
		ui.widget->replot();
	}
}

void QtAudio2::xAxisChanged(QCPRange range)
{
	ui.horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
	ui.horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void QtAudio2::yAxisChanged(QCPRange range)
{
	ui.verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
	ui.verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}
QtAudio2::~QtAudio2()
{
	delete(buf);
	buf = NULL;
	//m_chart->removeAllSeries();
	delete ui.widget;
}