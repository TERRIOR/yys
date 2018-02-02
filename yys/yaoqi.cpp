#include "yaoqi.h"
#include<QMessageBox>
yaoqi::yaoqi()
{

}

void yaoqi::start()
{

}

void yaoqi::run(HWND hwnd,RECT rc)
{

    //init();
    //HDC hDC = GetWindowDC(hwnd);
    int count=0;
    //int warn=0;
    bool findking=false;
    Mat findimg,findimg2;
    Point matchp,matchp2;
    Point mid2=Point(830,400);
    //Point mid=Point(toppoint.x+830,toppoint.y+400);
    Point startbattle=Point(790,480);//组队时，开始按键坐标
    Size startsize=Size(130,40);//随机域
    Point joinbattle=Point(106,222);//组队时，加入按键坐标1
    Point joinbattle2=Point(180,222);//组队时，加入按键坐标2
    Size joinsize=Size(30,30);//随机域
    Point preparepoint=Point(880,450);//组队时，准备按键坐标
    Size preparesize=Size(100,100);//准备随机域
    cout<<"hunshi"<<endl;
    findimg=imread("yys//step2//shengli3.png");
    resize(findimg,findimg,Size(findimg.cols/3,findimg.rows/3),0,0,INTER_LINEAR);
    cout<<findimg.channels()<<"  "<<findimg.depth()<<" "<<findimg.type()<<endl;
    while(1){
        //refresh();
        if(!getBrun()){
            break;
        }
        //m_playroi=imread("yys//yesheng5.png");
        refresh2(hwnd,rc);
        //imshow("da",m_playroi);
        cout<<m_playroi.rows<<"  "<<m_playroi.cols<<" "<<m_playroi.empty()<<endl;
        //waitKey(calrand(200,500));
        Sleep(300);

        if(m_playroi.rows<150&&m_playroi.cols<250){
            cout<<"mined"<<endl;
            continue;
        }
        cout<<"step1"<<endl;
        matchp=match(m_playroi,findimg,10);
        if(ifexsite( matchp)){
            cout<<"step1:  "<<matchp.x<<" "<<matchp.y<<endl;
            //touchpos(getrandxy( mid,Size(300,300)));
            Sleep(calrand(0,500));
            MouseLeftClick(hwnd,getrandxy( mid2,Size(300,300)));
            break;
        }


    }
    findimg2=imread("yys//step2//jiangli3.png");
    resize(findimg2,findimg2,Size(findimg2.cols/3,findimg2.rows/3),0,0,INTER_LINEAR);
    Point p=getrandxy( mid2,Size(290,250));
    while(1){
        if(!getBrun()){
            break;
        }
        refresh2(hwnd,rc);
        cout<<"step2"<<endl;
        Sleep(calrand(200,500));
        MouseLeftClick(hwnd,p);
        if(m_playroi.rows<150&&m_playroi.cols<250){
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
    Sleep(1000);
    if(m_bifcap){
        Sleep(calrand(4000,6000));
        MouseLeftClick(hwnd,getrandxy( startbattle,startsize));
    }
    if(m_bifking){
        cout<<"king"<<endl;
        int countking=0;
        Mat findmatking=imread("yys//step2//king2.png");
        resize(findmatking,findmatking,Size(findmatking.cols/3,findmatking.rows/3),0,0,INTER_LINEAR);
        while(1)
        {
            if(!getBrun()){
                break;
            }
            refresh2(hwnd,rc);
            Sleep(300);
            if(m_playroi.rows<150&&m_playroi.cols<250){
                cout<<"mined"<<endl;
                continue;
            }
            cout<<"finding king"<<endl;
            matchp=match(m_playroi,findmatking,20);
            countking++;
            if(ifexsite( matchp)){
                //播放声音提醒
                cout<<"find the king!"<<endl;
                findking=true;
                QApplication::beep();
                break;
            }
            if(countking>3)
                break;
        }
    }
    if(m_bifjoin&&(!findking)){
        cout<<"join"<<endl;
        int countcaptain=0;
        bool ifmoren=true;//是否默认
        Sleep(calrand(200,1000));
        Mat findmatcap=imread("yys//step2//gou.png");
        Mat findmatcap2=imread("yys//step2//moren.png");
        resize(findmatcap,findmatcap,Size(findmatcap.cols/3,findmatcap.rows/3),0,0,INTER_LINEAR);
        resize(findmatcap2,findmatcap2,Size(findmatcap2.cols/3,findmatcap2.rows/3),0,0,INTER_LINEAR);
        while(1)
        {
            if(!getBrun()){
                break;
            }
            refresh2(hwnd,rc);
            Sleep(500);
            if(m_playroi.rows<150&&m_playroi.cols<250){
                cout<<"mined"<<endl;
                continue;
            }
            cout<<"step3"<<endl;
            matchp=match(m_playroi,findmatcap,100);
            matchp2=match(m_playroi,findmatcap2,100);
            countcaptain++;
            cout<<matchp2.x<<" "<<matchp2.y<<endl;


            //gou2具有更高的优先级 是默认模式的触发按钮 所以先判断默认点
            if(ifexsite(matchp2)){
                Sleep(calrand(0,1000));
                MouseLeftClick(hwnd,getrandxy( joinbattle2,joinsize));    
                cout<<"moren"<<endl;
                ifmoren=true;//搜索到二加入 ，不是默认模式
                break;
            }
            //matchp=match(m_playroi,findmatcap,100);
            if(ifexsite( matchp)){  
                Sleep(calrand(0,1000));
                MouseLeftClick(hwnd,getrandxy( joinbattle,joinsize));
                //Sleep(calrand(200,700));
                //MouseLeftClick(hwnd,getrandxy( joinbattle,joinsize));
                cout<<"bu moren"<<endl;
                ifmoren=false;//搜索到二加入 ，不是默认模式
                break;
            }
            if(countcaptain>20){
                ifmoren=true;//没有搜索到二加入，所以是默认模式
                break;
            }
        }
        if(!ifmoren){
            Mat findmatzb=imread("yys//step2//zhunbei.png");
            resize(findmatzb,findmatzb,Size(findmatzb.cols/3,findmatzb.rows/3),0,0,INTER_LINEAR);
            while(1)
            {
                if(!getBrun()){
                    break;
                }
                refresh2(hwnd,rc);
                Sleep(500);
                if(m_playroi.rows<150&&m_playroi.cols<250){
                    cout<<"mined"<<endl;
                    continue;
                }
                cout<<"zhunbei step"<<endl;
                matchp=match(m_playroi,findmatzb,10);
                if(ifexsite( matchp)){
                    Sleep(calrand(0,1000));
                    MouseLeftClick(hwnd,getrandxy( preparepoint,preparesize));
                    break;
                }
            }
        }

    }
    //ReleaseDC(NULL, hDC);
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

bool yaoqi::getBifking() const
{
    return m_bifking;
}

void yaoqi::setBifking(int bifking)
{
    m_bifking = bifking;
}

bool yaoqi::getBifjoin() const
{
    return m_bifjoin;
}

void yaoqi::setBifjoin(bool bifjoin)
{
    m_bifjoin = bifjoin;
}

bool yaoqi::getBifcap() const
{
    return m_bifcap;
}

void yaoqi::setBifcap(bool bifcap)
{
    m_bifcap = bifcap;
}





