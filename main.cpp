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
#include "constnumber.h"
#include <cctype>

using namespace std;
Airport matrix[matrixSize];
string airlines[totalAirlines] = {};

void reLoadData(char *airportFrom, char *airportTo, char *routeFrom, char *routeTo);
void findPath(int A, int B);
void showPath(int A, int B);
bool getInput(int &source, int &dest);

int main()
{
    reLoadData("airports.dat", "airports.xml", "routes.dat", "routes.xml");
    readAirport(matrix, "airports.xml");
    readRoutes(matrix, "routes.xml");
    readAirlines(airlines, "airlines.dat");
    int A,B;
    while(getInput(A, B)){
        findPath(A, B);
        showPath(A, B);
    }
    cout << "END of PROGRAM" << endl;
    return 0;
}

void reLoadData(char *airportFrom, char *airportTo, char *routeFrom, char *routeTo)
{
    airport2xml(airportFrom, airportTo);
    routes2xml(routeFrom, routeTo);
}

void findPath(int start, int end)
{
    int minDistance[matrixSize], visited[matrixSize];
    int d, id, pre, airlineID, holder = start;
    int nextVisit = start, minD;
    bool reachDest = false, DEADEND = false;;

    //initiallize all vectors to 0
    for(int i = 0; i < matrixSize; ++i){
        minDistance[i] = maxD;
        visited[i] = 0;
        matrix[i].from() = start;
    }
    minDistance[start] = 0;
    while(!reachDest){
        DEADEND = true;
        visited[nextVisit] = 1;
        start = nextVisit;
        for(int i = 0; i < matrix[start].numberOfDestinations(); ++i){
            matrix[start].to(i, d, id, airlineID);//get id of #i destination airport and its airport id;
            d += minDistance[start];
            if(!visited[id] &&  d <= minDistance[id])//if the new distance is shorter, replace the old distance with new distance;
            {
                minDistance[id] = d;
                matrix[id].from() = start;
                matrix[id].theAirID(airlineID);
            }
        }
        //find the min distance
        minD = maxD;
        pre = nextVisit;
        for(int i = 0; i < matrixSize; ++i){
            if(!visited[i] && minD > minDistance[i]){
                minD = minDistance[i];
                nextVisit = i;
            }
        }
        reachDest = visited[end];
    }
    cout << endl << "Shortest flight distance from " << matrix[holder].info() <<" to " << matrix[end].info() << " is " << minDistance[end] << endl << endl;
}

void showPath(int A, int B)
{
    int walker = 0, last;
    vector<int> route;
    route.push_back(B);
    walker = B;
    while(walker!=A){
        walker = matrix[walker].from();
        route.push_back(walker);
    }
    last = route.size()-1;
    cout << "Leave " << matrix[route[last]].info()
         << " on " << matrix[route[last-1]].showAvailibleAirlines(airlines)
         << " after flying " << matrix[route[last]].distance(matrix[route[last-1]]) << " miles" << endl << endl;
    for(int i = last-1; i > 0; --i){
        cout << "Change planes at "<< matrix[route[i]].info()
             << " on " << matrix[route[i]].showAvailibleAirlines(airlines)
             << " after flying " << matrix[route[i]].distance(matrix[route[i-1]]) << " miles" << endl << endl;
    }
    cout << "Arrive  at " << matrix[route[0]].info();
    cout << endl << endl;
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
