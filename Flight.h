#ifndef FLIGHT_H
#define FLIGHT_H

#include "Airport.h"

class Flight {
public:
    Flight(Airport _from, Airport _to);
    void showFlightDetail();

    friend
    bool operator ==(const Flight& LHS, const Flight& RHS);

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
    cout << "From " << from.getAirportInfo() << " to " << to.getAirportInfo() << endl;
}

bool operator ==(const Flight &LHS, const Flight &RHS)
{
    return LHS.from == RHS.from && LHS.to == RHS.to;
}

#endif // FLIGHT_H
