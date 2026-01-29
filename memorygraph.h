#ifndef MEMORYGRAPH_H
#define MEMORYGRAPH_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

namespace Ui {
class Memorygraph;
}

class Memorygraph : public QWidget
{
    Q_OBJECT

public:
    explicit Memorygraph(QWidget *parent = nullptr);
    ~Memorygraph();

public slots:
    void appendValue(double value);
    void clearGraph();

private:
    Ui::Memorygraph *ui;
    QChartView*  m_view = nullptr;
    QChart*      m_chart = nullptr;
    QLineSeries* m_series = nullptr;
    QValueAxis*  m_axisX = nullptr;
    QValueAxis*  m_axisY = nullptr;

    qint64 m_x = 0;      // x축(시간/샘플 인덱스)
    int    m_window = 60; // 최근 60개만 보이게(원하는 대로)
};

#endif // MEMORYGRAPH_H
