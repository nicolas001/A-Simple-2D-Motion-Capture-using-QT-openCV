#include "pointobject.h"




bool PointObject::findObjects(Mat& threshold, PointObject points[], int & counter, const int & maxObjects, const int& minArea)
{


    counter = 0;
    Mat temp;
    threshold.copyTo(temp);

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );


    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        if(numObjects<=maxObjects){

            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;
                if(area>minArea){

                    PointObject object;

                    object.setXpos(moment.m10/area);
                    object.setYpos(moment.m01/area);
                    object.setColor(getColor());
                    points[counter++] = object;
                }
            }

        }
    }
    return counter!=0;

}

void PointObject::morphOps(Mat &thresh)
{
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}
