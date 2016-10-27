#include <iostream>
#include "PathFinder.h"

using namespace std;

int main()
{
    PathFinder pf;
    string from, to;

    while( true ) {
        cout << "======================================" << endl
             << "Enter 0 to quit the program.          " << endl
             << "Pleace enter SOURCE airport name(LAX):" << endl;
        cin >> from;
        if (from == "0") { break; }
        cout << "Pleace enter DESTINATION:" << endl;
        cin >> to;
        if (to == "0") {  break; }
        cout << "======================================" << endl;
        pf.findPath(from, to);
    }
    return 0;
}
