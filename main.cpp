#include <QCoreApplication>
#include <QtXml/qdom.h>
#include "DataProcessor.h"
#include <iostream>
#include <ctime>
#include <QFile>
#include <QXmlStreamReader>
#include <vector>
#include <QString>
#include "Airport.h"
#include <cctype>
#include "PathFinder.h"

using namespace std;

bool getInput(int &source, int &dest);

int main()
{
    PathFinder pf;
    int A,B;
    while(getInput(A, B)){
        pf.findPath(A, B);
    }
    cout << "END of PROGRAM" << endl;
    return 0;
}
bool getInput(int &source, int &dest)
{
    string A, B;
    cout << endl << "Enter 0 to quit the program." << endl
         << "Pleace enter SOURCE airport name(LAX):";
    cin >> A;
    if(A=="0")
        return false;
    for(int i = 0; i < A.size(); ++i)
        A[i] = toupper(A[i]);
    source = name2number(A);
    cout << endl << "Destination(JFK):" << endl;
    cin >> B;
    for(int i = 0; i < B.size(); ++i)
        B[i] = toupper(B[i]);
    dest = name2number(B);
    cout << endl;
    if(source && dest)
        return true;
    source = dest = 0;
    cout << "can not find the airport(s) entered, please try again." << endl;
    return getInput(source, dest);
}
