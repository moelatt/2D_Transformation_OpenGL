#ifndef MAIN_H
#define MAIN_H
#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include  <GL/glut.h>
#endif
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
using namespace std;
#define maxVertices 50

float *PixelBuffer;
float *lineBuffer;
string fileName ;
vector<vector<double> > myArray;
const int screen_width = 550 , screen_height = 550; 
int scale, rotation, translate, clipping, rasterize, exist, list, division ,digit, continues;
float color[] = { 0,1,1 };
int lineTotal;
double maxPoint = 0;
double minPoint = screen_height;
float windowValue = screen_width * screen_height * 3;
const char* arr[] = {"Object-1", "Object-2", "Object-3", "Object-4", "Object-5", 
                     "Object-6", "Object-7", "Object-8","Object-9", "Object-10",
                     "Object-11","Object-12","Object-13","Object-14","Object-15"};
int viewPortPoint[][2] = {{1,0},{1, screen_height},{screen_width, screen_height},{screen_width,0}};
int viewPortSize = sizeof(viewPortPoint)/sizeof(viewPortPoint[0]);
int linePoints[maxVertices][2];

void getDataFromFile();
void createMenuFunc();
void display(); 
void DrawLine(); 
int absolute(int num);
void swapFunc(int x, int y);
void drawPixelBuffer(int, int);
inline int roundOff(const double a) {return (int)(a+0.5);}
void polygonPixel(int x, int y, int objectIndex);
void renderPixelBuffer(int objectIndex, int num);
void BresenhamAlgorithm(double xStart, double yStart, double xEnd, double yEnd, int objectIndex);
void DdaAlgorithm(double xStart, double yStart, double xEnd, double yEnd, int objectIndex);
void insertionSort(int x[], int size);
void setPolyPixel(int x, int y, int id);
int rasterYpoint(int id, int num);
void rasterizationLine(int objectIndex);
void rasterizeFunc(int id);
void translateFunc(int id);
void rotateFunc(int id);
void scaleFunc(int id);
void clippingFunc(int id);
void saveDataInOutputFile();
inline void mainMenu(int objectIndex) {;}
void list_menuFunc(int id){};
void clipFunc(int linePoints[][2], int &objectSize, int x1, int y1, int x2, int y2);
void suthHodgmanAlgo(int linePoint[][2], int objectSize, int id);
int xyIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int num);
void continueFunc(int id);
void exitFunc(int id);
#endif