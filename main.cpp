#include <iostream>
#include <fstream>

using namespace std;
int main() {
    string filePath;

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open files for reading
    ifstream ip;
    ip.open(filePath, ios::in);
    if (!ip.is_open()) cerr << "ERROR: File Open" << endl;

    //find number of lines to allocate memory for the array of x and y
    int count_line = 0;
    string x_str, y_str;

    while(ip.good() && !ip.eof()){
        getline(ip, x_str, '\n');
        count_line ++;
    }

    //return to the begin of the file
    ip.clear();
    ip.seekg(0);

    //create arrays of x and y with dynamic allocation
    int *x_arr, *y_arr;
    x_arr = new int[count_line], y_arr = new int[count_line];

    //read the file and input the contents into the arrays
    int i = 0;
    while (ip.good() && !ip.eof()) {
        getline(ip, x_str, ',');
        getline(ip, y_str, '\n');
        *(x_arr + i) = stoi(x_str);
        *(y_arr + i) = stoi(y_str);
        i ++;
    }

    //output array
    for (int index = 0; index < count_line; index ++) {
        cout << *(x_arr + index) << *(y_arr + index) << endl;
    }

    ip.close();
    return 0;
}

void doExercise1(){
    // add your code here
}
