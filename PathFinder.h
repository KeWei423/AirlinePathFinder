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
    void oldFindPath(int start, int end);

    int nameToID(string name);

private:
    DataProcessor dp;
    Airport** airports;
    map<int, vector<int>> routes;
    //    string airlines[TOTAL_AIRLINES] = {};
};

#endif // PATHFINDER_H

PathFinder::PathFinder()
{
    airports = dp.getAirports();
    routes = dp.getRoutes();
}

void PathFinder::findPath(int from, int to)
{
    while (!airports) {
        airports = dp.getAirports();
    }

    int currentAirport = from;
    int distanceToCurrentAirport = 0;
    map<int, int> visitedAirportDistance; // { airportId: distance }
    map<int, int> fromTable; // { destinationAirport: fromAirport }
    visitedAirportDistance[currentAirport] = -1;

    while (currentAirport != to)
    {
        // find airports that reachable from current airport
        vector<int> availableDestinationAirports = routes[currentAirport];

        int added = 0;
        // find distance to every destination airports
        for (vector<int>::iterator at = availableDestinationAirports.begin();
             at != availableDestinationAirports.end();
             at++)
        {
            Airport* A = airports[currentAirport];
            Airport* B = airports[*at];
            int distance = A->getDistanceTo(*B);

            int distanceFromStartToHere = distance + distanceToCurrentAirport;
            int distanceRecorded = visitedAirportDistance[*at];

            if (distanceRecorded == 0) {
                visitedAirportDistance[*at] = distanceFromStartToHere;
                fromTable[*at] = currentAirport;
            }
            else if (distanceFromStartToHere < distanceRecorded){
                visitedAirportDistance[*at] = distanceFromStartToHere;
                fromTable[*at] = currentAirport;
            }
        }

        // find the min in the visitedAirport
        int minDistance = MAX_DISTANCE, minAirportId = 0;
        for (map<int, int>::iterator walker = visitedAirportDistance.begin();
             walker != visitedAirportDistance.end(); walker++)
        {
            if (walker->second != -1 && walker->second < minDistance) {
                minAirportId = walker->first;
                minDistance = walker->second;
            }
        }
        if (minAirportId == 0) {
            cout << "No more destinations." << endl;
            return;
        }

        currentAirport = minAirportId;
        distanceToCurrentAirport = minDistance;
        visitedAirportDistance[currentAirport] = -1;
    }
    cout << "Path is found!!!" << endl;
    int at = to;
    map<int, int>::iterator atIt;

    while (at != from && atIt != fromTable.end()) {

        cout << at << " from ";
        atIt = fromTable.find(at);
        if (atIt != fromTable.end()) {
            at = atIt->second;
        }

        cout << at << endl;

//        cout << airports[at]->getAirportInfo() <<
//                " is came from "
//             << airports[fromTable[at]]->getAirportInfo()
//            << " at " << airports[at]->getDistanceTo(*airports[fromTable[at]]) << " miles away" << endl;
//        at = fromTable[at];
    }
}

void PathFinder::findPath(string from, string to)
{
    int start = dp.getAirportIdFor(from), end = dp.getAirportIdFor(to);
    cout << start << " => " << end << endl;
    findPath(start, end);
    //    oldFindPath(start, end);
}


void PathFinder::oldFindPath(int start, int end)
{
    /*
    int minDistance[SIZE], visited[SIZE];
    int d, id, pre, airlineID, holder = start;
    int nextVisit = start, minD;
    bool reachDest = false, DEADEND = false;;

    //initiallize all vectors to 0
    for(int i = 0; i < SIZE; ++i){
        minDistance[i] = MAX_DISTANCE;
        visited[i] = 0;
        airports[i].from() = start;
    }
    minDistance[start] = 0;
    while(!reachDest){
        DEADEND = true;
        visited[nextVisit] = 1;
        start = nextVisit;
        for(int i = 0; i < airports[start].getDestinationCount(); ++i){
            airports[start].to(i, d, id, airlineID);//get id of #i destination airport and its airport id;
            d += minDistance[start];
            if(!visited[id] &&  d <= minDistance[id])//if the new distance is shorter, replace the old distance with new distance;
            {
                minDistance[id] = d;
                airports[id].from() = start;
                airports[id].theAirID(airlineID);
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
    cout << endl << "Shortest flight distance from " << airports[holder].getAirportInfo() <<" to " << airports[end].getAirportInfo() << " is " << minDistance[end] << endl << endl;

    // ==================================================
    int A = start, B = end;
    int walker = 0, last;
    vector<int> route;
    route.push_back(B);
    walker = B;
    while(walker!=A){
        walker = airports[walker].from();
        route.push_back(walker);
    }
    last = route.size()-1;
    cout << "Leave " << airports[route[last]].getAirportInfo()
         << " on " << airports[route[last-1]].showAvailibleAirlines(airlines)
         << " after flying " << airports[route[last]].getDistanceTo(airports[route[last-1]]) << " miles" << endl << endl;
    for(int i = last-1; i > 0; --i){
        cout << "Change planes at "<< airports[route[i]].getAirportInfo()
             << " on " << airports[route[i]].showAvailibleAirlines(airlines)
             << " after flying " << airports[route[i]].getDistanceTo(airports[route[i-1]]) << " miles" << endl << endl;
    }
    cout << "Arrive  at " << airports[route[0]].getAirportInfo();
    cout << endl << endl;
    */
}
