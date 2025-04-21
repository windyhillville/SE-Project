#include <iostream>
#include "Planet.h"
#include "DataProcessing.h"
#include <vector>
using namespace std;

int main () {
    // Earth's properties
    const string EARTH_NAME = "Earth";
    const float EARTH_MASS = 5.972e24; // KG
    const float EARTH_RADIUS = 6371; // KM
    const float EARTH_ORBITAL_DISTANCE = 149597870.7; // KM
    const float EARTH_GRAVITY = 9.8; // (m/s^2)
    const float EARTH_HABITABILITY = 100; // %

    // vector to hold all exoplanets
    vector<Planet*> planets;
    vector<User*> users;
    // loads all users from file
    loadUsers(users, "accounts.txt");
    // placeholder csv file until we get the entire dataset
    inputParser(planets, "ExoPlanets.csv");
    // call to create the user interface will go here

    return 0;
}