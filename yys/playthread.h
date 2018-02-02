#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H
#include <QThread>
#include "yaoqi.h"
class playthread :public QThread
{
    Q_OBJECT

public:
   playthread();
   void stop();
   void  run();
   bool getIfkillking() const;
   void setIfkillking(bool value);

   bool getIfjoin() const;
   void setIfjoin(bool value);

   QString getHwndstr() const;
   void setHwndstr(const QString &value);

   bool getIfascap() const;
   void setIfascap(bool value);

protected:

private:
   QString hwndstr;
   volatile bool stopped;
   yaoqi m_yaoqi;
    bool ifkillking;
    bool ifjoin;
    bool ifascap;
signals:
    void countsend(int count);
};

#endif // PLAYTHREAD_H
