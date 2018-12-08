#ifndef CALLOUT_H
#define CALLOUT_H
#include<QDialog>
#include<QWidget>
#include <QtWidgets/QGridLayout>
#include<QLabel>
#include<QDebug>
class callout : public QDialog
{
    Q_OBJECT
public:
    callout(QWidget *parent = nullptr);
    QLabel *m_label = nullptr;

private:
    QGridLayout *m_layout = nullptr;
protected:
   void mouseDoubleClickEvent(QMouseEvent *event);
signals:
     void HideCallout();
public slots:
};

#endif // CALLOUT_H
