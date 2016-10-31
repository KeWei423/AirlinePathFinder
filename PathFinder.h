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

private:
    void clearPath();
    void updateDistanceTable(int currentAirportId, int distanceToCurrentAirport);
    bool findMinDistanceAirport(int &minAirportId, int &minDistance);
    void showPath(int from, int to);
    int nameToID(string name);

    DataProcessor dp;
    Airport** airports;
    map<int, vector<int>> routes;
    map<int, int> distanceTo; // [airportId : distance]
    map<int, int> cameFrom; // [destinationAirport : fromAirport]
    enum AIRPORT_STATES { NOT_FOUND = -2, VISITED = -1, NOTVISITES = 0 };
};

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
        distanceTo[currentAirportId] = VISITED;
        updateDistanceTable(currentAirportId, distanceToCurrentAirport);
        int minAirportId, minDistance;
        if (!findMinDistanceAirport(minAirportId, minDistance)) {
            return;
        }
        currentAirportId = minAirportId;
        distanceToCurrentAirport = minDistance;
    }
    showPath(from, to);
}

void PathFinder::findPath(string from, string to)
{
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
    // find airports that reachable from current airport
    vector<int> routeDestinations = routes[currentAirportId];
    Airport* currentAirport = airports[currentAirportId];
    // find distance to every destination airports
    for (vector<int>::iterator edge = routeDestinations.begin();
         edge != routeDestinations.end();
         edge++)
    {
        Airport* edgeAirprot = airports[*edge];
        if (edgeAirprot != NULL) {
            int distance = currentAirport->getDistanceTo(*edgeAirprot)
                    + distanceToCurrentAirport;
            if (distanceTo[*edge] == NOTVISITES) {
                distanceTo[*edge] = distance;
                cameFrom[*edge] = currentAirportId;
            }
            else if (distance < distanceTo[*edge]) {
                distanceTo[*edge] = distance;
                cameFrom[*edge] = currentAirportId;
            }
        }
    }
}

bool PathFinder::findMinDistanceAirport(int & minAirportId, int &minDistance)
{
    // find the min in the visited Airport
    map<int, int>::iterator walker = distanceTo.begin();
    minAirportId = NOT_FOUND;
    while (walker != distanceTo.end() && distanceTo[walker->first] == VISITED) {
        walker++;
    }
    if (walker == distanceTo.end()) {
        cout << "NO Path Avaliable!" << endl;
        return false;
    }
    minAirportId = walker->first;
    minDistance = walker->second;
    walker++;
    while (walker != distanceTo.end())
    {
        int airportId = walker->first, distance = walker->second;
        if (distanceTo[airportId] != VISITED && distance < minDistance) {
            minAirportId = airportId;
            minDistance = distance;
        }
        walker++;
    }
    return true;
}

void PathFinder::showPath(int from, int to)
{
    Trip trip(airports[from]->getAirportInfo(), airports[to]->getAirportInfo());
    int temp;
    for (int at = to; at != from; at = cameFrom[at]) {
        Flight flight(*airports[cameFrom[at]], *airports[at]);
        trip.insertFlight(flight);
        temp = at;
    }
    trip.showTrip();
}

#endif // PATHFINDER_H
