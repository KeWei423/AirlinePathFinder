#ifndef AIRPORT
#define AIRPORT
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "constnumber.h"
#include <stdio.h>
const double radiusOfEarth = 3959;// (6,371 km)
const double PI = 3.1415926;
const int matrixSize = 9542;
const double maxD = 2 * PI * radiusOfEarth;
const int totalAirlines = 19846;

using namespace std;
class Airport{
public:
    Airport();
    void set(int _id, string _name, string _city, string _country, double _latitude, double _lontitude);
    void addDest(int airportID, int distance, int _ID);
    int distance(Airport dest);
    string info();
    int numberOfDestinations();
    void to(int i, int &d, int &id, int &airID);
    int& from();
    void theAirID(int id);
    string showAvailibleAirlines(string airlines[]);
    string theName();

private:
    int ID;
    string name, city, country;
    double latitude, lontitude;
    //edges
    vector<int> destID;
    vector<int> dist;
    vector<int> airlineID;
    //shortest distance and available airlines
    int shortest, preShortest;
    vector<int> available_airline;
};

Airport::Airport()
{
    shortest = preShortest = ID = 0; name = string(); city = string(); country = string();
}

void Airport::set(int _id, string _name, string _city, string _country, double _latitude, double _lontitude)
{
    ID = _id; name = _name; city = _city; country = _country; latitude = _latitude; lontitude = _lontitude;
}

void Airport::addDest(int airportID, int distance, int _ID)
{
    destID.push_back(airportID);
    dist.push_back(distance);
    airlineID.push_back(_ID);
}

int Airport::distance(Airport dest)
{
    return radiusOfEarth
           * acos(sin(latitude*PI/180)*sin( dest.latitude*PI/180 )
                + cos( latitude*PI/180 )*cos( dest.latitude*PI/180 )*cos( abs(dest.lontitude-lontitude) * PI/180) ) ;
}

string Airport::info()
{
    string temp = name + "(" + city+ ")";
    return temp;
}

int Airport::numberOfDestinations()
{
    return destID.size();
}

void Airport::to(int i, int &d, int &id, int &_airID)
{
    id = destID[i];
    d = dist[i];
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

string Airport::showAvailibleAirlines(string airlines[])
{
    string temp = airlines[available_airline[0]];
    for(int i = 1; i < available_airline.size(); ++i)
    {
        temp.append(" or " + airlines[available_airline[i]]);
    }
    return temp;
}

string Airport::theName()
{
    return name;
}

#endif // AIRPORT
