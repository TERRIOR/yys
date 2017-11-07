#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //m_yaoqi.touchpos(Point(15,15));
    //获取主屏幕
    //namedWindow("1", CV_WINDOW_AUTOSIZE);
    /*while(1){
        if(1){
            QScreen *screen = QGuiApplication::primaryScreen();
            //抓屏
            QPixmap pix= screen->grabWindow(0);
            QImage img= pix.toImage();
            mat_screen = m_yaoqi.qimage2mat(img);
            imshow("1",mat_screen);
            waitKey(100);
            int sleeptime=calrand(0,5);
            cout<<sleeptime<<endl;
            msleep(1,1000);
        }

    }*/

}


void MainWindow::msleep(int msec,int scare)//自定义Qt延时函数,单位秒
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

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    m_bstart=true;
    //m_yaoqi.touchpos(15,700);
    pthread.start();
}

void MainWindow::on_pushButton_2_clicked()
{
    m_bstart=true;
    if(pthread.isRunning()){
        pthread.stop();
    }
}
