#include <iostream>
#include "PathFinder.h"

using namespace std;

int main()
{
    PathFinder pf;
    string from, to;
    cout << "======================================" << endl
         << "Enter 0 to quit the program.          " << endl
         << "Pleace enter SOURCE airport name(LAX):" << endl;
    cin >> from;
    cout << "Pleace enter DESTINATION:" << endl;
    cin >> to;
    cout << "======================================" << endl;
    pf.findPath(from, to);
    return 0;
}
