#include "activity.h"

activity::activity()
{

}

Point activity::match(const Mat &finded_img, const Mat &find_img, const int thread)
{
    Mat result;
    /// Create the result matrix
    const int result_cols =  finded_img.cols -find_img.cols + 1;
    const int result_rows = finded_img.rows - find_img.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    /// Do the Matching and Normalize
    ///用灰度图检测比较快
    matchTemplate( finded_img, find_img, result, match_method );
    //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    cout<<"min:"<<minVal<<"  max:"<<maxVal<<endl;
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    {
        matchLoc = minLoc;
        //最小值是匹配度 大于阈值 不合格
        if (minVal>thread){
            return Point(0,0);
        }
    }
    else
    {
        matchLoc = maxLoc;
        //最小值是匹配度 大于阈值 不合格
        if (minVal<thread){
            return Point(0,0);
        }
    }
    /// Show me what you got
    //pointl=Point( matchLoc.x + find_img.cols , matchLoc.y + find_img.rows );
    //rectangle( imgl1, matchLoc, pointl, Scalar::all(0), 2, 8, 0     );
    return matchLoc;
}

Point activity::getXY(const Mat &finded_img, const Mat &find_img)
{
    Point p= match(finded_img,find_img,1000);
    return Point(p.x + find_img.cols/2 , p.y + find_img.rows/2);
}

bool activity::ifexsite(const Mat &finded_img, const Mat &find_img, const int thread)
{
    Point p= match(finded_img,find_img,thread);
    if(p.x==0&&p.y==0){
        return false;
    }else{
        return true;
    }

}

