#include "playthread.h"

playthread::playthread()
{

}

void playthread::stop()
{
    stopped=true;
    m_yaoqi.setBrun(false);
    cout<<"stop"<<endl;
}

void playthread::run()
{
    stopped=false;
    m_yaoqi.setBrun(true);
    bool findhwnd;
    RECT rc;
    HWND hwnd = FindWindow(NULL,hwndstr.toStdWString().c_str()); //注意窗口不能最小化
    if (hwnd == NULL)
    {
       cout << "no text " << endl;
       //return 0;
       findhwnd=false;
    }else
        findhwnd=true;
    GetClientRect(hwnd, &rc);
    int count=0;
    m_yaoqi.setBifking(ifkillking);
    m_yaoqi.setBifjoin(ifjoin);
    m_yaoqi.setBifcap(ifascap);
    while(findhwnd&&(!stopped)){
       m_yaoqi.run(hwnd,rc);
       count++;
       emit countsend(count);
    }

}

bool playthread::getIfkillking() const
{
    return ifkillking;
}

void playthread::setIfkillking(bool value)
{
    ifkillking = value;
}

bool playthread::getIfjoin() const
{
    return ifjoin;
}

void playthread::setIfjoin(bool value)
{
    ifjoin = value;
}

QString playthread::getHwndstr() const
{
    return hwndstr;
}

void playthread::setHwndstr(const QString &value)
{
    hwndstr = value;
}

bool playthread::getIfascap() const
{
    return ifascap;
}

void playthread::setIfascap(bool value)
{
    ifascap = value;
}


