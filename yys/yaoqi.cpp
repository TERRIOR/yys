#include "yaoqi.h"

yaoqi::yaoqi()
{

}

void yaoqi::start()
{

}

void yaoqi::run()
{
    Mat findimg,findimg2;

    while(getBrun()){
        init();
        //cout<<"yaoqi start"<<endl;
        msleep(100,1);
        if(m_binited){
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
        }


    }

}

void yaoqi::init()
{
    m_mscreen=getscreen();
    Mat martchtop=imread("yys//step1//kuangdw3.png");
    toppoint=match(m_mscreen,martchtop,10000);

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



