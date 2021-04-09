#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <iomanip>
//acknowledment: https://www.codespeedy.com/how-to-insert-a-node-in-linked-list-in-cpp/#:~:text=Adding%20a%20node%20at%20the%20front.%201%20First,node%2A%20newnode%20%3D%20%28struct%20node%2A%29%20malloc%28sizeof%28struct%20...%20
using namespace std;

typedef struct {
    int x, y;
} Contents;
struct Node{
    Contents data;
    Node *next;
};
typedef struct Node *nodePtr;

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
        cerr << "ERROR: File Open" << endl;
    }
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
void init(nodePtr &pHead) {
    pHead = NULL;
}
nodePtr createNode(Contents d) {
    nodePtr p = new Node;
    if (p != NULL) {
        p->data = d;
        p->next = NULL;
    }
    return p;
}
void addLastNode(nodePtr &pHead, Contents value) {
    nodePtr newNode = new Node;
    nodePtr lastNode = pHead;
    newNode->data = value;
    newNode->next = NULL;
    if (pHead == NULL) {
        pHead = newNode;
        return;
    }
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    lastNode->next = newNode;
}
int createList(nodePtr &pHead, ifstream &ip, string str) {
    //create list to store file's contents into the list
    Contents d;
    int countLine = 0;
    getline(ip, str); //skip the first line (x,y)
    while (!ip.eof()) {
        getline(ip, str, ',');
        d.x = strToInt(str);
        getline(ip, str, '\n');
        d.y = strToInt(str);
        nodePtr p = createNode(d);
        if (p != NULL) {
            addLastNode(pHead, d);
            countLine ++;
        }
    }
    return countLine;
}
void showList(nodePtr pHead)
{
    for (nodePtr k = pHead; k != NULL;k = k->next) {
        cout << k->data.x << " " << k->data.y << endl;
    }
}

bool checkArguments(int argc) {
    //check number of arguments
    if (argc != 2) {
        cerr << "Invalid number of arguments.";
        return false;
    }
    return true;
}

////Math functions:

Contents mean(nodePtr &pHead, int countLine) {
    Contents m;
    m.x = 0;
    m.y = 0;
    for (nodePtr temp = pHead; temp != nullptr; temp ++) {
        m.x += temp->data.x;
        m.y += temp->data.y;
    }
    m.x /= countLine;
    m.y /= countLine;
    return m;
}

Contents median(nodePtr &pHead, int countLine) {
    nodePtr temp = pHead;
    int index = 0;
    while (temp != NULL) {
        index ++;
        if (countLine % 2 != 0 && index == (countLine % 2)) {
            return temp->data;
        }
        else if (countLine % 2 == 0 && index == (countLine % 2)){
            return temp->data;
        }
    }
}
////Function to calculate Mode
Contents mode(nodePtr &pHead, int countLine) {
    Contents m = mean(pHead, countLine), med = median(pHead, countLine), mod;
    mod.x = m.x - 3 *(m.x -med.x);
    mod.y = m.y - 3 *(m.y -med.y);
    return mod;
}
////Function to calculate Variance
Contents variance(nodePtr &pHead, int countLine) {
    // Compute sum squared
    // differences with mean.
    Contents squaredDiff, m = mean(pHead, countLine);
    for (nodePtr temp = pHead; )
//    for (int i = 1; i < countLine; i++) {
//        squaredDiff += (array[i] - m) * (array[i] - m);
//    }
//    return (squaredDiff / countLine);
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
double firstQuartile(int*array, int countLine){
    double med  = median(array, countLine);
    double med1 = median(array, med);
    return med1;
}

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
void printDouble(string str, double result1, double result2) {
    cout << str << " x = " << result1 << " - " << str << " y = " << result2 << endl;
}
// Main function:
int main(int argc, char *argv[]) {
    ifstream ip;
    nodePtr pHead;

    //check if the arguments are valid
    if (!checkArguments(argc)) {
        showTeamInformation();
        exit(1);
    }

    //declare variables
    string filePath, str, str2;
    int countLine, *array_x, *array_y;

    //ask user to input file's address
    cout << "Hi Dr.Minh Dinh, please type your ABSOLUTE PATH of your file:";
    cin >> filePath;

    //open the file for reading
    openFile(filePath, ip);
    init(pHead);
    countLine = createList(pHead,ip, str);
    ip.close();

    showList(pHead);


    //output the results
    cout << "median x = " <<

    showTeamInformation();
    return 0;
}
