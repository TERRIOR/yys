#include "activity.h"

activity::activity()
{
    screen_size.width=screenx;
    screen_size.height=screeny;
}

Mat activity::getscreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    //抓屏
    QPixmap pix= screen->grabWindow(0);
    QImage img= pix.toImage();
    return qimage2mat(img);
}

Mat activity::getscreen2(HWND hwnd, RECT rc)
{
    /*
    HDC hdcScreen = GetDC(NULL);
    HDC hdc = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);


    //复制
    SelectObject(hdc, hbmp);
    */
    //PrintWindow(hwnd, hdc, PW_CLIENTONLY);
   //PW_CLIENTONLY：Only the client area of the window is copied to hdcBlt.
   //By default, the entire window is copied.
   //PW_CLIENTONLY表示仅仅拷贝窗口的客户区域，而默认情况下，执行printwindow会拷贝整个窗口

    Mat mat1=CaptureScreen(false,hwnd);;
    cvtColor(mat1 , mat1 , CV_RGBA2RGB);
    return mat1;
}
Mat activity::CaptureScreen(bool FullScreen, HWND hwnd)
{
    HDC hDC;
    if(FullScreen)
        hDC = GetDC(NULL); //Get full screen
    else
    {
        hDC = GetWindowDC(hwnd); //Now get it's DC handle
    }

    HDC hMemDC = CreateCompatibleDC(hDC);
    RECT r;
    GetWindowRect(hwnd,&r); //need this for Form
    SIZE size;
    if(FullScreen)
    {
        size.cx = GetSystemMetrics(SM_CXSCREEN);
        size.cy = GetSystemMetrics(SM_CYSCREEN);
    }
    else
    {
        size.cx = r.right-r.left;
        size.cy = r.bottom-r.top;
    }

    //most of the remaining code is normal GDI stuff

    HBITMAP hBitmap = CreateCompatibleBitmap(hDC, size.cx, size.cy);
    if (hBitmap)
    {
        HBITMAP hOld = (HBITMAP) SelectObject(hMemDC, hBitmap);//更换
        BitBlt(hMemDC, 0, 0, size.cx, size.cy, hDC, 0, 0, SRCCOPY);//
        //StretchBlt(hMemDC, 0, 0, size.cx/2, size.cy/2, hDC, 0, 0,size.cx, size.cy, SRCCOPY);
        SelectObject(hMemDC, hOld);//换回来
        Mat mat;
        HBitmapToMat(hBitmap,mat);
        DeleteObject(hBitmap);
        DeleteObject(hOld);
        int brelease1=DeleteDC(hMemDC);
        int brelease2=ReleaseDC(hwnd,hDC);
        if(brelease2==0)
            cout<<"not release dc"<<endl;
        if(brelease1==0)
            cout<<"not del dc"<<endl;
        return mat;
    }


}
BOOL activity::HBitmapToMat(HBITMAP& _hBmp,Mat& _mat)

{
    BITMAP bmp;
    GetObject(_hBmp,sizeof(BITMAP),&bmp);
    int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;
    int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
    Mat v_mat;
    v_mat.create(cvSize(bmp.bmWidth,bmp.bmHeight), CV_MAKETYPE(CV_8U,nChannels));
    GetBitmapBits(_hBmp,bmp.bmHeight*bmp.bmWidth*nChannels,v_mat.data);
    _mat=v_mat;
    return TRUE;
}

Mat activity::getmask(Size size1, Size size2, Point p)
{
    Mat mask=Mat::zeros(size1, CV_8UC1);
    rectangle(mask, p, size2, Scalar(255), -1, 8);
    return mask;
}

Mat activity::getplaymat(Size size2, Point p)
{
    m_playroi=m_mscreen(Rect(p.x,p.y,size2.width,size2.height));
    return m_playroi;
}

void activity::msleep(int msec, int scare)
{
    QDateTime last = QDateTime::currentDateTime();
    QDateTime now;
    while (1)
    {
        now = QDateTime::currentDateTime();
        if (last.msecsTo(now)/scare >= msec)
        {
            break;
        }
    }
}

void activity::touchpos(Point p)
{
    if(ifexsite(p)){
        qDebug()<<"mouse clicked";

        movetopos(p,10);
        Sleep(calrand(0,100));
        mouse_event(MOUSEEVENTF_LEFTDOWN ,0,0,0,0);
        Sleep(calrand(0,10));
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    }
}
void activity::MouseLeftClick(HWND gameh,Point p)
{
    if(ifexsite(p)){
        qDebug()<<"mouse clicked";
        Sleep(calrand(0,10));
        LPARAM lparam = MAKELPARAM(p.x,p.y); //x坐标，y坐标
        LRESULT result =::SendMessage(gameh,WM_LBUTTONDOWN,VK_LBUTTON,lparam);
        Sleep(calrand(0,20));
        LRESULT result1 =::SendMessage(gameh,WM_LBUTTONUP,0,lparam);
        //TRACE("鼠标按下%d,弹起%d",result,result1);
    }

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
    //cout<<matchLoc.x<<" "<<matchLoc.y<<endl;
    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    {
        matchLoc = minLoc;
        //最小值是匹配度 大于阈值 不合格
        if (maxVal/minVal<thread){
            return Point(0,0);
        }
    }
    else
    {
        matchLoc = maxLoc;
        //最小值是匹配度 大于阈值 不合格
        if (maxVal/minVal<thread){
            return Point(0,0);
        }
    }
    /// Show me what you got
    //pointl=Point( matchLoc.x + find_img.cols , matchLoc.y + find_img.rows );
    //rectangle( imgl1, matchLoc, pointl, Scalar::all(0), 2, 8, 0     );
    return matchLoc;
}

Point activity::getXY(const Mat &finded_img, const Mat &find_img, int thread)
{
    Point p= match(finded_img,find_img,thread);
    if(ifexsite(p)){
        return Point(p.x + find_img.cols/2 , p.y + find_img.rows/2);
    }else{
        return p;
    }

}

Point activity::getxychamfer(Mat &finded_img, Mat &find_img)
{
    vector<vector<Point> > results;
    vector<float> costs;
    int x,y;
    int best;
    best= chamerMatching( finded_img, find_img, results, costs );
    if(best<0){
        return Point(0,0);
    }else{
        size_t i, n = results[best].size();
        for( i = 0; i < n; i++ )
        {
            Point pt = results[best][i];
            if( pt.inside(Rect(0, 0, finded_img.cols, finded_img.rows)) ){
                x+=pt.x;
                y+=pt.y;
            }
        }
        return Point(x/n,y/n);
    }
}

bool activity::ifexsite(Point p)
{
    //Point p= match(finded_img,find_img,thread);
    if(p.x==0&&p.y==0){
        return false;
    }else{
        return true;
    }

}

bool activity::ifimgex( Mat &finded_img, Mat &find_img)
{
    vector<vector<Point> > results;
    vector<float> costs;
    int best;
    Mat gray1(finded_img.size(), CV_8UC1),gray2(find_img.size(), CV_8UC1);
    cvtColor(finded_img,gray1,CV_RGB2GRAY);
    cvtColor(find_img,gray2,CV_RGB2GRAY);
    //finded_img.copyTo(gray1);
    //find_img.copyTo(gray2);
    //gray1.convertTo(gray1,CV_8UC1);
    //gray2.convertTo(gray2,CV_8UC1);
    best = chamerMatching( gray1, gray2, results, costs );
    cout<<"chamer"<<endl;
    if(best<0){
        return false;
    }else{
        return true;
    }
}

bool activity::getBrun() const
{
    return m_brun;
}

void activity::setBrun(bool brun)
{
    m_brun = brun;
}

void activity::movetopos(Point p ,int i)
{
    POINT pstart;
    GetCursorPos(&pstart);//获取鼠标坐标
    //cout<<pstart.x<< "  "<<pstart.y<<endl;
    //cout<<p.x<< "  "<<p.y<<endl;
    float stepx,stepy,px,py;
    stepx=(float)(p.x-pstart.x)/i;
    stepy=(float)(p.y-pstart.y)/i;
    //cout<<stepx<< "  "<<stepy<<endl;
    px=pstart.x;
    py=pstart.y;
    while(i){
        i--;
        px=px+stepx;
        py=py+stepy;
        //Sleep(1);
        SetCursorPos(px, py);
        //cout<<px<< "  "<<py<<endl;
    }
    SetCursorPos(p.x, p.y);
}

int activity::calrand(int a, int b)
{
    return (rand() % (b-a+1))+ a;
}

Point activity::getrandxy(Point p, Size size)
{
    int lengthx=size.width*0.3;
    int lengthy=size.height*0.3;
    int offsetx=calrand(-lengthx,lengthx);
    int offsety=calrand(-lengthy,lengthy);
    return Point(p.x+offsetx,p.y+offsety);
}

void activity::touchfromstring(String s, int thread)
{
    Mat findimg=imread(s);
    Point p=getxychamfer(m_mscreen,findimg);
    if(ifexsite(p)){
        p.x=toppoint.x+p.x;
        p.y=toppoint.y+p.y;
        touchpos( getrandxy(p,findimg.size()));
    }

}

void activity::refresh()
{
    m_mscreen=getscreen();
    m_playroi=getplaymat(screen_size,toppoint);
}

void activity::refresh2(HWND hwnd,RECT rc){
    //getscreen2(hwnd,rc);
    m_playroi=getscreen2(hwnd,rc);
    resize(m_playroi,m_playroi,Size(m_playroi.cols/3,m_playroi.rows/3),0,0,INTER_LINEAR);
}
Mat activity::qimage2mat(const QImage& qimage)
{
    Mat mat =Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
    Mat mat2 = Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}
