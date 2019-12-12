#include "main.h"

void translateFunc(int id){
    renderPixelBuffer(id, 3);
    renderPixelBuffer(id, 4);
    float xValue, yValue, vertex = 0;
    cout << "\n" << "Enter the x translation value: ";
    cin >> xValue;
    cout << "Enter the y translation value: ";
    cin >> yValue;
    int xyVerticies = myArray.at(id).at(0);
    while(vertex < xyVerticies){
        int xIndex = 1 + 2 * vertex, yIndex = 2 + 2* vertex;
        myArray.at(id).at(xIndex) += xValue;
        myArray.at(id).at(yIndex) += yValue;
        vertex  = vertex + 1;
    }
    for (int i = 0; i < xyVerticies; i++) {
		linePoints[i][0] = (int)myArray.at(id).at(1+i*2);
	    linePoints[i][1] = (int)myArray.at(id).at(2+i*2);
	}
    suthHodgmanAlgo(linePoints, xyVerticies, id);
    rasterizeFunc(digit);
}
// ============================================================================================//
void rotateFunc(int id){
    renderPixelBuffer(id, 2);
    renderPixelBuffer(id, 4);
    double degree, xSum = 0, ySum = 0, xMidPoint, yMidPoint;
    int vertices = myArray.at(id).at(0), 
    i = 0, j = 0, k = 0; 
    cout << "\n" << "Please enter degree to rotate the object-" << id + 1 << ": ";
    cin >> degree;
    double radians = (double)degree /180.0 * 3.14159265359;
    int points[maxVertices][2]; 

    while(i < vertices){
        xSum = xSum + myArray.at(id).at(1+i*2);
        i = i + 1;
    }
    xMidPoint = xSum / (double)vertices;
    while (j < vertices){
        ySum += myArray.at(id).at(2+j*2);
        j = j + 1;
    }
    yMidPoint = ySum / (double)vertices;
    while(k < vertices) {
        double xPoint, yPoint; 
        xPoint = myArray.at(id).at(1+k*2) - xMidPoint;
        yPoint = myArray.at(id).at(2+k*2) - yMidPoint;
        myArray.at(id).at(1+k*2) = (xPoint*cos(radians) - yPoint*sin(radians)) + xMidPoint;
        myArray.at(id).at(2+k*2) = (xPoint*sin(radians) + yPoint*cos(radians)) + yMidPoint;
        k++;
    }
    for (int i = 0; i < vertices; i++) {
		linePoints[i][0] = (int)myArray.at(id).at(1+i*2);
	    linePoints[i][1] = (int)myArray.at(id).at(2+i*2);
	}
    suthHodgmanAlgo(linePoints, vertices, id);
    rasterizeFunc(digit);
}
// ============================================================================================//
void scaleFunc(int id){
    renderPixelBuffer(id, 2);
    renderPixelBuffer(id, 4);
    double scaleValue; 
	int vertices = myArray.at(id).at(0), i = 0, j = 0, k = 0;
    double xSum = 0, ySum = 0, centerOfX, centerOfY;

	cout << "\n" << "Please enter the magnitude to scale the object-" << id + 1 << "\n"
    << "0 to 1 decrease size, 1 to 10 increase size: ";	
	cin >> scaleValue;

    while(i < vertices){
        xSum = xSum + myArray.at(id).at(1+i*2);
        i = i + 1;
    }
	centerOfX = xSum / (double)vertices;
    while(j < vertices){
        ySum = ySum + myArray.at(id).at(2+j*2); 
        j = j + 1;
    }
	centerOfY = ySum / (double)vertices;
    while(k < vertices){
        myArray.at(id).at(1+k*2) = scaleValue*(myArray.at(id).at(1+k*2) - centerOfX) + centerOfX; 
		myArray.at(id).at(2+k*2) = scaleValue*(myArray.at(id).at(2+k*2) - centerOfY) + centerOfY;
        k += 1;
    }
    for (int i = 0; i < vertices; i++) {
		linePoints[i][0] = (int)myArray.at(id).at(1+i*2);
	    linePoints[i][1] = (int)myArray.at(id).at(2+i*2);
	}
    suthHodgmanAlgo(linePoints, vertices, id);
    rasterizeFunc(digit);    
}
// ============================================================================================//
void clippingFunc(int id){
    renderPixelBuffer(id, 2);
    renderPixelBuffer(id, 4);
    int minWidth, maxWidth, minHeight, maxHeight; 
	int vertices = myArray.at(id).at(0); 
	cout << "\n" << "In order to clip, Please enter window four area value min and max for width and heigh"
     << "to clip the object < eg: 100 200 200 400 >: \n "; 
	cin >> minWidth >> maxWidth >> minHeight >> maxHeight;
	while (minWidth < 0 || maxWidth > screen_width || minHeight < 0 || maxHeight > screen_height || minWidth >= maxWidth || minHeight >= maxHeight) {
		cout << "\n" << "Error!! out of range. " << "\n" <<
        "Please enter four clip area value min and max for width and height again to clip the object-" << id + 1 << endl;;
		cin >> minWidth >> maxWidth >> minHeight >> maxHeight; 
	}
    for (int i = 0; i < vertices; i++) {
		linePoints[i][0] = (int)myArray.at(id).at(1+i*2);
	    linePoints[i][1] = (int)myArray.at(id).at(2+i*2);	
	}		
	int clipWindow[][2] = {{minWidth, minHeight}, {minWidth, maxHeight}, {maxWidth, maxHeight}, {maxWidth, minHeight}}; 	
    int clipPolySize = sizeof(clipWindow)/sizeof(clipWindow[0]);

    for (int i=0; i<clipPolySize; i++) { 
        int k = (i+1) % clipPolySize; 
        clipFunc(linePoints, vertices, clipWindow[i][0], 
             clipWindow[i][1], clipWindow[k][0], 
             clipWindow[k][1]); 
    } 
    myArray.at(id).clear();
	myArray.at(id).push_back(vertices); 
	for (int i = 0; i < vertices; i++) { 
        myArray.at(id).push_back((double)linePoints[i][0]-1); 
        myArray.at(id).push_back((double)linePoints[i][1]-1); 
	}
    rasterizeFunc(digit);
}
// ============================================================================================//
int xyIntersect(int a, int b, int c, int d, int e, int f, int g, int h, int num){
    switch (num){
    case 1:
         division = ((a*d - b*c) * (e-g) - (a-c) * (e*h - f*g)) / ((a-c) * (f-h) - (b-d) * (e-g));
	    return (division); break;
    case 2:
         division = ((a*d - b*c) * (f-h) - (b-d) * (e*h - f*g)) / ((a-c) * (f-h) - (b-d) * (e-g));
        return (division); break;
    default:
        break;
    }
}
void clipFunc(int linePoints[][2], int &objectSize, int a, int b, int c, int d){
int newLinePoint[maxVertices][2], newLinePointSize = 0; 
    for (int i = 0; i < objectSize; i++) { 
        int k = (i+1) % objectSize; 
        int ix = linePoints[i][0], iy = linePoints[i][1]; 
        int kx = linePoints[k][0], ky = linePoints[k][1]; 
        int iPosition = (c-a) * (iy-b) - (d-b) * (ix-a); 
        int kPosition = (c-a) * (ky-b) - (d-b) * (kx-a); 
        if (iPosition < 0  && kPosition < 0){ 
            newLinePoint[newLinePointSize][0] = kx; 
            newLinePoint[newLinePointSize][1] = ky; 
            newLinePointSize++; 
        } 
        else if (iPosition >= 0  && kPosition < 0) { 
            newLinePoint[newLinePointSize][0] = xyIntersect(a, b, c, d, ix, iy, kx, ky, 1); 
            newLinePoint[newLinePointSize][1] = xyIntersect(a, b, c, d, ix, iy, kx, ky, 2); 
            newLinePointSize++; 
  
            newLinePoint[newLinePointSize][0] = kx; 
            newLinePoint[newLinePointSize][1] = ky; 
            newLinePointSize++; 
        } 
        else if (iPosition < 0  && kPosition >= 0) { 
            newLinePoint[newLinePointSize][0] = xyIntersect(a, b, c, d, ix, iy, kx, ky, 1); 
            newLinePoint[newLinePointSize][1] = xyIntersect(a, b, c, d, ix, iy, kx, ky, 2); 
            newLinePointSize++; 
        } 
    } 
    objectSize = newLinePointSize; 
    for (int i = 0; i < objectSize; i++) { 
        linePoints[i][0] = newLinePoint[i][0]; 
        linePoints[i][1]  = newLinePoint[i][1]; 
    }
}
void suthHodgmanAlgo(int linePoint[][2], int objectSize, int id){
    for (int i=0; i<viewPortSize; i++) { 
        int k = (i+1) % viewPortSize; 
        clipFunc(linePoint, objectSize, viewPortPoint[i][0], 
             viewPortPoint[i][1], viewPortPoint[k][0], 
             viewPortPoint[k][1]); 
    } 
    myArray.at(id).clear();
	myArray.at(id).push_back(objectSize); 
	for (int i = 0; i < objectSize; i++) { 
        myArray.at(id).push_back((double)linePoints[i][0]-1); 
        myArray.at(id).push_back((double)linePoints[i][1]-1); 
	}
}