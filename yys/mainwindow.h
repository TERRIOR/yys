#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include <QMainWindow>
#include <QtCore/qpoint.h>
#include <QtGui/qwindowdefs.h>
#include <QThread>
#include <QObject>
#include <QScreen>
#include <QTimer>
#include "yaoqi.h"
#include "qcursor.h"
#include <QDateTime>
#include <time.h>
#include <stdlib.h>
#include <playthread.h>

namespace Ui {
class MainWindow;
}
using namespace cv ;
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void msleep(int msec,int scare);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void countuiplus(int count);
private:
    string editstr;
    playthread pthread;
    Ui::MainWindow *ui;
    yaoqi m_yaoqi;
    bool m_bstart=false;
    Mat mat_screen;
};

#endif // MAINWINDOW_H
