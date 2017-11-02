#include "activity.h"

activity::activity()
{

}

Point activity::getXY(const Mat &finded_img, const Mat &find_img)
{
    //int x_size=find_img.size().width;
    //int y_size=find_img.size().height;
    Mat result;
    /// Create the result matrix
    const int result_cols =  finded_img.cols -find_img.cols + 1;
    const int result_rows = finded_img.rows - find_img.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    /// Do the Matching and Normalize
    ///用灰度图检测比较快
    matchTemplate( finded_img, find_img, result, match_method );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
      { matchLoc = minLoc; }
    else
      { matchLoc = maxLoc; }
    /// Show me what you got
    //pointl=Point( matchLoc.x + find_img.cols , matchLoc.y + find_img.rows );
    //rectangle( imgl1, matchLoc, pointl, Scalar::all(0), 2, 8, 0     );
    return Point(matchLoc.x + find_img.cols/2 , matchLoc.y + find_img.rows/2);

}

