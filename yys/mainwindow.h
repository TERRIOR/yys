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
#include "yaoqi.h"
namespace Ui {
class MainWindow;
}
using namespace cv ;
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    yaoqi m_yaoqi;
};

#endif // MAINWINDOW_H
