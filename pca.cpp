#include <iostream>
#include <fstream>
#include <string>
#include "Eigen/Dense"

using namespace std;
int main(){

    Eigen::MatrixXd avgRainfall(64,2); //64 2 variable data points

    std::ifstream inputFile("../Data/Data.txt");
    if(inputFile){
        string location = "";
        string line = "";
        string line2 = "";

        int count1 = 0;
        int count2 = 0;

        inputFile >> line;
        inputFile >> line; //discard the first two lines

        while(!inputFile.eof()){
            // getline(inputFile, line, '\n');
            // getline(inputFile, line, '\n');
            inputFile >> location;
            inputFile >> line; 
            inputFile >> line2;
    
            // cout<< line<<endl;
            // cout << line2<<endl;

            avgRainfall(count1, 0) = stod(line);
            avgRainfall(count1, 1) = stod(line2);

            count1 ++;
           
           // avgRainfall(count1, count2) = ;

           // value =stod(line);         
        }

    }else{
        std::cout << "File now found, exiting.";
        return 0;
    }

    cout << avgRainfall<<endl;

    

return 0;
}