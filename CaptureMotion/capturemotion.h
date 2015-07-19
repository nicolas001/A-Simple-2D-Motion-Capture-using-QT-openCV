#ifndef CAPTUREMOTION_H
#define CAPTUREMOTION_H

#include <QMainWindow>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "pointobject.h"
#include <body.h>


using namespace std;

namespace Ui {
class CaptureMotion;
}

class CaptureMotion : public QMainWindow
{
    Q_OBJECT

public:
    explicit CaptureMotion(QWidget *parent = 0);
    void calibrateValue();

    ~CaptureMotion();

private slots:

    void on_BarhsvMin_sliderMoved(int position);
    void on_checkStart_clicked(bool checked);
    void on_btnTerminar_clicked();
    void on_btnStartCC_clicked();
    void on_btnDoneCC_clicked();

private:
    Ui::CaptureMotion *ui;

    int m_valorHSV;
    int FRAME_WIDTH;
    int FRAME_HEIGHT;
    int MIN_OBJECT_AREA;

    string windowName;
    string windowName1;
    string windowName2;

    Mat src;

    Mat mainImagen;

    void (Body::*currentFun)();
    Mat threshold;

   VideoCapture capture;
   bool m_processActivated;
   VideoWriter videobn;
   VideoWriter videoreal;
   VideoWriter videoanimacion;


   Body m_body;

};

#endif // CAPTUREMOTION_H
