#ifndef FLIGHT_H
#define FLIGHT_H

#include "Airport.h"

class Flight {
public:
    Flight();
    Flight(const Flight& other);
    Flight(Airport _from, Airport _to);
    void showFlightDetail();
    void operator =(const Flight& other);

    friend
    bool operator ==(const Flight& LHS, const Flight& RHS);

private:
    void copy(const Flight& other);

    Airport from, to;
};

Flight::Flight()
{

}

Flight::Flight(const Flight &other)
{
    copy(other);
}

Flight::Flight(Airport _from, Airport _to)
{
    from = _from;
    to = _to;
}

void Flight::showFlightDetail()
{
    cout << "From " << from.getAirportInfo() << " to " << to.getAirportInfo() << endl;
}

void Flight::operator =(const Flight &other)
{
    copy(other);
}

void Flight::copy(const Flight &other)
{
    from = other.from;
    to = other.to;
}

bool operator ==(const Flight &LHS, const Flight &RHS)
{
    return LHS.from == RHS.from && LHS.to == RHS.to;
}

#endif // FLIGHT_H
