#include "main.h"

void rasterizeFunc(int id){
    digit = id;
    int options = 1;
    switch (id){
    case 1:
        for (int objectIndex = 0;objectIndex < myArray.size(); objectIndex++) { 
            renderPixelBuffer(objectIndex, 3); 		
            drawPixelBuffer(objectIndex, options);
            rasterizationLine(objectIndex);
            renderPixelBuffer(objectIndex, 1);
        }
        saveDataInOutputFile();
        glutPostRedisplay();
        break;
    case 0:
        renderPixelBuffer(id, 2);
        renderPixelBuffer(id, 4);
        for (int objectIndex = 0;objectIndex < myArray.size(); objectIndex++) { 
            renderPixelBuffer(objectIndex, 3); 		
            drawPixelBuffer(objectIndex, options);
            renderPixelBuffer(objectIndex, 1);
        }
        saveDataInOutputFile();
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
int rasterYpoint(int id, int num){
    int pointY = myArray.at(id).at(2);
    int polySize = myArray.at(id).at(0);
    switch (num){
    case 1: // minimum y point
        for(int i = 0; i < polySize; i++) {
            if(myArray.at(id).at(2+i*2) < pointY) {
                pointY = myArray.at(id).at(2+i*2);
            }
        } return pointY; break;
    case 2: // maximum y point
        for(int i = 0; i < polySize; i++) {
            if(myArray.at(id).at(2+i*2) > pointY) {
                pointY = myArray.at(id).at(2+i*2);
            }
        } return pointY; break;
    default:
        break;
    }
}
void insertionSort(int x[], int size){
	for(int i = 0; i < size; i++){
		int value = x[i];
		int index = i;
		while(index > 0 && x[index -1 ] > value) {
			x[index] = x[index - 1];
			index = index - 1;
		}
		x[index] = value;
	}
}
void rasterizationLine(int id) {
	int miny = rasterYpoint(id, 1), polySize = myArray.at(id).at(0);
	int maxy = rasterYpoint(id, 2);
	int x1, x2, y1, y2, y = miny;
	while(y < maxy) {
		int v1, v2, v11, v22;
		int x;
		int arr[maxVertices];
		int count = 0;
		for(v1 = 0, v2 = polySize - 1; v1 < polySize; v2 = v1, v1++) {
			x1 = myArray.at(id).at(1+v1*2); y1 = myArray.at(id).at(2+v1*2);
			x2 = myArray.at(id).at(1+v2*2); y2 = myArray.at(id).at(2+v2*2);

			int yMax = (y1>y2)?y1:y2;
			int yMin = (y1<y2)?y1:y2;

			if(y1 == y2) {
				if(y == y1) {
					int xMax = (x1>x2)?x1:x2;
					int xMin = (x1<x2)?x1:x2;
				}
				continue;
			}
			if(y > yMax || y < yMin)
				continue;
			x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
			if((x == x1) && (y == y1)) {
				if(v1 == 0) {
					v11 = myArray.at(id).at(0) - 1;
					v22 = 1;
				} else if (v1 == myArray.at(id).at(0) - 1) {
					v11 = v1 - 1;
					v22 = 0;
				} else {
					v11 = v1 - 1;
					v22 = v1 + 1;
				}
				if((y -  myArray.at(id).at(2+v11*2)) * (y -  myArray.at(id).at(2+v22*2)) < 0) {
					arr[count] = x;
					count++;
				} else {
					arr[count] = x;
					count++;
					arr[count] = x;
					count++;
				}
			} else if((x == x2) && (y == y2)) {
					arr[count] = x;
					count++;
					arr[count] = x;
					count++;
			} else {
				arr[count] = x;
				count++;
			}
		}
		insertionSort(arr, count);
		for(int i = 0; i < count; i += 2) {
			int j = i + 1;
			x = arr[i];
			while(x < arr[j]) {
				polygonPixel(x, y, id);
				x = x + 1;
			}
		}
		y = y + 1;
	}
}

