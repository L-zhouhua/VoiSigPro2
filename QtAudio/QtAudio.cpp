#include "QtAudio.h"

QtAudio::QtAudio(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// ����ϵ��-����
	QLineSeries *series = new QLineSeries();
	// Ϊϵ����������
	for (quint32 i = 0; i < 100; i++) {
		series->append(i, sin(0.6f*i));
	}
	// ����ͼ��
	m_chart = new QChart();

	// ���ϵ��
	m_chart->addSeries(series);
	//chart->legend()->hide();		// ����ͼ��

	m_chart->createDefaultAxes();		// ��������ӵ�ͼ��� series ������Ĭ�ϵ�������

									// ��������
	m_chart->setTheme(QChart::ChartThemeDark);

	// ��ͼ��󶨵���ͼ
	ui.widget->setChart(m_chart);
}
QtAudio::~QtAudio()
{
	m_chart->removeAllSeries();
}
