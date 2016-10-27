#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <iostream>
#include "DataProcessor.h"
using namespace std;

class PathFinder {
public:
    PathFinder();

    void findPath(int from, int to);
    void findPath(string from, string to);

    int nameToID(string name);

private:
    DataProcessor dp;
    Airport* matrix;
    string airlines[TOTAL_AIRLINES] = {};
};

#endif // PATHFINDER_H

PathFinder::PathFinder()
{
    dp.reloadData();
    matrix = dp.getAirports();
}

void PathFinder::findPath(int start, int end)
{
    int minDistance[SIZE], visited[SIZE];
    int d, id, pre, airlineID, holder = start;
    int nextVisit = start, minD;
    bool reachDest = false, DEADEND = false;;

    //initiallize all vectors to 0
    for(int i = 0; i < SIZE; ++i){
        minDistance[i] = MAX_DISTANCE;
        visited[i] = 0;
        matrix[i].from() = start;
    }
    minDistance[start] = 0;
    while(!reachDest){
        DEADEND = true;
        visited[nextVisit] = 1;
        start = nextVisit;
        for(int i = 0; i < matrix[start].getDestinationCount(); ++i){
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
        minD = MAX_DISTANCE;
        pre = nextVisit;
        for(int i = 0; i < SIZE; ++i){
            if(!visited[i] && minD > minDistance[i]){
                minD = minDistance[i];
                nextVisit = i;
            }
        }
        reachDest = visited[end];
    }
    cout << endl << "Shortest flight distance from " << matrix[holder].getAirportInfo() <<" to " << matrix[end].getAirportInfo() << " is " << minDistance[end] << endl << endl;

    // ==================================================
    int A = start, B = end;
    int walker = 0, last;
    vector<int> route;
    route.push_back(B);
    walker = B;
    while(walker!=A){
        walker = matrix[walker].from();
        route.push_back(walker);
    }
    last = route.size()-1;
    cout << "Leave " << matrix[route[last]].getAirportInfo()
         << " on " << matrix[route[last-1]].showAvailibleAirlines(airlines)
         << " after flying " << matrix[route[last]].getDistanceTo(matrix[route[last-1]]) << " miles" << endl << endl;
    for(int i = last-1; i > 0; --i){
        cout << "Change planes at "<< matrix[route[i]].getAirportInfo()
             << " on " << matrix[route[i]].showAvailibleAirlines(airlines)
             << " after flying " << matrix[route[i]].getDistanceTo(matrix[route[i-1]]) << " miles" << endl << endl;
    }
    cout << "Arrive  at " << matrix[route[0]].getAirportInfo();
    cout << endl << endl;
}

void PathFinder::findPath(string from, string to)
{
    int start = dp.getAirportIdFor(from), end = dp.getAirportIdFor(to);
    cout << start << " => " << end << endl;
//    findPath(start, end);
}
