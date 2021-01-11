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
    
        inputFile >> line;
        inputFile >> line; //discard the first two lines

        while(!inputFile.eof()){
            inputFile >> location;
            inputFile >> line; 
            inputFile >> line2;

            avgRainfall(count1, 0) = stod(line);
            avgRainfall(count1, 1) = stod(line2);
            count1 ++;
        }
    }else{
        std::cout << "File now found, exiting.";
        return 0;
    }
    inputFile.close();

    ofstream outputFile("../output.txt");

    outputFile << "-------------------------------------\n   Question 1: Eigen Values\n-------------------------------------\n";

    Eigen::MatrixXd centered = avgRainfall.rowwise() - avgRainfall.colwise().mean();
    Eigen::MatrixXd covarianceMatrix = (centered.adjoint()*centered/double(avgRainfall.rows()-1));

    Eigen::EigenSolver<Eigen::MatrixXd> eigenSolver(covarianceMatrix);

      complex<double> eigenValue1 = eigenSolver.eigenvalues()[0];
      complex<double> eigenValue2 = eigenSolver.eigenvalues()[1];

      outputFile << "PCA1: "<<eigenValue1.real()<<endl;
      outputFile << "PCA2: "<<eigenValue2.real()<<endl;

    outputFile << "-------------------------------------\n   Question 2: Eigen Vectors\n-------------------------------------\n";
    outputFile <<"PCA1:\n"<<eigenSolver.eigenvectors().col(0).real() << endl;
    outputFile <<"PCA2:\n"<<eigenSolver.eigenvectors().col(1).real() << endl;

    outputFile << "-------------------------------------\n   Question 3: Covariance Matrix\n-------------------------------------\n";
    outputFile << covarianceMatrix << endl;

    complex<double> totalVariance = eigenValue1 + eigenValue2;

    outputFile << "-------------------------------------\n   Question 4: Total Variance\n-------------------------------------\n";
    outputFile << totalVariance.real() << endl;

    complex<double> propotion1 = eigenValue1/totalVariance *100.0;
    complex<double> propotion2 = eigenValue2/totalVariance *100.0;

    outputFile << "-------------------------------------\n   Question 4: Proportion of Variance\n-------------------------------------\n";
    outputFile << "PCA1: "<<propotion1.real() <<"%  "  << endl;
    outputFile << "PCA2: "<<propotion2.real() <<"%  "  << endl;
    outputFile.close();

    cout <<"\nResults printed to output.txt in directory above.\n\n";
return 0;
}