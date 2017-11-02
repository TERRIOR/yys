#ifndef ACTIVITY_H
#define ACTIVITY_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "point.h"
using namespace cv;
class activity
{
public:
    activity();
    Point getXY(const Mat &finded_img, const Mat &find_img);
private:
    const int match_method=0;
};

#endif // ACTIVITY_H
