#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H
#include <QThread>
#include "yaoqi.h"
class playthread :public QThread
{
public:
   playthread();
   void stop();
   void  run();
protected:

private:
    volatile bool stopped;
    yaoqi m_yaoqi;
};

#endif // PLAYTHREAD_H
