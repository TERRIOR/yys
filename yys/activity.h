#ifndef ACTIVITY_H
#define ACTIVITY_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QtCore>
#include <qwidget.h>
#include <QApplication>
#include <QtGui>
#include <QThread>
#include <QObject>
#include <QScreen>
#include <QTimer>
#include <QDateTime>
#include "iostream"
#include "point.h"
#pragma comment(lib,"user32.lib")
using namespace cv;
using namespace std;
class activity
{
public:
    activity();

    Mat getscreen();

    Mat getmask(Size size1,Size size2,Point p);
    Mat getplaymat(Size size2, Point p);
    void msleep(int msec,int scare);
    void touchpos(Point p);
    Point match(const Mat &finded_img, const Mat &find_img,const int thread);//返回匹配点坐标
    Point getXY(const Mat &finded_img, const Mat &find_img,int thread);//返回匹配框的中点
    Point getxychamfer(Mat &finded_img, Mat &find_img);
    Mat qimage2mat(const QImage& qimage);//qimage转IMG 格式
    bool ifexsite(Point p);//检测图像是否存在
    bool ifimgex(Mat &finded_img,Mat &find_img);
    bool getBrun() const;
    void setBrun(bool brun);
    void movetopos(Point p,int i);
    int calrand(int a,int b);
    Point getrandxy(Point p,Size size);
    void touchfromstring(String s,int thread);
    void refresh();
protected:
    Mat m_mscreen;
    Mat m_mask;
    Mat m_playroi;
    Point toppoint;
    Size screen_size;
    const int screenx=1204;//屏幕的分辨率
    const int screeny=680;//同上
    const int button_directory=110;
private:
    const int match_method=0;
    bool m_brun;

};

#endif // ACTIVITY_H
