#include "main.h"

void createMenuFunc(){
    rasterize = glutCreateMenu(rasterizeFunc);
        glutAddMenuEntry("On", 1);
        glutAddMenuEntry("Off", 0);

    translate = glutCreateMenu(translateFunc);
        for(int i = 0; i < myArray.size(); i++){
            glutAddMenuEntry(arr[i], i); 
        } 
    scale = glutCreateMenu(scaleFunc);
        for(int i = 0; i < myArray.size(); i++){
            glutAddMenuEntry(arr[i], i); 
        }
    rotation = glutCreateMenu(rotateFunc);
        for(int i = 0; i < myArray.size(); i++){
            glutAddMenuEntry(arr[i], i); 
        }

    list = glutCreateMenu(list_menuFunc);
        glutAddSubMenu("Translation", translate);
        glutAddSubMenu("Rotation", rotation);
        glutAddSubMenu("Scaling", scale);
    
    clipping = glutCreateMenu(clippingFunc); 
        for(int i = 0; i < myArray.size(); i++){
            glutAddMenuEntry(arr[i], i); 
        }
    
    exist = glutCreateMenu(exitFunc);
        glutAddMenuEntry("Exit-Program", 0);

    continues = glutCreateMenu(continueFunc);
        glutAddMenuEntry("Continue-Program", 0);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("Rasterization", rasterize);
    glutAddSubMenu("Transformations", list);
    glutAddSubMenu("Clipping", clipping);
    glutAddSubMenu("Continue", continues);
    glutAddSubMenu("Exit", exist);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}