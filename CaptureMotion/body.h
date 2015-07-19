#ifndef BODY_H
#define BODY_H
#include <pointobject.h>
#include <omp.h>
#include <iostream>
#include <limits>

using namespace std;

class Body
{
    private:

        const int m_maxPoints;
        const int numPointInf;
        const int numPointSup;
        const int numPointLegs;
        const int numPointArms;
        const int posThorax;
        const int posNeck;


        PointObject *m_bodyPoints;
        int m_partsBySide;
        //puntos del lado derecho
        PointObject *m_rightSide;//mas la cabeza
        //puntos del lado izquierdo
        PointObject *m_leftSide;
        //contador
        int counter;


        PointObject m_mainPoint;

    public:

        Body();
        void addPointBpody(const PointObject&);
        void calibrateBody();
        void appendPart(const float&, int, int, int, int, const int&);
        int findNear(PointObject& , bool []);
        void findNearPoints();
        void drawBody(Mat&);
        int fintPoints(Mat&, Mat&, const int &);
        inline void setValueVmin(const int& value){m_mainPoint.setHSVmin(Scalar(0,0,value));}


        ~Body();
};

#endif // BODY_H
