#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

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

double mean(int *array, int countLine) {
    int sum = 0;
    for (int i = 1; i < countLine; i ++) {
        sum += array[i];
    }
    return (sum / countLine);
}

double median(int *array, int countLine) {

    if (countLine % 2 != 0) {
        return array[countLine / 2];
    } else {
        return (double)(array[(countLine - 1) / 2] + array[countLine / 2]) / 2;
    }
}
////Function to calculate Variance
double variance(int* array, int countLine) {
    // Compute sum squared
    // differences with mean.
    double squaredDiff = 0, m = mean(array, countLine);
    for (int i = 1; i < countLine; i++) {
        squaredDiff += (array[i] - m) * (array[i] - m);
    }
    return (squaredDiff / countLine);
}

////Function to calculate Deviation
double standardDeviation(int* array, int countLine) {
    double var = variance(array, countLine);
    return sqrt(var);
}

//Function to calculate MAD
double meanAbsoluteDeviation(int* array, int countLine) {
    double m = mean(array, countLine), absSum = 0;
    for (int i = 0; i < countLine; i++) {
        absSum += abs(array[i] - m);
    }
    // Return mean absolute deviation about mean.
    return (absSum / countLine);
}

////Function to calculate First Quartile


//// Function to calculate skewness.
double skewness(int* array, int countLine){
    double sum = 0, m = mean(array, countLine), skew;
    for (int i = 0; i < countLine; i++)
        sum = (array[i] - m) * (array[i] - mean(array, countLine)) * (array[i] - mean(array, countLine));
    skew = sum / (countLine * standardDeviation(array, countLine) * standardDeviation(array, countLine) * standardDeviation(array, countLine) * standardDeviation(array, countLine));
    return skew;
}

////Function to calculate Kurtosis
double kurtosis(int* array, int countLine) {
    double sum = 0, kurt;
    for (int i = 0; i < countLine; i++) {
        sum = (array[i] - mean(array, countLine)) * (array[i] - mean(array, countLine)) *
                (array[i] - mean(array, countLine)) * (array[i] - mean(array, countLine));

    }
    kurt = (sum / (countLine * standardDeviation(array, countLine) * standardDeviation(array, countLine) * standardDeviation(array, countLine) * standardDeviation(array, countLine) * standardDeviation(array, countLine))) - 3;
    return kurt;
}

double covariance(int *array_x, int *array_y, int countLine) {
    double sum = 0, m_x = mean(array_x, countLine), m_y = mean(array_y, countLine);
    for (int index = 1; index < countLine; index ++) {
        sum += ((array_x[index] - m_x)*(array_y[index] - m_y));
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
    double m_x = mean(array_x, countLine), m_y = mean(array_y, countLine);
    double stdev_x = standardDeviation(array_x, countLine), stdev_y = standardDeviation(array_y, countLine);

    //find a, b in y = ax + b
    //a is slope
    slope = (r * stdev_y)/stdev_x;
    //b is intercept
    intercept = m_y - slope * m_x;

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
    int m_x = mean(array_x, countLine), m_y = mean(array_y, countLine);
    return 0;
}

// Function detail:
