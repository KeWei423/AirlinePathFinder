#ifndef DATAPROCESSORTEST_H
#define DATAPROCESSORTEST_H

#include "DataProcessor.h"

class DataProcessorTester
{
public:
    DataProcessorTester();
    bool run();
    bool testDataProcessor();
    bool testGetRoutes();

private:
    DataProcessor dp;
};

DataProcessorTester::DataProcessorTester()
{
    dp = DataProcessor();
}

bool DataProcessorTester::run()
{
    testDataProcessor();
    testGetRoutes();
}

bool DataProcessorTester::testDataProcessor()
{
    Airport** airports = dp.getAirports();
    int counter = 0;
    for (int i = 0; i < SIZE; i++) {
        counter += airports[i] ? 1 : 0;
    }
    if (counter == 8099) {
        return true;
    }
    return false;
}

bool DataProcessorTester::testGetRoutes()
{
    map<int, vector<int>> routes = dp.getRoutes();
    string input;
    cout << "Enter airport name to find number of destinations. 0 to quit." << endl;
    while (cin >> input) {
        if (input == "0") {
            return true;
        }
        int id = dp.getAirportIdFor(input);
        vector<int> destinations = routes[id];
        cout << destinations.size() << " destinations" << endl;
    }
}
#endif // DATAPROCESSORTEST_H
