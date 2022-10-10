#include "segment.h"
#include <string>
#include "pbPlots.hpp"
#include "supportLib.hpp"

class robot {
  //declaring the private members
    private:
        int degreeOfFreedom=0;
        segment* parentS;
    //declaring the public members
    public:
    //default constructor
        robot () {
            parentS = NULL;
            degreeOfFreedom=0;
        }
        //non-default constructor
        robot (segment* parent) {
            degreeOfFreedom = 1;
            parentS = parent;
        }
        //getter for dOf
        int getDegreeOfFreedom() {
            return degreeOfFreedom;
        }
        //method for adding new segment
        void newSegment (segment* newsegment) {
          //if condition: applying the first segment to the passed one if no segment was spotted
            if(parentS == NULL) {
                degreeOfFreedom = 1;
                parentS = newsegment;
            }
            else {
                //else condition for incrementing the dOf
                segment* ptr;
                //for loop for checking each segment and assigning new the coordinates
                for(ptr = parentS; ptr->getChildS(); ptr = ptr->getChildS()) {}
                ptr->setChildS(newsegment);
                degreeOfFreedom += 1;
            }
        }
        //method for deleting the segments
        void deleteSegment () {
          //if condition: in case there is no segments in the linkage, return
            if(parentS == NULL) {
              return;
            }
            //removing the single segment
            else if(degreeOfFreedom == 1) {
                parentS = NULL;
                degreeOfFreedom = 0;
            }
            else {
                segment* ptr;
                //for loop for checking each segment and assigning new start and end points: setting NULL to the segment and decrementing the dOf
                for(ptr = parentS; (ptr->getChildS())->getChildS(); ptr = ptr->getChildS()) {}
                ptr->setChildS(NULL);
                degreeOfFreedom -= 1;
            }
        }

        //method for returning the robotic arm to the default position
        void defaultPosition () {
            if(parentS == NULL){
            }
            else {
                segment* ptr;
                point defaultPoint = point();
               //for loop for checking each segment and assigning new start and end points
                for(ptr = parentS; ptr != NULL; defaultPoint = ptr->getStartP(), ptr = ptr->getChildS()) {
                    ptr->setStartP(defaultPoint);
                    ptr->setA(0);
                }
            }
        }
        //method for forward kinematics
        void applyForwardKinematics(double givenAngles[], int givenArraySize) {
          //if condition: returning if the array size is bigger than the dOf
            if (givenArraySize > degreeOfFreedom)
                return;
            segment* ptr = parentS;
            point defaultPoint = ptr->getStartP();
            //for loop for checking each segment and assigning new start and end points + the angle
            for(int sz = 0; sz < givenArraySize; sz++, defaultPoint = ptr->getEndP(), ptr = ptr->getChildS()) {
                ptr->setStartP(defaultPoint);
                ptr->setA(givenAngles[sz]);
            }
        }

        //method for plotting the graph (implemented library)
        void drawGraph(string name) {
            double pointsX[degreeOfFreedom * 2];
            double pointsY[degreeOfFreedom * 2];
            segment* ptr;
            int degree = 0;
            for(ptr = parentS; ptr; ptr = ptr->getChildS(), degree += 1) {
                pointsX[degree * 2] = (ptr->getStartP()).getX();
                pointsY[degree * 2] = (ptr->getStartP()).getY();
                pointsX[degree * 2 + 1] = (ptr->getEndP()).getX();
                pointsY[degree * 2 + 1] = (ptr->getEndP()).getY();
            }
            //vector that allows the pass to pbPlots to be plotted
            vector<double> xs(pointsX, pointsX+sizeof(pointsX)/sizeof(double));
            vector<double> ys(pointsY, pointsY+sizeof(pointsY)/sizeof(double));
    
            bool success;
            StringReference *errorMessage = new StringReference();
            RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

            ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
            series->xs = &xs;
            series->ys = &ys;
            series->linearInterpolation = true;
            series->lineThickness = 2;
            series->pointType = toVector(L"pixels");
            series->color = GetGray(0.3);

            ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
            settings->width = 600;
            
            settings->height = 400;
            settings->autoBoundaries = true;
            settings->autoPadding = true;
            settings->title = toVector(L"Plot");
            settings->xLabel = toVector(L"X axis");
            settings->yLabel = toVector(L"Y axis");
            settings->scatterPlotSeries->push_back(series);
          //graphing the scatter plot
            success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

            if(success){
                vector<double> *pngdata = ConvertToPNG(imageReference->image);
                WriteToFile(pngdata, name);
                DeleteImage(imageReference->image);
            }else{
                cerr << "Error: ";
                for(int i = 0; i < errorMessage->string->size(); i++){
                    wcerr << errorMessage->string->at(i);
                }
                cerr << endl;
            }
        }
};