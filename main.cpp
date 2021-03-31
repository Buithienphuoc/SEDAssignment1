#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
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
void doExercise1(){
    // add your code here
}

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
    // outArray(array, count_line);

    ip.close();
    showTeamInformation();
    return 0;
}

// Function detail:
