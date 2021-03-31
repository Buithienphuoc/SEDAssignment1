#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Contents{
    public:
        int x, y;
};

// Function declarations:
void showTeamInformation();
void openFile(const string &filePath, ifstream& ip); //open file for reading only
int findNumberOfLines(string x, ifstream& ip);
void returnToBeginOfFile(ifstream& ip);
void storeFileIntoArrays(Contents *array, string str, string str2, ifstream& ip);
void outArray(Contents *array, int count_line);

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
void storeFileIntoArrays(Contents *array, string str, string str2, ifstream& ip) {
    int index = 0;
    string::size_type sz;
    while (ip.good()) {
        getline(ip, str, ',');
        cout << "str: " << str<< endl;
        cout << str << endl;
        // array[index].x = stoi(str,&sz);
        cout << str2 << endl;
        getline(ip, str2, '\n');
        // array[index].y = stoi(str2,&sz);
        index ++;
    }
}
void outArray(Contents *array, int count_line) {
    cout << "The array: \n";
    for (int index = 0; index < count_line; index ++) {
        cout << setw(4) << array[index].x
            << setw(4) << "||"
            << setw(4) << array[index].y << endl;
    }
}
void doExercise1(){
    // add your code here
}
