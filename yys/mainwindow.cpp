#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    namedWindow("1", CV_WINDOW_AUTOSIZE);
    ui->setupUi(this);
    Mat mat1,mat2;
    mat1=imread(".\\yys\\3.png");
    mat2=imread(".\\yys\\step2\\select.png");
    Point pstart= m_yaoqi.match(mat1,mat2,1000);
    if(pstart.x==0&&pstart.y==0){
        cout<<"dd"<<endl;
    }else{
        Point pointl=Point( pstart.x + mat2.cols , pstart.y + mat2.rows );
        rectangle( mat1, pstart, pointl, Scalar::all(0), 2, 8, 0);
    }

    imshow("1",mat1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
