#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef struct {
        int x, y;
} answers;

void showTeamInformation(){
    cout << "ASSIGNMENT 1GROUP<TT>" << endl
         << "s3634831,s3634831@rmit.edu.vn, Bui , Phuoc" << endl
         << "s3695656,s3695656@rmit.edu.vn, Nguyen , Trung" << endl
         << "s3879954,s3879954@rmit.edu.vn, Tran,Nhung" << endl
         << "s3877981,s3877981@rmit.edu.vn, Ngo , Nguyet" << endl;
}
void openFile(const string& filePath, ifstream& ip) {
    ip.open(filePath, ios::in);
    if (!ip.is_open()) {
        showTeamInformation();
        cerr << "ERROR: File Open" << endl;
    }
}
int findNumberOfLines(string x, ifstream& ip) {
    int count = 0;
    while (ip.good()) {
        getline(ip, x, '\n');
        count ++;
    }
    return count;
}
void returnToBeginOfFile(ifstream& ip) {
    ip.clear();
    ip.seekg(1);
}
int strToInt(string str) {
    int index = 0, num = 0, dec = pow(10, str.size())/10;
    while (str[index] != '\0') {
        num += ((str[index] - '0') * dec);
        dec /= 10;
        index ++;
    }
    return num;
}
void storeFileIntoArrays(int *array_x, int *array_y, string str, ifstream& ip) {
    int index = 0; //run index 1++, b/c index 0 is 'x','y'
    while (ip.good()) {
        getline(ip, str, ',');
        array_x[index] = strToInt(str);
        getline(ip, str, '\n');
        array_y[index] = strToInt(str);
        index ++;
    }
}
////Math functions:

answers mean(int *array_x, int *array_y, int countLine) {
    answers m;
    int sum_x = 0, sum_y = 0;
    for (int i = 0; i < countLine; i ++) {
        sum_x += array_x[i];
        sum_y += array_y[i];
    }
    m.x = sum_x / countLine;
    m.y = sum_y / countLine;
    return m;
}

double median(int* array_x, int* array_y, int countLine) {

    if (countLine % 2 != 0) {
        return array_x[countLine / 2];
        return array_y[countLine / 2];
    } else {
        return (array_x[(countLine - 1) / 2] + array_x[countLine / 2]) / 2;
        return (array_y[(countLine - 1) / 2] + array_y[countLine / 2]) / 2;
    }
}
////Function to calculate Variance
answers variance(int* array_x, int* array_y, int countLine) {
    answers vari;
    // Compute sum squared
    // differences with mean.
    double squaredDiff_x = 0;
    double squaredDiff_y = 0;
    for (int i = 0; i < countLine; i++) {
        squaredDiff_x += (array_x[i] - mean) * (array_x[i] - mean);
        squaredDiff_y += (array_y[i] - mean) * (array_y[i] - mean);
    }
    vari.x = squaredDiff_x / countLine;
    vari.y = squaredDiff_y / countLine;
    return vari;
    }

    ////Function to calculate Deviation
    answers standardDeviation(int* array_x, int* array_y, int countLine, answers variance) {
        answers stdDevi;
        stdDevi.x = sqrt(variance(array_x, countLine));
        stdDevi.y = sqrt(variance(array_y, countLine));
        return stdDevi;
    }

    //Function to calculate MAD
    answers meanAbsoluteDeviation(int* array_x, int* array_y, int countLine, answers mean) {
        answers MAD;
        float absSum_x = 0;
        float absSum_y = 0;
        for (int i = 0; i < countLine; i++) {
            absSum_x = absSum_x + abs(array_x[i] - mean(array_x, countLine));
            absSum_y = absSum_y + abs(array_y[i] - mean(array_y, countLine));
        }
        // Return mean absolute deviation about mean.
        MAD.x = absSum_x / countLine;
        MAD.y = absSum_y / countLine;
        return MAD;
    }

    ////Function to calculate First Quartile


    //// Function to calculate skewness.

    answers skewness(int* array_x, int* array_y, int countLine){
        answers skew;
        float sum_x = 0;
        float sum_y = 0;
        for (int i = 0; i < countLine; i++) {
            sum_x = (array_x[i] - mean(array_x, countLine)) * (array_x[i] - mean(array_x, countLine)) * (array_x[i] - mean(array_x, countLine));
            sum_y = (array_y[i] - mean(array_y, countLine)) * (array_y[i] - mean(array_y, countLine)) * (array_y[i] - mean(array_y, countLine));
        }
        skew.x = sum_x / (countLine * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine));
        skew.y = sum_y / (countLine * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine));
        return skew;
    }

    ////Function to calculate Kurtosis
    answers kurtosis(int* array_x, int* array_y, int countLine) {
        answers kurt;
        float sum_x = 0;
        float sum_y = 0;
        double kurtosis_x = 0;
        double kurtosis_y = 0;
        for (int i = 0; i < countLine; i++) {
            sum_x = (array_x[i] - mean(array_x, countLine)) * (array_x[i] - mean(array_x, countLine)) * (array_x[i] - mean(array_x, countLine)) * (array_x[i] - mean(array_x, countLine));
            sum_y = (array_y[i] - mean(array_y, countLine)) * (array_y[i] - mean(array_y, countLine)) * (array_y[i] - mean(array_y, countLine)) * (array_y[i] - mean(array_y, countLine));
        }
        kurt.x = (sum_x / (countLine * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine) * standardDeviation(array_x, countLine))) - 3;
        kurt.y = (sum_y / (countLine * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine) * standardDeviation(array_y, countLine))) - 3;
        return kurt;
    }
}
double covariance(int *array_x, int *array_y, answers median, int countLine) {
    double sum = 0;
    for (int index = 1; index < countLine; index ++) {
        sum += ((array_x[index] - median.x)*(array_y[index] - median.y));
    }
    return (sum / (countLine - 1));
}
double coefficient(int *array_x, int *array_y, int countLine) {
    double squareSum_x = 0, squareSum_y = 0;
    long int sum_x = 0, sum_y = 0, sum_xy = 0;
    for (int i = 1; i < countLine; i ++) {
        sum_xy += (array_x[i] * array_y[i]);
        squareSum_x += pow(array_x[i], 2);
        squareSum_y += pow(array_y[i], 2);
        sum_x += array_x[i];
        sum_y += array_y[i];
    }
    double denominator = sqrt((countLine * squareSum_x - pow(sum_x,2))
            *(countLine * squareSum_y - pow(sum_y, 2)));
    return ((double)(countLine * sum_xy - sum_x * sum_y)/denominator);
}

void linearRegression(int *array_x, int *array_y, int countLine) {
    //initialize the variables
    double r = coefficient(array_x, array_y, countLine), slope, intercept;
    answers m = mean(array_x, array_y, countLine), stdev = standardDeviation(array_x, array_y, countLine);

    //find a, b in y = ax + b
    //a is slope
    slope = (r * stdev.y)/stdev.x;
    //b is intercept
    intercept = m.y - slope * m.x;

    //output the equation
    cout << "The linear equation: y = " << slope << "x + " << intercept << endl;
}
void printDouble(double num) {

}
// Main function:
int main() {
    ifstream ip;
    //declare variables
    string filePath, str, str2;
    int countLine, *array_x, *array_y;

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open the file for reading
    openFile(filePath, ip);

    //start inputting the program contents of csv file
    countLine = findNumberOfLines(str, ip);
    returnToBeginOfFile(ip);
    // create array to store x and y with dynamic memory allocation
    array_x = new int[countLine];
    array_y = new int[countLine];
    storeFileIntoArrays(array_x, array_y, str, ip);

    //output array
    // outArray(array, count_line);

    ip.close();
    showTeamInformation();
    return 0;
}

// Function detail:
