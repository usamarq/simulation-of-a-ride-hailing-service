/*UberApp.cpp*/

#include "UberApp.h"

UberApp::UberApp(string filename) {
    ifstream fin;
    fin.open(filename);
    fin >> numCities;
    distanceMap = new Graph<City>(numCities);
    costPerPersonMap = new Graph<City>(numCities);
    cityList = new Hash<City>(numCities);
    City *src = new City();
    City *des = new City();
    string srcName, desName;
    int i, j;
    double dist;
    double cost;
    while (!fin.eof()) {
        fin.ignore();
        getline(fin, srcName, '\t');
        src = new City(srcName);
        getline(fin, desName, '\t');
        des = new City(desName);
        fin >> dist >> cost;
        cityList->store(*src);
        cityList->store(*des);
        i = cityList->hash(*src);
        j = cityList->hash(*des);
        distanceMap->addEdge(i, j, dist);
        costPerPersonMap->addEdge(i, j, cost);
        cout << '(' << *src << ", " << *des << ") is "
            << dist << "kms long, and costs Rs"
            << cost << " per customer for bus service\n";
    }
    distanceMap->buildPaths(*cityList);
    costPerPersonMap->buildPaths(*cityList);

}

void UberApp::menu() {
    cout << endl
        << 1 << " - Find path of minimum hops from City A to City B\n"
        << 2 << " - Handle users in queue(ride hailing service)\n"
        << 3 << " - Display all paths for bus service\n"
        << 4 << " - Shortest path from City A to City B\n"
        << 0 << " - Exit\n";
}

void UberApp::minHop() {
    cout << "--Finding minimum hops from City A to City B--\n";
    int src, des;
    cityList->print();

    cout << "Select starting city number\n> ";
    cin >> src;

    cout << "Select ending city number\n> ";
    cin >> des;

    if (src == des) {
        cout << "Already at destination\n";
        return;
    }

    distanceMap->ShortestHop(src, des);

}

void UberApp::busPaths() {
    cout << "--Finding minimum bus cost path from City A to City B--\n";
    int src, des;
    cityList->print();

    cout << "Select starting city number\n> ";
    cin >> src;

    cout << "Select ending city number\n> ";
    cin >> des;

    if (src == des) {
        cout << "Already at destination\n";
        return;
    }

    costPerPersonMap->MSTpath(src, des);
}

void UberApp::shortestPath() {
    cout << "--Finding shortest path from City A to City B--\n";
    int src, des;
    cityList->print();

    cout << "Select starting city number\n> ";
    cin >> src;

    cout << "Select ending city number\n> ";
    cin >> des;

    if (src == des) {
        cout << "Already at destination\n";
        return;
    }

    distanceMap->ShortestPath(src, des);
    cout << "It has a total distance of " << distanceMap->minDist(src, des) << endl;
}

void UberApp::userRides(string filename) {
    int numUsers;
    ifstream fin;
    fin.open(filename);
    fin >> numUsers;
    UserList = new priority_queue<User>();
    User tmpUsr;

    bool usrType;

    City *src = new City();
    City *des = new City();
    string srcName, desName, usrID;

    while (!fin.eof()) {
        fin.ignore();
        getline(fin, usrID, '\t');
        getline(fin, srcName, '\t');
        src = new City(srcName);
        getline(fin, desName, '\t');
        des = new City(desName);
        fin >> usrType;
        tmpUsr = User(usrID, *src, *des, usrType);
        UserList->push(tmpUsr);
    }

    fin.close();

    int *cityCars = new int[numCities];
    for (int i = 0; i < numCities; i++) {
        cityCars[i] = 5;
    }

    int srcIndex, desIndex;
    queue<User> waitlist;
    while (!UserList->empty()) {
        tmpUsr = UserList->top();
        *src = tmpUsr.from;
        *des = tmpUsr.to;
        usrID = tmpUsr.ID;
        srcIndex = cityList->hash(*src);
        desIndex = cityList->hash(*des);
        if (waitlist.size() > 0) {
            if (cityCars[cityList->hash((waitlist.front().from))] > 0) {
                tmpUsr = waitlist.front();
                *src = tmpUsr.from;
                *des = tmpUsr.to;
                usrID = tmpUsr.ID;
                srcIndex = cityList->hash(*src);
                desIndex = cityList->hash(*des);
                cout << "User: " << usrID << " path is :\n";
                distanceMap->ShortestPath(srcIndex, desIndex);
                cout << "Fare for the user is: " << tmpUsr.rate * distanceMap->minDist(srcIndex, desIndex) << endl;
                cityCars[srcIndex] -= 1;
                cityCars[desIndex] += 1;
                waitlist.pop();
            }
        }

        if (cityCars[srcIndex] > 0) {
            cout << "User: " << usrID << " path is :\n";
            distanceMap->ShortestPath(srcIndex, desIndex);
            cout << "Fare for the user is: " << tmpUsr.rate * distanceMap->minDist(srcIndex, desIndex) << endl;
            cityCars[srcIndex] -= 1;
            cityCars[desIndex] += 1;
        } else {
            cout << "Wait please while we find you a captain\n";
            waitlist.push(tmpUsr);
        }
        UserList->pop();

    }


}

