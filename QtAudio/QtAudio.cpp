#include "QtAudio.h"

QtAudio::QtAudio(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// 构建系列-折线
	QLineSeries *series = new QLineSeries();
	// 为系列设置数据
	for (quint32 i = 0; i < 100; i++) {
		series->append(i, sin(0.6f*i));
	}
	// 构建图表
	m_chart = new QChart();

	// 添加系列
	m_chart->addSeries(series);
	//chart->legend()->hide();		// 隐藏图例

	m_chart->createDefaultAxes();		// 基于已添加到图表的 series 来创建默认的坐标轴

									// 设置主题
	m_chart->setTheme(QChart::ChartThemeDark);

	// 将图表绑定到视图
	ui.widget->setChart(m_chart);
}
QtAudio::~QtAudio()
{
	m_chart->removeAllSeries();
}
