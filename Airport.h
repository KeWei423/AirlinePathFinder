#ifndef AIRPORT
#define AIRPORT
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

const double EARTH_RADIUS = 3959; // (6,371 km)
const double PI = 3.1415926;
const int SIZE = 9542;

using namespace std;
class Airport{
public:
    Airport();
    Airport(const Airport& other);
    Airport(int _id, string _name, string _city, double _latitude, double _longtitude);

    int getDistanceTo(Airport dest);
    string getAirportInfo();
    string getAirportName();
    void operator =(const Airport& other);

    friend
    bool operator ==(const Airport& LHS, const Airport& RHS);

private:
    void copy(const Airport& other);

    int ID;
    string name, city;
    double latitude, longtitude;
};

Airport::Airport()
{
    name = city = "Not Initialized";
    latitude = longtitude = 0;
}

Airport::Airport(const Airport &other)
{
    copy(other);
}

Airport::Airport(int _id, string _name, string _city, double _latitude, double _longtitude)
{
    ID = _id;
    name = _name;
    city = _city;
    latitude = _latitude;
    longtitude = _longtitude;
}

void Airport::operator =(const Airport &other)
{
    copy(other);
}

int Airport::getDistanceTo(Airport dest)
{
    double distance =
            EARTH_RADIUS
            * acos(sin(latitude*PI/180)
                   * sin( dest.latitude*PI/180 )
                   + cos( latitude*PI/180 )
                   * cos( dest.latitude*PI/180 )
                   * cos( abs(dest.longtitude-longtitude) * PI/180) ) ;
    return distance;
}

string Airport::getAirportInfo()
{
    return name + "(" + city+ ")";
}

void Airport::copy(const Airport &other)
{
    ID = other.ID;
    name = other.name;
    city = other.city;
    latitude = other.latitude;
    longtitude = other.longtitude;
}

string Airport::getAirportName()
{
    return name;
}


bool operator ==(const Airport &LHS, const Airport &RHS)
{
    return LHS.ID == RHS.ID &&
            LHS.name == RHS.name &&
            LHS.city == RHS.city &&
            LHS.latitude == RHS.latitude &&
            LHS.longtitude == RHS.longtitude;
}

#endif // AIRPORT
