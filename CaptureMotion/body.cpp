#include "body.h"

Body::Body(): m_maxPoints(15), numPointInf(6),numPointSup(6),numPointLegs(3), numPointArms(3), posThorax(3), posNeck(4)
{
    /**Contenedores de lps puntos corporales**/
    m_bodyPoints  = new PointObject [m_maxPoints];
    m_partsBySide = numPointArms+numPointLegs+2;
    m_rightSide   = new PointObject [m_partsBySide+1];
    m_leftSide    = new PointObject [m_partsBySide];
    counter = 0;



}

void Body::addPointBpody(const PointObject & newP)
{
    if(counter==m_maxPoints)counter=0;
    m_bodyPoints[counter] = newP;
}

void Body::calibrateBody()
{
    if(m_maxPoints==counter)
    {
        float middle = (m_bodyPoints[0].getXpos() + m_bodyPoints[1].getXpos())/2.0;//sacamos la pos media de ambos
        //piernas
        appendPart(middle,0,numPointInf,0,0,1);
        //torax
        m_rightSide[posThorax] = m_bodyPoints[numPointInf];
        m_leftSide[posThorax] = m_bodyPoints[numPointInf];
        //brazos(sin manos)
        appendPart(middle,numPointInf+1,numPointSup-2,posNeck+2,posNeck+2,-1);
        //cuello
        m_rightSide[posNeck] = m_bodyPoints[numPointInf+numPointSup-1];
        m_leftSide[posNeck] = m_bodyPoints[numPointInf+numPointSup-1];
        //manos
        appendPart(middle,numPointInf+numPointSup,2,posNeck+numPointArms,posNeck+numPointArms,1);
        //cabeza
        m_rightSide[m_partsBySide] = m_bodyPoints[counter-1];

    }
}

void Body::appendPart(const float& middle, int ini, int itera, int r, int l, const int& incre)
{
    for(int i=ini; i<ini+itera; i++)
    {
            if(m_bodyPoints[i].getXpos()<= middle)
            {
                m_rightSide[r] = m_bodyPoints[i];
                r+=incre;
            }
            else
            {
                m_leftSide[l] = m_bodyPoints[i];
                l+=incre;
            }
    }
}

int Body::findNear(PointObject& current, bool visitados[])
{
    int near = 0;
    float distNear = std::numeric_limits<double>::infinity();
    for(int i=0; i< counter; i++)
        if(!visitados[i])
        {
            float dist = current.distance(m_bodyPoints[i]);
            if(dist < distNear  )
            {
                near = i;
                distNear = dist;
            }
        }
    visitados[near] = true;
    current = m_bodyPoints[near];
    return near;
}

void Body::findNearPoints()
{
    cout<<counter<<endl;
    bool visitados[m_maxPoints];
     #pragma omp parallel for
    for(int i=0; i<m_maxPoints; i++)
        visitados[i] = false;
     #pragma omp parallel for
    for(int i=0; i<m_partsBySide+1; i++)
        findNear(m_rightSide[i],visitados);
    m_leftSide[posThorax] = m_rightSide[posThorax];
    m_leftSide[posNeck] = m_rightSide[posNeck];
     #pragma omp parallel for
    for(int i=0; i<m_partsBySide; i++)
        if(i!= posThorax && i!=posNeck)
            findNear(m_leftSide[i],visitados);
}

void Body::drawBody(Mat& buffer)
{
     #pragma omp parallel for
    for(int i=0; i<m_maxPoints/2; i++)
    {
        cv::line(buffer,cv::Point(m_rightSide[i].getXpos(),m_rightSide[i].getYpos()),cv::Point(m_rightSide[i+1].getXpos(),m_rightSide[i+1].getYpos()), CV_RGB(255,0,0),6);
        cv::line(buffer,cv::Point(m_leftSide[i].getXpos(),m_leftSide[i].getYpos()),cv::Point(m_leftSide[i+1].getXpos(),m_leftSide[i+1].getYpos()), CV_RGB(255,0,0),6);
    }
    cv::line(buffer,cv::Point(m_rightSide[posNeck].getXpos(),m_rightSide[posNeck].getYpos()),cv::Point(m_rightSide[m_partsBySide].getXpos(),m_rightSide[m_partsBySide].getYpos()), CV_RGB(255,0,0),6);
    cv::circle(buffer,cv::Point(m_rightSide[m_partsBySide].getXpos(),m_rightSide[m_partsBySide].getYpos()),15,CV_RGB(255,0,0),20);


}

int  Body::fintPoints(Mat & image, Mat& threshold, const int& minArea)
{
    Mat HSV;
    cvtColor(image,HSV,COLOR_BGR2HSV);
    inRange(HSV,m_mainPoint.getHSVmin(),m_mainPoint.getHSVmax(),threshold);
    m_mainPoint.morphOps(threshold);
    m_mainPoint.findObjects(threshold,m_bodyPoints,counter,m_maxPoints,minArea);
    return counter;
}

Body::~Body()
{
    delete [] m_bodyPoints;
    delete [] m_rightSide;
    delete [] m_leftSide;
}
