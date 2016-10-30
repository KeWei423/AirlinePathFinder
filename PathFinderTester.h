#ifndef PATHFINDERTEST_H
#define PATHFINDERTEST_H
#include "PathFinder.h"

class PathFinderTester {
public:
    PathFinderTester();
    bool run();
    bool testFindPath();


private:
    PathFinder pf;

};



#endif // PATHFINDERTEST_H

PathFinderTester::PathFinderTester()
{

}

bool PathFinderTester::run()
{
    testFindPath();
}

bool PathFinderTester::testFindPath()
{
    pf.findPath("LAX", "JFK");
    pf.findPath("LAX", "SIN");
//    pf.findPath("LAX", "YHU");
//    pf.findPath("LAX", "YPL");
//    pf.findPath("LAX", "YSJ");
//    pf.findPath("LAX", "YXE");
//    pf.findPath("LAX", "TIN");
//    pf.findPath("LAX", "ANR");
//    pf.findPath("LAX", "KAO");
//    pf.findPath("LAX", "EDI");
//    pf.findPath("LAX", "NTB");
//    pf.findPath("LAX", "GOT");
//    pf.findPath("LAX", "JKG");
//    pf.findPath("LAX", "KLR");
//    pf.findPath("LAX", "BBT");
//    pf.findPath("LAX", "LUO");
}
