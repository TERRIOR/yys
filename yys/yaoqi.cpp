#include "yaoqi.h"

yaoqi::yaoqi()
{

}

void yaoqi::start()
{

}

void yaoqi::run()
{
    bool findhwnd;
    RECT rc;
    HWND hwnd = FindWindow(NULL,TEXT("夜神模拟器")); //注意窗口不能最小化
    if (hwnd == NULL)
    {
       cout << "no text " << endl;
       //return 0;
       findhwnd=false;
    }else findhwnd=true;
    GetClientRect(hwnd, &rc);
    Mat findimg,findimg2;
    Point matchp;
    int count=0;
    init();
    while(getBrun()&&findhwnd){


        msleep(100,1);
        if(1){
            Point mid2=Point(830,400);
            Point mid=Point(toppoint.x+830,toppoint.y+400);
            cout<<"hunshi"<<endl;
            findimg=imread("yys//step2//shengli3.png");

            cout<<findimg.channels()<<"  "<<findimg.depth()<<" "<<findimg.type()<<endl;
            while(1){
                //refresh();
                refresh2(hwnd,rc);
                //imshow("da",m_playroi);
                cout<<m_playroi.rows<<"  "<<m_playroi.cols<<" "<<m_playroi.empty()<<endl;
                //waitKey(100);

                msleep(calrand(200,500),1);

                if(m_playroi.rows<400&&m_playroi.cols<500){
                    cout<<"mined"<<endl;
                    continue;
                }
                cout<<"step1"<<endl;
                matchp=match(m_playroi,findimg,10);
                if(ifexsite( matchp)){
                    cout<<"step1:  "<<matchp.x<<" "<<matchp.y<<endl;
                    //touchpos(getrandxy( mid,Size(300,300)));
                    MouseLeftClick(hwnd,getrandxy( mid2,Size(300,300)));
                    break;
                }


            }
            findimg2=imread("yys//step2//jiangli3.png");
            Point p=getrandxy( mid2,Size(290,250));
            while(1){
                //refresh();
                refresh2(hwnd,rc);
                cout<<"step2"<<endl;
                msleep(calrand(200,500),1);
                //touchpos(getrandxy( p,Size(80,80)));
                MouseLeftClick(hwnd,getrandxy( p,Size(60,60)));
                if(m_playroi.rows<400&&m_playroi.cols<500){
                    cout<<"mined"<<endl;
                    continue;
                }
                matchp=match(m_playroi,findimg2,10);
                count++;
                if(ifexsite(matchp))
                {
                  count=18;
                }
                if(count>20){
                    cout<<"step2:  "<<matchp.x<<" "<<matchp.y<<endl;
                    count=0;
                    break;
                }
            }


        }
        /*if(m_binited){
            //获得妖气封印对应的坐标
            touchpos(getrandxy(getselectpos(2),Size(button_directory,button_directory)));
            msleep(calrand(0,10),100);
            refresh();
            Point p,p2;
            p.x=toppoint.x+238;
            p.y=toppoint.y+553;
            findimg=imread("yys//step2//join.png");
            Mat team=m_playroi(Rect(373,155,234,368));
            findimg2=imread("yys//step2//haifangzu.png");
            int i=50,j=50;
            //;
            p2.x=0;
            p2.y=0;
            while (!ifexsite(p2)&&j) {
                while(!ifexsite( match(m_mscreen,findimg,100))&&i){
                    ifimgex(m_mscreen,findimg);
                    touchpos(getrandxy( p,Size(203,62)));
                    cout<<"unfind!"<<endl;
                    refresh();
                    i--;
                }
                j--;
                p2=match(team,findimg2,100);
                if(ifexsite(p2)){

                    Point touchjoin(p2.x+602+373+toppoint.x,p2.y+30+155+toppoint.y);
                    touchpos(getrandxy(touchjoin,Size(findimg.cols,findimg.rows)));
                }
            }


            cout<<"find join!"<<endl;
            msleep(calrand(0,100),1000);
            m_binited=false;

        }*/


    }

}

void yaoqi::init()
{
    m_mscreen=getscreen();
    Mat martchtop=imread("yys//step1//2.png");
    toppoint=match(m_mscreen,martchtop,100);

    //cout<<m_mscreen.cols<<"  "<<m_mscreen.rows<<endl;
    if(ifexsite(toppoint)){
        toppoint.y=toppoint.y+30;
        //m_mask=getmask(martchtop.size(),screen_size,toppoint );
        m_playroi=getplaymat(screen_size,toppoint);
        cout<<"cun zai"<<endl;
        m_binited=true;
        waitKey(calrand(0,10));
    }else{
        cout<<"bu cun zai"<<endl;
        m_binited=false;
    }

}

void yaoqi::end()
{

}
Point yaoqi::getselectpos(int i)
{
    Mat mat_directory=imread("yys//step2//select2.png");
    //imshow("wwwwwww",mat_directory);
    //waitKey(10);
    Point p;
    p=match(m_playroi,mat_directory,100);
    cout<<p.x<< "  "<<p.y<<endl;
    if(ifexsite(p)){
        Point touchpoint;
        touchpoint.y=toppoint.y+p.y+mat_directory.rows/2;
        touchpoint.x=toppoint.x+p.x+i*mat_directory.cols/8-mat_directory.cols/16;
        cout<<touchpoint.x<< "  "<<touchpoint.y<<endl;
        return touchpoint;
    }else{
        return p;
    }
}



