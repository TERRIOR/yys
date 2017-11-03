#ifndef YAOQI_H
#define YAOQI_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "activity.h"
class yaoqi:public activity
{
public:
    yaoqi();
    void start();
    void init();
    void end();
private:
    int m_imodel;
    int m_icount;
    bool m_bstart;
};

#endif // YAOQI_H
