#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QWidget>
#include<QObject>
#include<QPainter>
#include<QMouseEvent>
#include<QLineEdit>
#include<QLayout>
class DoubleSlider : public QWidget
{
    Q_OBJECT
public:
    DoubleSlider(QWidget* parent = 0);
    void setRange(float min, float max);
    void setSingleStep(float step);
    void setMaxRange(float range);
    void setMinRange(float range);


    enum State{ MinHandle,MaxHandle,None};

    float minValue() const;
    float maxValue() const;

    float minRange() const;
    float maxRange() const;

public slots:
    void setLabel(const QString& label);
    void setMaxValue(float val);
    void setMinValue(float val);

signals:
    void minValueChanged(float);
    void maxValueChanged(float);

private:
    float m_min;
    float m_max;
    float m_singleStep;

    float m_minValue;
    float m_maxValue;

    QRect minHandleRegion;
    QRect maxHandleRegion;

    State m_state;

    QString m_label;

protected:
    void paintEvent(QPaintEvent* event);
    void paintColoredRect(QRect rect, QColor color, QPainter* painter);
    void paintValueLabel(QPainter* painter);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void keyPressEvent(QKeyEvent *event);
    void leaveEvent(QEvent* event);
};

#endif // DOUBLESLIDER_H
