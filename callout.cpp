#include "callout.h"

callout::callout(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    m_layout = new QGridLayout();
    m_label = new QLabel();
    m_layout->addWidget(m_label);
    m_label->setText("dddddddddddddd");
    this->setLayout(m_layout);
}

void callout::mouseDoubleClickEvent(QMouseEvent *event){
    qDebug()<<"ffffffffffffffffffffffff";
    emit HideCallout();
}
