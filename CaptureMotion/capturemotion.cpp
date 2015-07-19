#include "capturemotion.h"
#include "ui_capturemotion.h"
#include <opencv2/opencv.hpp>
#include <qmessagebox.h>
#include <omp.h>

CaptureMotion::CaptureMotion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CaptureMotion)
{
    ui->setupUi(this);


    /**Valor de HSV**/
    m_valorHSV = 0;

    /**Dimensiones de la pantalla**/
    FRAME_WIDTH = 640;
    FRAME_HEIGHT = 480;
    MIN_OBJECT_AREA = 100;

    /**Nombre de las ventanas necesarias en OPENCV**/
    windowName = "Original Image";
    windowName2 = "Thresholded Image";


   /**Iniciamos la captura de la camara**/
    capture.open(1);
    if(!capture.isOpened() ){return;}
    capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);




    /**Funcion a ejecutar segun el boton que presionemos**/
    currentFun = &Body::calibrateBody;

    /**Videos a guardar**/
    videoreal = VideoWriter("videoreal.avi", CV_FOURCC('P','I','M','1'), 20, Size(640,480));
    videoanimacion = VideoWriter("videoanimacion.avi", CV_FOURCC('P','I','M','1'), 20, Size(640,480));
}




void CaptureMotion::calibrateValue()
{
    while(m_processActivated)
    {
        Mat animation = Mat(FRAME_HEIGHT,FRAME_WIDTH, CV_8UC3, Scalar(0,0,0));

        /**Capturamos un nuevo frame**/
        capture.read(mainImagen);
        src = mainImagen;
        if( !src.data ){ return; }

        /**Sacamos los nuevos puntos**/
        m_body.setValueVmin(m_valorHSV);
        m_body.fintPoints(mainImagen, threshold,MIN_OBJECT_AREA);

        /**Ejecutamos la funcion deseada deacuerdo a los botones de calibrar o empezar con la captura de movimeinto**/
        (m_body.*currentFun)();
        /**Grafica el cuerpo**/
        m_body.drawBody(animation);

        /**Mostramos en pantalla**/
        imshow(windowName2,threshold);
        imshow(windowName,animation);

        /**Grabamos**/
        videoanimacion<<animation;
        videoreal << mainImagen;

        waitKey(30);

    }


    videoanimacion.release();
    videoreal.release();
    destroyWindow(windowName);
    destroyWindow(windowName2);


}



CaptureMotion::~CaptureMotion()
{

    destroyWindow(windowName);
    destroyWindow(windowName2);
    delete ui;
}



void CaptureMotion::on_BarhsvMin_sliderMoved(int position)
{
    ui->txtV->setText(QString::number(position));
    m_valorHSV = position;

}



void CaptureMotion::on_checkStart_clicked(bool checked)
{
    if(checked==true)
        calibrateValue();
}



void CaptureMotion::on_btnTerminar_clicked()
{
    m_processActivated = false;
}

void CaptureMotion::on_btnStartCC_clicked()
{

    currentFun = &Body::calibrateBody;
}

void CaptureMotion::on_btnDoneCC_clicked()
{
    currentFun = &Body::findNearPoints;
}
