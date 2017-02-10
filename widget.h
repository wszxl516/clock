#ifndef WIDGET_H
#define WIDGET_H
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>
#include <QFont>
#include <QTime>
#include <QString>
#include <QPolygonF>
#include <QKeyEvent>
#include <QTimer>
#include <QPolygonF>
#include <QPointF>
#include <QPainterPath>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QString getTime(QString ss);
    void keyPressEvent(QKeyEvent *event);
private:
    bool m_Drag;
    QPoint  m_DragPosition;
    QPainter *QP;
    int hh,mm,ss;
    QString timeNow;
    QTimer *t;
    QPolygonF *hc;
    QPolygonF *mc;
    QPolygonF *sc;
    QVector<QPointF> *vec;
    QPainterPath paths;
    QPainterPath pathm;
    QPainterPath pathh;
    int fw,fh;

};

#endif // WIDGET_H
