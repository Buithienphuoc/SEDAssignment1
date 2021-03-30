#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream ip;
class Contents{
    public:
        int x, y;
};

// Function declarations:
void showTeamInformation();
void openFile(const string &filePath); //open file for reading only
int findNumberOfLines(string x);
void returnToBeginOfFile();
void storeFileIntoArrays(Contents *array, string str, string str2);
void outArray(Contents *array, int count_line);

// Main function:
int main() {
    //declare variables
    string filePath, str, str2;
    int count_line;
    Contents *array;

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open the file for reading
    openFile(filePath);

    //start inputting the program contents of csv file
    count_line = findNumberOfLines(str);
    returnToBeginOfFile();
    //create array to store x and y with dynamic memory allocation
    array = new Contents[count_line];
    storeFileIntoArrays(array, str, str2);

    //output array
    outArray(array, count_line);

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
void openFile(const string& filePath) {
    ip.open(filePath, ios::in);
    if (!ip.is_open()) {
        showTeamInformation();
        cerr << "ERROR: File Open" << endl;
    }
}
int findNumberOfLines(string x) {
    int count = 0;
    while (ip.good()) {
        getline(ip, x, '\n');
        count ++;
    }
    return count;
}
void returnToBeginOfFile() {
    ip.clear();
    ip.seekg(1);
}
void storeFileIntoArrays(Contents *array, string str, string str2) {
    int index = 0;
    while (ip.good()) {
        getline(ip, str, ',');
        cout << "str: " << str<< endl;
        array[index].x = stoi(str);
        getline(ip, str2, '\n');
        array[index].y = stoi(str2);
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
