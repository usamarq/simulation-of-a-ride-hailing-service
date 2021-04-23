/*UberApp.h*/

#ifndef UBERAPP_H
#define UBERAPP_H

#include"City.h"
#include"User.h"
#include"Graph.h"
#include"Hash.h"
#include<string>
#include<list>
#include<iostream>
#include<fstream>
using namespace std;

class UberApp {
private:
    priority_queue<User> *UserList; // Works same as MaxHeap we did in lab
    Graph<City> *distanceMap;
    Graph<City> *costPerPersonMap;
    Hash<City> *cityList;
    int numCities;
public:
    UberApp(string filename);
    void menu();
    void userRides(string filename);
    void minHop();
    void busPaths();
    void shortestPath();
};


#endif // !UBERAPP_H
