#ifndef LOADDATA
#define LOADDATA
#include <QCoreApplication>
#include <QXmlStreamWriter>
#include <QtXml/qdom.h>
#include <QFile>
#include <qstring.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include "Airport.h"

using namespace std;

struct node{
    string name;
    int id;
};

class DataProcessor {
public:

    DataProcessor(char *_airportDataFilename ="airports.dat",
                  char *_airportXmlFilename = "airports.xml",
                  char *_routeDataFilename = "routes.dat",
                  char *_routeXmlFilename = "routes.xml");

    Airport* getAirports(Airport *list);
    void reloadData();

private:
    void airportDataToXml();
    void routesDataToXml();
    void insertRoutesIntoAirports(Airport *list);

    char *airportDataFilename;
    char *airportXmlFilename;
    char *routeDataFilename;
    char *routeXmlFilename;
};


// ==========================================================================================   OLD FUNCTIONS

vector<node*> airporList;

void readAirlines(string airlines[], char *input)
{
    ifstream in(input);
    char buffer[200], delimiter[2] = {'"', ','}, *airlineID, *name;
    while(!in.eof())
    {
        in.getline(buffer, 200);
        airlineID = strtok(buffer, delimiter);
        name = strtok(NULL, delimiter);//company name
        airlines[atoi(airlineID)] = name;
    }
}

int name2number(string name){
    int size = airporList.size();
    for(int i = 0; i < size; ++i)
        if(airporList[i]->name == name)
            return airporList[i]->id;
    return false;
}
#endif // LOADDATA
// ==========================================================================================   Class FUNCTIONS


DataProcessor::DataProcessor(char *_airportDataFilename,
                             char *_airportXmlFilename,
                             char *_routeDataFilename,
                             char *_routeXmlFilename)
{
    airportDataFilename = _airportDataFilename;
    airportXmlFilename = _airportXmlFilename;
    routeDataFilename = _routeDataFilename;
    routeXmlFilename = _routeXmlFilename;
}

Airport *DataProcessor::getAirports(Airport* list)
{
    node *A;
    int id;
    double latitude, lontitude;;
    string IATA, city, ICAO;

    //open dom file
    QDomDocument routesDoc;
    QFile file(airportXmlFilename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        cout << "can not open file" << endl;
    else
    {
//        cout << input <<" is opened." << endl;
        //load file
        if(!routesDoc.setContent(&file))
            cout << " fail to load content" << endl;
        //go to the root
        QDomElement root = routesDoc.firstChildElement();
        //put source in to list
        QDomNodeList airportList = root.elementsByTagName("airportID");
        QDomNode route;
        QDomElement element;
        //for every route
        for(int i = 0; i < airportList.size(); ++i)
        {
            //convert to element
            route = airportList.at(i);
            element = route.toElement();
            //get the text elements
            id = element.text().toInt();
            element = element.nextSiblingElement("IATA");
            IATA = element.text().toStdString();
            element = element.nextSiblingElement("ICAO");
            ICAO = element.text().toStdString();
            element = element.nextSiblingElement("city");
            city = element.text().toStdString();
            element = element.nextSiblingElement("latitude");
            latitude = element.text().toDouble();
            element = element.nextSiblingElement("longitude");
            lontitude = element.text().toDouble();
            if(latitude && lontitude)
                list[id].set(id, IATA, city, "", latitude, lontitude);
            A = new node;
            A->id = id;
            A->name = IATA;
            airporList.push_back(A);
            A = new node;
            A->id = id;
            A->name = ICAO;
            airporList.push_back(A);
        }
    }
    insertRoutesIntoAirports(list);
    return list;
}

void DataProcessor::reloadData()
{
    airportDataToXml();
    routesDataToXml();
}

void DataProcessor::airportDataToXml()
{
    ifstream in(airportDataFilename);
    QFile dest(airportXmlFilename);
    if(!dest.open(QIODevice::WriteOnly))
        cout << "can not open " << airportXmlFilename << endl;
    QXmlStreamWriter out(&dest);
    out.setAutoFormatting(true);
    out.writeStartDocument();

    char *airportID, *IATA, *ICAO, *city, *latitude, *longitude;
    char buffer[200], delimiter[2] = {'"',','};
    out.writeStartElement("vertex");
    while(!in.eof()){
        in.getline(buffer, 200);
        airportID = strtok (buffer, delimiter);//airportID
        strtok (NULL, delimiter);//name
        city = strtok (NULL, delimiter);//city
        strtok (NULL, delimiter);//Country
        IATA = strtok (NULL, delimiter);//IATA
        ICAO = strtok (NULL, delimiter);//ICAO
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
    }
    out.writeEndDocument();
    dest.close();
    in.close();

}

void DataProcessor::routesDataToXml()
{
    //open files
    ifstream in(routeDataFilename);
    QFile dest(routeDataFilename);
    dest.open(QIODevice::WriteOnly);
    QXmlStreamWriter out(&dest);

    //set up xml
    out.setAutoFormatting(true);
    out.writeStartDocument();
    out.writeStartElement("routes");

    //buffers
    char buffer[200], delimiter[2] = {'"', ','}, *source, *destination, *airlineID;

    //reading until the end
    while(!in.eof())
    {
        //read a line
        in.getline(buffer, 200);
        strtok (buffer, delimiter);//Airline
        airlineID = strtok (NULL, delimiter);//Airline ID
        strtok (NULL, delimiter);//Source
        source = strtok (NULL, delimiter);//Source ID
        strtok (NULL, delimiter);//Dest
        destination = strtok (NULL, delimiter);//Dest ID

        //source
            //dest
        out.writeStartElement("route");
            out.writeTextElement("source", source);
            out.writeTextElement("dest", destination);
            out.writeTextElement("airlineID", airlineID);
        out.writeEndElement();
    }
    out.writeEndElement();
    dest.close();
    in.close();
}

void DataProcessor::insertRoutesIntoAirports(Airport *list)
{
    short source, dest, airlineID;
    //open dom file
    QDomDocument routesDoc;
    QFile file(routeXmlFilename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        cout << "can not open file" << endl;
    else
    {
        //load file
        if(!routesDoc.setContent(&file))
            cout << "fail to load" << endl;

        //go to the root
        QDomElement root = routesDoc.firstChildElement();
        //put source in to list
        QDomNodeList routes = root.elementsByTagName("source");
        QDomNode route;
        QDomElement routeElement;
        //for every route
        for(int i = 0; i < routes.count(); ++i)
        {
            //convert to element
            route = routes.at(i);
            routeElement = route.toElement();
            //get the text elements
            source = routeElement.text().toShort();
            routeElement = routeElement.nextSiblingElement("dest");
            dest = routeElement.text().toShort();
            routeElement = routeElement.nextSiblingElement("airlineID");
            airlineID = routeElement.text().toShort();
            if(source && dest)
                list[source].addDestination(dest, list[source].getDistanceTo(list[dest]), airlineID);

        }
    }
}
