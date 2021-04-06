#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

typedef struct {
    public:
        int x, y;
} Contents;

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
void storeFileIntoArrays(Contents *array, string str, string str2, ifstream& ip) {
    int index = 0; //run index 1++, b/c index 0 is 'x','y'
    while (ip.good()) {
        getline(ip, str, ',');
        array[index].x = strToInt(str);
        getline(ip, str2, '\n');
        array[index].y = strToInt(str2);
        index ++;
    }
}


////MATH FUNCTIONS:

////Function to calculate Mean
answers mean(int* array_x, int * array_y, int countLine){
    answers m;
        // Calculate sum of all elements.
        int sum_x = 0;
        int sum_y = 0;
        for (int i = 0; i < countLine; i++) {
            sum_x += array_x[i];
            sum_y += array_y[i];
        }
        m.x = sum_x/countLine;
        m.y = sum_y/countLine;
        return m;
    };
////Function to calculate Median: https://www.tutorialspoint.com/program-for-mean-and-median-of-an-unsorted-array-in-cplusplus
double median(int* array_x, int* array_y, int countLine){

    if (countLine % 2 != 0){
        return (double)array_x[countLine/2];
        return (double)array_y[countLine/2];}
    else {
        return (double) (array_x[(countLine - 1) / 2] + array_x[countLine / 2]) / 2.0;
        return (double) (array_y[(countLine - 1) / 2] + array_y[countLine / 2]) / 2.0;
};

//Function to find Mode


////Function to calculate Variance
answers variance(int* array_x, int* array_y, int countLine) {
    answers Vari;
    // Compute sum squared
    // differences with mean.
    double squaredDiff_x = 0;
    double squaredDiff_y = 0;
    for (int i = 0; i < countLine; i++) {
        squaredDiff_x += (array_x[i] - mean) * (array_x[i] - mean);
        squaredDiff_y += (array_y[i] - mean) * (array_y[i] - mean);
    }
    Vari.x = squaredDiff_x / countLine;
    Vari.y = squaredDiff_y / countLine;
    return Vari;
};
////Function to calculate Deviation
answers standardDeviation(int* array_x, int* array_y,int countLine){
    answers stdDevi;
    stdDevi.x = sqrt(variance(array_x, countLine))
    stdDevi.y = sqrt(variance(array_y, countLine))
    return stdDevi;
};

//Function to calculate MAD
answers meanAbsoluteDeviation(int* array_x, int* array_y, int countLine){
    // Calculate the sum of absolute
    answers MAD;
    // deviation about mean.
    float absSum = 0;
    for (int i = 0; i < countLine; i++) {
        absSum_x = absSum + abs(array_x[i] - mean(array_x, countLine));
        absSum_y = absSum + abs(array_y[i] - mean(array_y, countLine));
    }
    // Return mean absolute deviation about mean.
    MAD.x = absSum_x / countLine;
    MAD.y = absSum_y / countLine;
    return MAD;
};

////Function to calculate First Quartile


//// Function to calculate skewness.

float skewness(int* array_x, int* array_y, int countLine{
    float sum = 0;
    for (int i = 0; i < countLine; i++)
        sum = (arr[i] - mean(arr, countLine)) *  (arr[i] - mean(arr, countLine)) *  (arr[i] - mean(arr, countLine));
    return sum / (countLine * standardDeviation(arr, countLine) * standardDeviation(arr, countLine) * standardDeviation(arr, countLine) * standardDeviation(arr, countLine));
};


// Main function:
int main() {
    ifstream ip;
    //declare variables
    string filePath, str, str2;
    int count_line;
    Contents *array;

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open the file for reading
    openFile(filePath, ip);

    //start inputting the program contents of csv file
    count_line = findNumberOfLines(str, ip);
    returnToBeginOfFile(ip);
    // create array to store x and y with dynamic memory allocation
    array = new Contents[count_line];
    storeFileIntoArrays(array, str, str2, ip);

    //output array
    // outArray(array, countLine);

    ip.close();
    showTeamInformation();
    return 0;

}
}

// Function detail: