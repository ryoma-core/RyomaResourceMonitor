#ifndef DISKGRAPH_H
#define DISKGRAPH_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>


namespace Ui {
class Diskgraph;
}

class Diskgraph : public QWidget
{
    Q_OBJECT

public:
    explicit Diskgraph(QWidget *parent = nullptr);
    ~Diskgraph();

public slots:
    void appendValue(double value);
    void clearGraph();

private:
    Ui::Diskgraph *ui;
    QChartView*  m_view = nullptr;
    QChart*      m_chart = nullptr;
    QLineSeries* m_series = nullptr;
    QValueAxis*  m_axisX = nullptr;
    QValueAxis*  m_axisY = nullptr;

    qint64 m_x = 0;      // x축(시간/샘플 인덱스)
    int    m_window = 60; // 최근 60개만 보이게(원하는 대로)
};

#endif // DISKGRAPH_H
