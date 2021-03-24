#include <iostream>
#include <fstream>

using namespace std;
int main() {
    string filePath;
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;
    ifstream ip(filePath);
    if (!ip.is_open()) cout << "ERROR: File Open" << endl;

    string x;
    string y;

    while(ip.good()){
        getline(ip,x,',');
        getline(ip, y, '\n');

        cout << "x:" << x << endl
             << "y:" << y << endl << endl;
    }
    ip.close();
    return 0;
}
