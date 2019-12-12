#include "main.h"
// get the data from input file
void getDataFromFile(){
    vector<double> data;
    double vertices;
    fstream myFile;
    cout<< "Welcome from graphic world!" << "\n" <<endl;
    cout << "Enter the input file name: ";
    cin >> fileName;
    while(cin){
        fstream myFile(fileName);
        if (myFile.is_open()){
        break;  
        }
        else if(myFile.fail()){
        cout<< "Unable to open the file" << endl;
        cout << "Enter the input file name again: ";
        cin >> fileName;
        }
    }
    myFile.open(fileName);
    while (myFile >> vertices){
        data.push_back(vertices);
    }
    myFile.close();
    auto XYpoints = data.begin(); 
    int polyTotalForBuffer = (int)*XYpoints;
    int i = 0;
    while(i < polyTotalForBuffer){
        vector<double> Vx; 
        myArray.push_back(Vx);  
        double vertices = *(++XYpoints);
        myArray.at(i).push_back(vertices);
        int j = 0;
        while(j < vertices){
            myArray.at(i).push_back(*(++XYpoints)); 
            myArray.at(i).push_back(*(++XYpoints)); 
            j++;
        } 
        i = i + 1;
    }
    lineBuffer = new float[polyTotalForBuffer*screen_width * screen_height * 3]();
}
void saveDataInOutputFile(){
    ofstream outputFile;
    outputFile.open(fileName);
    outputFile << myArray.size() << endl;
    for (int i = 0; i < myArray.size(); i++) {
        outputFile << endl;
        for (int j = 0; j < myArray.at(i).size(); j++){
            outputFile << myArray.at(i).at(j) << " ";
            if(j % 2 == 0){
                outputFile << endl;
            }
        }
        outputFile << endl;
    }
}