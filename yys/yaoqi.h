#ifndef YAOQI_H
#define YAOQI_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "activity.h"
#include<QThread>
#include<QDebug>
#include <QDateTime>
#include <iostream>
#include <QTimer>
using namespace cv;
using namespace std;
class yaoqi:public activity
{
public:
    yaoqi();
    void start();
    void run(HWND hwnd, RECT rc);
    void init();//获取游戏区域
    void end();

    Point getselectpos(int i);

    bool getBifking() const;
    void setBifking(int bifking);

    bool getBifjoin() const;
    void setBifjoin(bool bifjoin);

    bool getBifcap() const;
    void setBifcap(bool bifcap);

private:

    bool m_bifking;
    bool m_bifjoin;
    bool m_bifcap;
    int m_imodel;
    int m_icount;
    bool m_binited=false;
    //bool m_bstart;

};

#endif // YAOQI_H
