#ifndef POINTOBJECT_H
#define POINTOBJECT_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;


class PointObject
{
    private:
        int m_xPos;
        int m_yPos;
        Scalar m_hsvMin;
        Scalar m_hsvMax;
        Scalar m_color;
    public:

        PointObject(int x=0, int y=0, Scalar min = Scalar(0,0,0), Scalar max = Scalar(255,255,255), Scalar color = Scalar(0,0,0)):
                    m_xPos(x), m_yPos(y), m_hsvMin(min), m_hsvMax(max), m_color(color){}

        inline int    getXpos()  {return m_xPos;}
        inline int    getYpos()  {return m_yPos;}
        inline Scalar getHSVmin(){return m_hsvMin;}
        inline Scalar getHSVmax(){return m_hsvMax;}
        inline Scalar getColor() {return m_color;}

        inline void   setXpos(const int& x)         {m_xPos = x;}
        inline void   setYpos(const int& y)         {m_yPos = y;}
        inline void   setHSVmin(const Scalar& min)  {m_hsvMin = min;}
        inline void   setHSVmax(const Scalar& max)  {m_hsvMax = max;}
        inline void   setColor(const Scalar& color) {m_color = color;}

        inline float  distance(PointObject& p2){return sqrt(pow(getXpos()-p2.getXpos(),2)+pow(getYpos()-p2.getYpos(),2));}
        bool findObjects(Mat&, PointObject [], int&, const int&, const int&);
        void morphOps(Mat&);
};

#endif // POINTOBJECT_H
