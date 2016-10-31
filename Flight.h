#ifndef FLIGHT_H
#define FLIGHT_H

#include "Airport.h"

class Flight {
public:
    Flight(Airport _from, Airport _to);
    void showFlightDetail();

private:
    Airport from, to;
};

Flight::Flight(Airport _from, Airport _to)
{
    from = _from;
    to = _to;
}

void Flight::showFlightDetail()
{
    cout << "Trip from " << from.getAirportInfo() << " to " << to.getAirportInfo() << endl;
}

#endif // FLIGHT_H
