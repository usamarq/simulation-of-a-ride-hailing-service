/*User.h*/

#ifndef USER_H
#define USER_H

#include"City.h"

struct User {
    string ID;
    City from;
    City to;
    bool premium;
    double rate;
    //key is 'premium'
    User() {
        ID = string();
        from = City();
        to = City();
        premium = false;
        rate = 0;
    }
    User(string id, City src, City des, bool prem)
        :ID(id), from(src), to(des), premium(prem) {
        if (prem)
            rate = 15;
        else
            rate = 10;
    }
    //operators for priority queue
    bool operator==(const User obj) const { return premium == obj.premium; }
    bool operator!=(const User obj) const { return premium != obj.premium; }
    bool operator>(const User obj) const { return premium > obj.premium; }
    bool operator<(const User obj) const { return premium < obj.premium; }

};

#endif // !USER_H
