#ifndef AIRPORT
#define AIRPORT
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

const double EARTH_RADIUS = 3959;// (6,371 km)
const double PI = 3.1415926;
const int SIZE = 9542;
const double MAX_DISTANCE = 2 * PI * EARTH_RADIUS;
const int TOTAL_AIRLINES = 19846;

using namespace std;
class Airport{
public:
    Airport();
    Airport(const Airport& other);
    Airport(int _id, string _name, string _city, double _latitude, double _lontitude);

    int getDestinationCount();
    int getDistanceTo(Airport dest);
    string getAirportInfo();
    void addDestination(int airportID, int getDistanceTo, int _ID);
    string getAirportName();
    void operator =(const Airport& other);
    vector<int> getAvailableDestinationAirports();


    // TODO: clean up needed functions
    string showAvailibleAirlines(string airlines[]);
    void to(int i, int &d, int &id, int &airID);
    int& from();
    void theAirID(int id);

private:
    void copy(const Airport& other);

    int ID;
    string name, city;
    double latitude, lontitude;
    //edges
    vector<int> destinationAirports;
    vector<int> distance;
    vector<int> airlineID;

    //shortest distance and available airlines
    int shortest, preShortest;
    vector<int> available_airline;
};

Airport::Airport()
{
    shortest = preShortest = ID = 0;
}

Airport::Airport(const Airport &other)
{
    copy(other);
}

Airport::Airport(int _id, string _name, string _city, double _latitude, double _lontitude)
{
    ID = _id;
    name = _name;
    city = _city;
    latitude = _latitude;
    lontitude = _lontitude;
}

void Airport::operator =(const Airport &other)
{
    copy(other);
}

vector<int> Airport::getAvailableDestinationAirports()
{
    cout << "Number of availiable airports:" << destinationAirports.size() << endl;
    return destinationAirports;
}

void Airport::addDestination(int airportID, int _distance, int _ID)
{
    destinationAirports.push_back(airportID);
    distance.push_back(_distance);
    airlineID.push_back(_ID);
}

int Airport::getDistanceTo(Airport dest)
{
    return EARTH_RADIUS
           * acos(sin(latitude*PI/180)*sin( dest.latitude*PI/180 )
                + cos( latitude*PI/180 )*cos( dest.latitude*PI/180 )*cos( abs(dest.lontitude-lontitude) * PI/180) ) ;
}

string Airport::getAirportInfo()
{
    return name + "(" + city+ ")";
}

int Airport::getDestinationCount()
{
    return destinationAirports.size();
}

void Airport::to(int i, int &d, int &id, int &_airID)
{
    id = destinationAirports[i];
    d = distance[i];
    _airID = airlineID[i];
}

int& Airport::from()
{
    return shortest;
}

void Airport::theAirID(int id)
{
    if(preShortest!=shortest){
        available_airline.clear();
        preShortest = shortest;
    }
    if(available_airline.size()>1 && available_airline[0] == id)
        return;
    available_airline.push_back(id);
}

void Airport::copy(const Airport &other)
{
    ID = other.ID;
    name = other.name;
    city = other.city;
    latitude = other.latitude;
    lontitude = other.lontitude;
}

string Airport::showAvailibleAirlines(string airlines[])
{
    string temp = airlines[available_airline[0]];
    for(unsigned long i = 1; i < available_airline.size(); ++i)
    {
        temp.append(" or " + airlines[available_airline[i]]);
    }
    return temp;
}

string Airport::getAirportName()
{
    return name;
}

#endif // AIRPORT
