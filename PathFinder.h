#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <iostream>
#include "DataProcessor.h"
#include "Trip.h"

using namespace std;

class PathFinder {
public:
    PathFinder();

    void findPath(int from, int to);
    void findPath(string from, string to);
    void oldFindPath(int start, int end);

    int nameToID(string name);

private:
    void clearPath();
    void updateDistanceTable(int currentAirportId, int distanceToCurrentAirport);
    bool findMinDistanceAirport(int &minAirportId, int &minDistance);
    void showPath(int from, int to);

    DataProcessor dp;
    Airport** airports;
    map<int, vector<int>> routes;
    map<int, int> distanceTo; // { airportId: distance }
    map<int, int> cameFrom; // { destinationAirport: fromAirport }
    enum AIRPORT_STATES { NOT_FOUND = -2, VISITED = -1, NOTVISITES = 0 };
};

#endif // PATHFINDER_H

PathFinder::PathFinder()
{
    airports = dp.getAirports();
    routes = dp.getRoutes();
}

void PathFinder::findPath(int from, int to)
{
    clearPath();
    int currentAirportId = from;
    int distanceToCurrentAirport = 0;

    while (currentAirportId != to)
    {
//        cout << "DEBUG A" << endl;
        distanceTo[currentAirportId] = VISITED;
        updateDistanceTable(currentAirportId, distanceToCurrentAirport);
//        cout << "DEBUG B" << endl;
        int minAirportId, minDistance;
        if (!findMinDistanceAirport(minAirportId, minDistance)) {
            return;
        }
        currentAirportId = minAirportId;
        distanceToCurrentAirport = minDistance;
//        cout << "DEBUG C" << endl;
//        cout << "=======" << endl;

    }

    cout << "Path is found!!!" << endl;
//    cout << "DEBUG D" << endl;
    showPath(from, to);
//    cout << "DEBUG E" << endl;
}

void PathFinder::findPath(string from, string to)
{
    cout << from << " => " << to << endl;
    int start = dp.getAirportIdFor(from), end = dp.getAirportIdFor(to);
    findPath(start, end);
}


void PathFinder::clearPath()
{
    distanceTo.clear();
    cameFrom.clear();
}

void PathFinder::updateDistanceTable(int currentAirportId, int distanceToCurrentAirport)
{
//    cout << "DEBUG A.1" << endl;

    // find airports that reachable from current airport
    vector<int> routeDestinations = routes[currentAirportId];
    Airport* currentAirport = airports[currentAirportId];
//    cout << "DEBUG A.2" << endl;
    // find distance to every destination airports
    for (vector<int>::iterator edge = routeDestinations.begin();
         edge != routeDestinations.end();
         edge++)
    {
//        cout << "DEBUG A.3.1" << endl;
        Airport* edgeAirprot = airports[*edge];
        if (edgeAirprot != NULL) {
            int distance = currentAirport->getDistanceTo(*edgeAirprot)
                    + distanceToCurrentAirport;
//            cout << "DEBUG A.3.1.1" << endl;
            if (distanceTo[*edge] == NOTVISITES) {
                distanceTo[*edge] = distance;
                cameFrom[*edge] = currentAirportId;
            }
            else if (distance < distanceTo[*edge]) {
                distanceTo[*edge] = distance;
                cameFrom[*edge] = currentAirportId;
            }
//            cout << "DEBUG A.3.1.2" << endl;
        }
//        cout << "DEBUG A.3.2" << endl;
    }
//    cout << "DEBUG A.3" << endl;
}

bool PathFinder::findMinDistanceAirport(int & minAirportId, int &minDistance)
{
//    cout << "DEBUG B.1" << endl;
    // find the min in the visited Airport
    map<int, int>::iterator walker = distanceTo.begin();
    minAirportId = NOT_FOUND, minDistance;
    while (walker != distanceTo.end() && distanceTo[walker->first] == VISITED) {
        walker++;
    }
    if (walker == distanceTo.end()) {
        cout << "NO Path Avaliable!" << endl;
        return false;
    }
//    cout << "DEBUG B.2" << endl;
    minAirportId = walker->first;
    minDistance = walker->second;
    walker++;
//    cout << "DEBUG B.3" << endl;
    while (walker != distanceTo.end())
    {
//        cout << "DEBUG B.2.1" << endl;
        int airportId = walker->first, distance = walker->second;
        if (distanceTo[airportId] != VISITED && distance < minDistance) {
            minAirportId = airportId;
            minDistance = distance;
        }
//        cout << "DEBUG B.2.2" << endl;
        walker++;
    }
//    cout << "DEBUG B.4" << endl;
    return true;
}

void PathFinder::showPath(int from, int to)
{
    Trip trip;
//    cout << "DEBUG E.1" << endl;
    int temp;
    for (int at = to; at != from; at = cameFrom[at]) {
        Flight flight(*airports[cameFrom[at]], *airports[at]);
        trip.insertFlight(flight);
        temp = at;
    }
//    cout << "DEBUG E.2" << endl;
    trip.showTrip();
}
