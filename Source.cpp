#include <iostream>
using namespace std;

#include"UberApp.h"

int main() {
    UberApp *u = new UberApp("cityMap.txt");
    cout << endl;

    int choice = -1;
    while (choice != 0) {
        u->menu();
        cout << "> ";
        cin >> choice;
        switch (choice) {
            case 1:
                u->minHop();
                break;
            case 2:
                u->userRides("users.txt");
                break;
            case 3:
                u->busPaths();
                break;
            case 4:
                u->shortestPath();
                break;
            default:
                break;
        }
    }
}