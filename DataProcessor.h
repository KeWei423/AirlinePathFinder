#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H
#include <fstream>
#include <iostream>
#include <map>
#include <QCoreApplication>
#include <QFile>
#include <qstring.h>
#include <QtXml/qdom.h>
#include <QXmlStreamWriter>
#include "Airport.h"
using namespace std;

class DataProcessor {
public:
    DataProcessor(string _airportDataFilename ="airports.dat",
                  string _airportXmlFilename = "airports.xml",
                  string _routeDataFilename = "routes.dat",
                  string _routeXmlFilename = "routes.xml");
    ~DataProcessor();

    Airport** getAirports(bool refresh = false);
    int getAirportIdFor(string name);
    const map<int, vector<int> > getRoutes();

private:
    bool airportDataToXml();
    void convertData();
    bool routesDataToXml();
    void nukem();

    string airportDataFilename;
    string airportXmlFilename;
    string routeDataFilename;
    string routeXmlFilename;
    map<string, int> airportIATA;
    map<string, int> airportICAO;
    Airport** airports;
};

DataProcessor::DataProcessor(string _airportDataFilename,
                             string _airportXmlFilename,
                             string _routeDataFilename,
                             string _routeXmlFilename)
{
    airportDataFilename = _airportDataFilename;
    airportXmlFilename = _airportXmlFilename;
    routeDataFilename = _routeDataFilename;
    routeXmlFilename = _routeXmlFilename;

    convertData();

    airports = NULL;
}

DataProcessor::~DataProcessor()
{
//    nukem();
}

Airport **DataProcessor::getAirports(bool refresh)
{
    if (refresh == true) {
        convertData();
    }

    QFile file(airportXmlFilename.c_str());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << airportXmlFilename << " can not be open!" << endl;
        return airports;
    }
    cout << "Opened " << airportXmlFilename << endl;
    QDomDocument XML;
    if(!XML.setContent(&file)) {
        cout << " fail to load content" << endl;
        return airports;
    }

    int id;
    double latitude, longitude;;
    string IATA, city, ICAO;
    QDomElement root = XML.firstChildElement();
    QDomNodeList airportNodeList = root.elementsByTagName("airportID");
    QDomNode routeNode;
    QDomElement routeElement;

    nukem();
    airports = new Airport*[SIZE] {};
    for(int i = 0; i < airportNodeList.size(); ++i)
    {
        //convert to element
        routeNode = airportNodeList.at(i);
        routeElement = routeNode.toElement();
        //get the text elements
        id = routeElement.text().toInt();
        routeElement = routeElement.nextSiblingElement("IATA");
        IATA = routeElement.text().toStdString();
        routeElement = routeElement.nextSiblingElement("ICAO");
        ICAO = routeElement.text().toStdString();
        routeElement = routeElement.nextSiblingElement("city");
        city = routeElement.text().toStdString();
        routeElement = routeElement.nextSiblingElement("latitude");
        latitude = routeElement.text().toDouble();
        routeElement = routeElement.nextSiblingElement("longitude");
        longitude = routeElement.text().toDouble();
        if(latitude && longitude) {
            airports[id] = new Airport(id, IATA, city, latitude, longitude);
            airportIATA[IATA] = airportICAO[ICAO] = id;
        }
    }
    file.close();
    cout << "Airports loaded." << endl;
    return airports;
}

int DataProcessor::getAirportIdFor(string name)
{
    for(unsigned long i = 0; i < name.size(); ++i)
    {
        name[i] = toupper(name[i]);
    }
    map<string, int>::iterator id = airportIATA.find(name);
    if ( id != airportIATA.end()) {
        return id->second;
    }
    id = airportICAO.find(name);
    if ( id != airportIATA.end()) {
        return id->second;
    }
    return 0;
}

const map<int, vector<int> > DataProcessor::getRoutes()
{
    map<int, vector<int> > routes;

    QFile file(routeXmlFilename.c_str());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << routeXmlFilename << " can not be open!" << endl;
        return routes;
    }
    cout << "Opened " << routeXmlFilename << endl;
    QDomDocument XML;
    if(!XML.setContent(&file)) {
        cout << "Fail to load content in " << routeXmlFilename << endl;
        return routes;
    }

    short sourceAirportID, destinationAirportID, airlineID;
    QDomElement root = XML.firstChildElement();
    QDomNodeList routeNodeList = root.elementsByTagName("source");
    QDomNode routeNode;
    QDomElement routeElement;
    int counter = 0;
    for(int i = 0; i < routeNodeList.count(); ++i)
    {
        routeNode = routeNodeList.at(i);
        routeElement = routeNode.toElement();
        sourceAirportID = routeElement.text().toShort();
        routeElement = routeElement.nextSiblingElement("dest");
        destinationAirportID = routeElement.text().toShort();
        routeElement = routeElement.nextSiblingElement("airlineID");
        airlineID = routeElement.text().toShort();
        if(sourceAirportID && destinationAirportID) {
            ++counter;
            routes[sourceAirportID].push_back(destinationAirportID);
        }
    }
    cout << counter << " routes were loaded." << endl;
    return routes;
}

void DataProcessor::convertData()
{
    cout << "Converting data to xml." << endl;
    airportDataToXml();
    routesDataToXml();
    cout << "Done converting data." << endl;
}

bool DataProcessor::airportDataToXml()
{
    ifstream in(airportDataFilename);
    if (!in.good()) {
        cout << airportDataFilename << " can not be open!" << endl;
        in.close();
        return false;
    }
    QFile dest(airportXmlFilename.c_str());
    if(!dest.open(QIODevice::WriteOnly)) {
        cout << "can not open " << airportXmlFilename << endl;
        return false;
    }
    QXmlStreamWriter out(&dest);
    out.setAutoFormatting(true);
    out.writeStartDocument();

    char *airportID, *IATA, *ICAO, *city, *latitude, *longitude;

    char buffer[200], delimiter[2] = {'"',','};
    out.writeStartElement("vertex");
    while(!in.eof()){
        in.getline(buffer, 200);
        airportID = strtok (buffer, delimiter);
        strtok (NULL, delimiter);
        city = strtok (NULL, delimiter);
        strtok (NULL, delimiter);
        IATA = strtok (NULL, delimiter);
        ICAO = strtok (NULL, delimiter);
        latitude = strtok (NULL, delimiter);
        longitude = strtok (NULL, delimiter);

        out.writeStartElement("airport");
            out.writeTextElement("airportID",airportID);
            out.writeTextElement("IATA", IATA);
            out.writeTextElement("ICAO", ICAO);
            out.writeTextElement("city", city);
            out.writeTextElement("latitude", latitude);
            out.writeTextElement("longitude", longitude);
        out.writeEndElement();
        airportID = NULL;
        city = NULL;
        IATA = NULL;
        ICAO = NULL;
        latitude = NULL;
        longitude = NULL;
    }
    out.writeEndDocument();
    dest.close();
    in.close();
    return true;
}


bool DataProcessor::routesDataToXml()
{
    ifstream in(routeDataFilename);
    if (!in.good()) {
        cout << routeDataFilename << " can not be open!" << endl;
        in.close();
        return false;
    }
    QFile dest(routeXmlFilename.c_str());
    if (!dest.open(QIODevice::WriteOnly)) {
        cout << routeXmlFilename << " can not be open!" << endl;
        return false;
    }
    QXmlStreamWriter out(&dest);
    out.setAutoFormatting(true);
    out.writeStartDocument();

    char buffer[200], delimiter[2] = {'"', ','}, *source, *destination, *airlineID;

    out.writeStartElement("routes");
    while(!in.eof())
    {
        in.getline(buffer, 200);
        strtok (buffer, delimiter);
        airlineID = strtok (NULL, delimiter);
        strtok (NULL, delimiter);
        source = strtok (NULL, delimiter);
        strtok (NULL, delimiter);
        destination = strtok (NULL, delimiter);

        out.writeStartElement("route");
            out.writeTextElement("source", source);
            out.writeTextElement("dest", destination);
            out.writeTextElement("airlineID", airlineID);
        out.writeEndElement();
        airlineID = NULL;
        source = NULL;
        destination = NULL;
    }
    out.writeEndElement();
    dest.close();
    in.close();
    return true;
}


void DataProcessor::nukem()
{
    if (!airports) {
        return;
    }
    for (int i = 0; i < SIZE; ++i) {
        if (airports[i]) {
            delete [] airports[i];
        }
    }
}

#endif // DATAPROCESSOR
