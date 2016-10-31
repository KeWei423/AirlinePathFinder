#ifndef TRIP_H
#define TRIP_H

#include <stack>
#include "Flight.h"

class Trip
{
public:
    Trip();
    Trip(string _from, string _to);

    void insertFlight(Flight flight);
    void showTrip();

private:
    stack<Flight> flights;
    string from, to;
};

Trip::Trip()
{
    from = to = "Unknown";
}

Trip::Trip(string _from, string _to)
{
    from = _from;
    to = _to;
}

void Trip::insertFlight(Flight flight)
{
    flights.push(flight);
}

void Trip::showTrip()
{
    if (flights.size() > 1) {
        int counter = 1;
        cout << "Trip from " << from << " to " << to << " required " << flights.size() << " flights:" << endl;
        while(!flights.empty()) {
            cout << "    #" << counter++ << ": ";
            flights.top().showFlightDetail();
            flights.pop();
        }
    } else if (flights.size() == 1) {
        cout << "Non-stop trip:" << endl;
        flights.top().showFlightDetail();
        flights.pop();
    } else {
        cout << "There is no route avaliable from " << from << " to " << to << endl;
    }
    cout << endl << endl;
}

#endif // TRIP_H
