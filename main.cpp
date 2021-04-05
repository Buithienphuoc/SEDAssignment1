#include <iostream>
#include <fstream>
#include <cmath>

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
    int index = 0; //run i 1++, b/c i 0 is 'x','y'
    while (!ip.eof()) {
        getline(ip, str, ',');
        array_x[index] = strToInt(str);
        getline(ip, str, '\n');
        array_y[index] = strToInt(str);
        index ++;
    }
    cout << "Number of line:" <<index << endl;

    for (int element = 1; element < index ; element++){
        cout << element << " place of Array X:" << array_x[element] << endl
             << element << " place of Array Y:" << array_y[element] << endl
             << "--------------------------" << endl;
    }
}

// Main function:
int main() {
    //declare variables
    ifstream ip;
    string filePath, str, str2;
    int count_line, *array_x, *array_y;
    count_line = findNumberOfLines(str, ip);
    array_x = new int[count_line];
    array_y = new int[count_line];

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open the file for reading
    openFile(filePath, ip);

    //start inputting the program contents of csv file
    returnToBeginOfFile(ip);
    // create array to store x and y with dynamic memory allocation

    storeFileIntoArrays(array_x, array_y, str, ip);

    ip.close();
    showTeamInformation();
    return 0;
}

