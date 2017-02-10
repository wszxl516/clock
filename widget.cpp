#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(400,400);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    vec = new QVector<QPointF>;
    vec->append(QPointF(-10,-10));
    vec->append(QPointF(3,-3));
    vec->append(QPointF(80,80));
    vec->append(QPointF(-3,3));
    hc = new QPolygonF(*vec);
    vec->clear();

    vec->append(QPointF(-10,-10));
    vec->append(QPointF(2,-2));
    vec->append(QPointF(95,95));
    vec->append(QPointF(-2,2));
    mc = new QPolygonF(*vec);
    vec->clear();

    vec->append(QPointF(-10,-10));
    vec->append(QPointF(2,-2));
    vec->append(QPointF(105,105));
    vec->append(QPointF(-2,2));
    sc = new QPolygonF(*vec);
    paths.addPolygon(*sc);
    pathm.addPolygon(*mc);
    pathh.addPolygon(*hc);
    delete vec;

    QP =new QPainter();
    t =new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(update()));
    t->start(1000);
}

Widget::~Widget()
{
delete QP;
delete t;
delete sc;
delete mc;
delete hc;

}
void Widget::paintEvent(QPaintEvent *event)
{
event->accept();
QP->begin(this);
QP->setPen(QPen(QColor(0,0,0,0),1));
QP->setBrush(QColor(0,0,0,100));
QP->drawEllipse(0,0,400,400);


QP->translate(200,200);
QP->setFont(QFont("msyh.ttf",16,QFont::Bold));
QP->setPen(QPen(QColor(240,240,240,255),1));
timeNow = getTime("hh:mm:ss");
fw =QP->fontMetrics().width(timeNow);
fh =QP->fontMetrics().height();
QP->drawText(0-fw/2,100,fw,fh,Qt::AlignCenter,timeNow);
QP->rotate(-135);
QP->save();
for(int i=0;i<=60;i++)
{
    QP->rotate(6);
    QP->setPen(QPen(QColor(250,250,250,250),1));
    QP->drawLine(130,130,135,135);
    if(i%5==4)
    {
        QP->setPen(QPen(QColor(250,250,250,255),2));
        QP->drawLine(120,120,135,135);

    }
}
hh =getTime("hh").toInt();
mm =getTime("mm").toInt();
ss =getTime("ss").toInt();

QP->restore();
QP->save();
QP->rotate(mm/2+hh*30);
QP->setPen(QPen(QColor(0,0,255,200),1));
QP->drawConvexPolygon(*hc);
QP->fillPath(pathh,QBrush(QColor(0,0,255,200)));


QP->restore();
QP->save();
QP->rotate(ss/10+mm*6);
QP->setPen(QPen(QColor(0,255,0,200),1));
QP->drawConvexPolygon(*mc);
QP->fillPath(pathm,QBrush(QColor(0,255,0,200)));

QP->restore();
QP->save();
QP->rotate(ss*6);
QP->setPen(QPen(QColor(255,0,0,200),1));
QP->drawConvexPolygon(*sc);
QP->fillPath(paths,QBrush(QColor(255,0,0,200)));
QP->restore();
QP->end();
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_Drag = true;
        m_DragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_Drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }

}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_Drag = false;
    event->accept();
}
QString Widget::getTime(QString timeFormat)
{
   QDateTime date_time = QDateTime::currentDateTime();
   QString timeString=date_time.toString(timeFormat);
   return timeString;
}
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
        QApplication::exit(0);
}
