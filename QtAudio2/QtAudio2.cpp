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
	//读取wav并写入dat文件
	buf = new double[sf_info.frames];
	ifstream infile;
	infile.open("double.dat");
	string s;
	int i = 0;
	//读取dat并存入buf中
	QVector<double> x(sf_info.frames), y(sf_info.frames);
	while (getline(infile, s))
	{
		y[i++] = stod(s);
	}
	for (int j = 0; j < sf_info.frames; j++)
	{
		x[j] = (double)j / sf_info.samplerate;
	}
	//关闭流
	infile.close();
	// 构建系列-折线
	//series = new QSplineSeries();
	//// 为系列设置数据
	//connect(ui.pushButton, &QCheckBox::clicked, this, &QtAudio2::reset_chart_click);
	////connect(ui.checkBox_2, &QCheckBox::clicked, this, &QtAudio2::on_changefrequency_click);
	//double samplerate = sf_info.samplerate;
	//for (int i = 0; i < sf_info.frames; i++) {
	//	series->append(i / samplerate, buf[i]);
	//}
	//// 构建图表
	//m_chart = new QChart();
	//series->setUseOpenGL(true);//改善性能，但好像没什么用...
	//// 添加系列
	//m_chart->addSeries(series);
	//
	////设置x轴
	//x = new QValueAxis();
	//x->setRange(0, sf_info.frames/ samplerate);
	//x->setLabelFormat("%g");
	//x->setTickCount(1);
	//x->setTitleText("X");
	////设置y轴
	//y = new QValueAxis();
	//y->setRange(-1, 1);
	//y->setLabelFormat("%g");
	//y->setTickCount(1);
	//y->setTitleText("Y");
	////m_chart->createDefaultAxes();		// 基于已添加到图表的 series 来创建默认的坐标轴
	//m_chart->legend()->hide(); // 隐藏图例
	//m_chart->setAxisX(x, series);
	//m_chart->setAxisY(y, series);
	//m_chart->setTheme(QChart::ChartThemeDark);// 设置主题
	//// 将图表绑定到视图
	////ui.widget->setChart(m_chart);
	pGraph = ui.widget->addGraph();
	pGraph->setPen(QPen(QColor(32, 178, 170)));//设置线颜色
	ui.widget->xAxis->setRange(0.0, (double)frames / samplerate);//设置x轴范围
	ui.widget->yAxis->setRange(-1, 1);//设置y轴范围
	ui.widget->axisRect()->setupFullAxesBox(true);
	ui.widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//平移、放大缩小
	ui.widget->graph(0)->setData(x, y);
	ui.widget->xAxis->setLabel("x");//x轴名称
	ui.widget->yAxis->setLabel("y");//y轴名称 
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