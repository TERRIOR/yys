#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>

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

    QObject::connect(&pthread, SIGNAL(countsend(int)), this, SLOT(countuiplus(int)));
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
    if(ui->tabWidget->currentIndex()==3){
        m_bstart=true;
        pthread.setHwndstr(ui->lineEdit->text());
        //m_yaoqi.touchpos(15,700);
        if(ui->checkBox->isChecked())
            pthread.setIfkillking(true);
        else
            pthread.setIfkillking(false);
        if(ui->checkBox_2->isChecked())
            pthread.setIfjoin(true);
        else
            pthread.setIfjoin(false);
        if(ui->checkBox_3->isChecked())
            pthread.setIfascap(true);
        else
            pthread.setIfascap(false);
        pthread.start();
    }else{
        QMessageBox::information(this,tr("sorry"),tr("This function is not open"));
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    m_bstart=true;
    if(pthread.isRunning()){
        pthread.stop();
    }
}

void MainWindow::countuiplus(int count)
{
    //static int count=0;
    //count++;
    cout<<count<<endl;
    ui->label_6->setText(QString::number(count, 10));
    ui->label_7->setText(QString::number(count*4, 10));
}
