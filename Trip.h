#ifndef TRIP_H
#define TRIP_H

#include <stack>
#include "Flight.h"

class Trip
{
public:
    Trip();

    void insertFlight(Flight flight);
    void showTrip();

private:
    stack<Flight> flights;
};

Trip::Trip()
{

}

void Trip::insertFlight(Flight flight)
{
    flights.push(flight);
}

void Trip::showTrip()
{
    while(!flights.empty()) {
        flights.top().showFlightDetail();
        flights.pop();
    }

}

#endif // TRIP_H
