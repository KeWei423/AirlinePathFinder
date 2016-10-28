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
    string airlines[TOTAL_AIRLINES] = {};
};

#endif // PATHFINDER_H

PathFinder::PathFinder()
{
    dp.convertData();
    airports = dp.getAirports();
    routes = dp.getRoutes();
}

void PathFinder::findPath(int from, int to)
{
    while (!airports) {
        dp.convertData();
        airports = dp.getAirports();
    }

    int currentAirport = from;
    int distanceToCurrentAirport = 0;
    map<int, int> visitedAirportDistance; // { airportId: distance }
    map<int, int> fromWhichAirport; // { destinationAirport: fromAirport }
    while (currentAirport != to)
    {
        visitedAirportDistance[currentAirport] = MAX_DISTANCE;
//        cout << visitedAirportDistance << " Destinations" << endl;
//        for (map<int, int>::iterator id = visitedAirportDistance.begin(); id != visitedAirportDistance.end(); id++) {
//            cout << "Visited:" << endl;
//            cout << "    " << id->first << endl;
//            if (airports[id->first]) {
//                cout << "    -" << airports[id->first]->getAirportName() << endl;
//            }
//        }

        // find airports that reachable from current airport
        vector<int> availableDestinationAirports = routes[currentAirport];
        cout << availableDestinationAirports.size() << " Airports availiable." << endl;
        // find distance to every destination airports
//        for (vector<int>::iterator at = availableDestinationAirports.begin(); at != availableDestinationAirports.end(); at)
//        {
//            cout << "    airprot #" << *at << endl;
//            // go through all the airports and put shortest distance in the map
//            Airport* A = airports[currentAirport];
//            if (!A) {
//                cout << "Airprot A is NULL" << endl;
//                break;
//            } else {
//                cout << "Airprot A is GOOD" << endl;
//            }

//            Airport* B = airports[*at];
//            if (!B) {
//                cout << "Airprot B is NULL" << endl;
//                break;
//            } else {
//                cout << "Airprot B is GOOD" << endl;
//            }


//            int distance = A->getDistanceTo(*B);
//            cout << "got distance" << endl;
//            int distanceToDestinationAirport = distance + distanceToCurrentAirport;

//            cout << A->getAirportName()
//                 << " -> " << B->getAirportName()
//                 << " = " << distanceToCurrentAirport
//                 << " + " << distance << endl;

//        }
//        cout << " recored all distance!" << endl;
        break;

        // find the min in the visitedAirport
        int minDistance = MAX_DISTANCE, minAirportId = 0;
        for (map<int, int>::iterator walker = visitedAirportDistance.begin();
             walker != visitedAirportDistance.end(); walker++)
        {
            if (walker->second < minDistance) {
                minAirportId = walker->first;
                minDistance = walker->second;
            }
        }
        if (minAirportId == 0) {
            cout << "No more destinations." << endl;
            return;
        }

        cout << "from " << airports[currentAirport]->getAirportName()
             << " to " << airports[minAirportId]->getAirportName()
             << " : " << minDistance << endl;
        fromWhichAirport[minAirportId] = currentAirport;
        currentAirport = minAirportId;
        distanceToCurrentAirport = minDistance;
    }

    for (map<int, int>::iterator source = fromWhichAirport.find(currentAirport);
         source != fromWhichAirport.end() && source->second != from;
         source = fromWhichAirport.find(source->second)) {
        cout << source->first << " => " << source->second << endl;
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
