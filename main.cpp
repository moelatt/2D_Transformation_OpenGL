#include "main.h"
#include "getFileData.cpp"
#include "createMenuUI.cpp"
#include "transformation.cpp"
#include "rasterization.cpp"
#include "drawLineAlgo.cpp"
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(screen_width/4,screen_height/4);
    glutInitWindowSize(screen_width, screen_height);
    glutCreateWindow("Project-1");
    glClearColor(0, 0, 0, 0);
    PixelBuffer = new float[screen_width * screen_height * 3]();
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glPointSize(5);
    renderPixelBuffer(screen_height, 4); 
    getDataFromFile();
    DrawLine();
    createMenuFunc();
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
// ===============================================================================//
// Display the openGL on screen
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glDrawPixels(screen_width, screen_height, GL_RGB, GL_FLOAT, PixelBuffer);
    glFlush();
}
void polygonPixel(int x, int y, int objectIndex){
    lineBuffer[objectIndex*screen_width*screen_height*3 + (y*screen_width+x)*3+0] = color[0];
    lineBuffer[objectIndex*screen_width*screen_height*3 + (y*screen_width+x)*3+1] = color[1];
    lineBuffer[objectIndex*screen_width*screen_height*3 + (y*screen_width+x)*3+2] = color[2];
}
// ==================================================================================//
void renderPixelBuffer(int objectIndex, int num){
    int index = 0, i = 0, c = 0, b = 0;
    switch (num){
    case 1:
        while(index < windowValue){ // display copy buffer
            if (lineBuffer[objectIndex*screen_width*screen_height*3 + index] != 0){
                PixelBuffer[index] = lineBuffer[objectIndex*screen_width*screen_height*3 + index];
            }
            index = index + 1;
        } break;
    case 2:
        while(i < windowValue){ // clear buffer
            PixelBuffer[i] = 0; i++;
        } break;
    case 3: 
        while(c < windowValue){ // clear polygon buffer
            lineBuffer[objectIndex*screen_width*screen_width*3 + c] = 0;
            c = c + 1;
        } break;
    case 4:
        while ( b < screen_width*screen_width) { // bg color
		PixelBuffer[b * 3] = 0.1;
		PixelBuffer[b * 3 + 1] = 0.15;
		PixelBuffer[b * 3 + 2] = 0.05;
        b = b + 1;
	    } break;
    default:
        break;
    }
}
// ============================================================================ //
// Draw Polygon in screen
void DrawLine() { 
    int options;
    cout << endl;
    cout << "1. Draw line with Bresenham Algorithm"<< endl ;
    cout << "2. Draw line with DDA Algorithm"<< "\n" <<endl ;
    cout << "Enter algorithm 1 or 2 to draw: ";
    cin >> options;
    while(options != 1 && options != 2){
        cout << "Error! You can only choose 1 or 2 to draw" << endl;
        cout << "Enter number 1 or 2 again to draw: ";
        cin >> options;
    }
    cout << "====> Righ Click Anywhere on Window Screen To See Menu <====" << endl;
    for (int objectIndex = 0;objectIndex < myArray.size(); objectIndex++) {  
       		renderPixelBuffer(objectIndex, 3); 		
            drawPixelBuffer(objectIndex, options);
            renderPixelBuffer(objectIndex, 1);
        }
}
void drawPixelBuffer(int objectIndex, int options){
    int totalLine = myArray.at(objectIndex).at(0), indexLine = 0;

    while(indexLine < totalLine){
        double xStart = myArray.at(objectIndex).at(1+indexLine*2);
        double yStart = myArray.at(objectIndex).at(2+indexLine*2); 
        double xEnd, yEnd;
        if (indexLine == totalLine-1) {
            xEnd = myArray.at(objectIndex).at(1);
            yEnd = myArray.at(objectIndex).at(2);
        }
        else {
            xEnd = myArray.at(objectIndex).at(3+indexLine*2);
            yEnd = myArray.at(objectIndex).at(4+indexLine*2);
        }
        switch (options){
            case 1:
                BresenhamAlgorithm(xStart, yStart, xEnd, yEnd, objectIndex);
                break;
            case 2:
                DdaAlgorithm(xStart, yStart, xEnd, yEnd, objectIndex);
                break;
            default:
            break;
        }
        indexLine = indexLine + 1;
    }
}
// ============================================================================================//
void continueFunc(int id){
    int i = 0;
    while(i < windowValue){ // clear buffer
            PixelBuffer[i] = 0; i++;
        }
    renderPixelBuffer( i, 4);
    int num = 0;
     int options;
    cout << endl;
    cout << "1. Draw line with Bresenham Algorithm"<< endl ;
    cout << "2. Draw line with DDA Algorithm"<< "\n" <<endl ;
    cout << "Enter algorithm 1 or 2 to draw: ";
    cin >> options;
    while(options != 1 && options != 2){
        cout << "Error! You can only choose 1 or 2 to draw" << endl;
        cout << "Enter number 1 or 2 again to draw: ";
        cin >> options;
    }
    cout << "====> Righ Click Anywhere on Window Screen To See Menu <====" << endl;

    for (int objectIndex = 0;objectIndex < myArray.size(); objectIndex++) { 
            renderPixelBuffer(objectIndex, 3); 		
            drawPixelBuffer(objectIndex, options);
            renderPixelBuffer(objectIndex, 1);
        }
        saveDataInOutputFile();
        glutPostRedisplay();
}
void exitFunc(int id){
    cout << endl;
    cout << "Any change will be saved in the original file the data is read in." << endl;
    cout << "Bye Bye!!" << "\n" <<endl;
    exit(0);
}
