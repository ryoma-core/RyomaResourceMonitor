#include "diskgraph.h"
#include "ui_diskgraph.h"

#include <QVBoxLayout>
#include <QPainter>

Diskgraph::Diskgraph(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Diskgraph)
{
    ui->setupUi(this);
    //1)선(데이터)
    m_series = new QLineSeries(this);
    m_series->setName("DISK %");

    //2)차트(도화지)
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("DISK Usage");
    m_chart->legend()->setVisible(true);

    //3) 축
    m_axisX = new QValueAxis();
    m_axisX->setTitleText("Time(s)");
    m_axisX->setRange(0, m_window);
    m_axisX->setLabelFormat("%d");

    m_axisY = new QValueAxis();
    m_axisY->setTitleText("%");
    m_axisY->setRange(0, 100);
    m_axisY->setLabelFormat("%.0f");

    m_chart->addAxis(m_axisX,Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    //4) 뷰(화면 위젯)
    m_view = new QChartView(m_chart,ui->chartHost);
    m_view->setRenderHint(QPainter::Antialiasing);

    //5) 레이아웃에 붙이기
    auto *hostLayout = ui->chartHost->layout();
    if (!hostLayout) {
        auto *v = new QVBoxLayout(ui->chartHost);
        v->setContentsMargins(0,0,0,0);
        v->setSpacing(0);
        ui->chartHost->setLayout(v);
        hostLayout = v;
    }
    hostLayout->addWidget(m_view);

    ui->chartHost->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Diskgraph::~Diskgraph()
{
    delete ui;
}

void Diskgraph::appendValue(double value)
{
    //값 방어
    if(value < 0) value = 0;
    if(value > 100) value = 100;

    //점 추가
    m_series->append(m_x,value);
    ++m_x;

    //최근 m_window개만 유지 ( 무한히 쌓이면 메모리 터짐)
    const int count = m_series->count();
    if(count > m_window)
    {
        m_series->removePoints(0, count - m_window);
    }

    if(m_x > m_window) {
        m_axisX->setRange(m_x - m_window, m_x);
    } else {
        m_axisX->setRange(0,m_window);
    }
}

void Diskgraph::clearGraph()
{
    m_series->clear();
    m_x = 0;
}
