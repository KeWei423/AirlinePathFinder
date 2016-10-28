#include <iostream>
#include "PathFinder.h"

using namespace std;

void testDataProcessor();


int main()
{
    /*
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
    */

    testDataProcessor();


    return 0;
}


void testDataProcessor() {
    DataProcessor dp;

    dp.convertData();

    Airport** airports = dp.getAirports();

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        if (airports[i]) {
            cout << airports[i]->getAirportName() << endl;
        } else {
            cout << "Empty" << endl;
        }

    }

}
