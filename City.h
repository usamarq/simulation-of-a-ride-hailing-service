/*City.h*/

#ifndef CITY_H
#define CITY_H

#include<string>
using namespace std;

struct City {
    string name;
    City() { name = string(); }
    City(string name) :name(name) {}
    bool operator==(const City obj) { return name == obj.name; }
    bool operator!=(const City obj) { return name != obj.name; }
    bool operator>(const City obj) { return name > obj.name; }
    bool operator<(const City obj) { return name < obj.name; }
    int operator%(int x) { //Used for hash function
        int sum = 0;
        for (char c : name) {
            sum += c;
        }
        return sum % x;
    }
    friend ostream& operator<<(ostream& out, City obj) {
        out << obj.name;
        return out;
    }
};

#endif // !CITY_H
