#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>

class myEventFilter: public QObject {
  Q_OBJECT
public:
  myEventFilter() {}
  ~myEventFilter() {
  }
protected:
  bool eventFilter(QObject* object, QEvent* event) {
    if(event->type() ==QEvent::MouseButtonRelease) {
      qDebug()<<object;
      return false; // make it unhandled and sent to other filters.
    } else
      return false;
  }
};

#endif // MYEVENTFILTER_H
