#include "Planet.h"


// Constructors
Planet::Planet() {
    // default constructor
    // catch all if there is no data
    // front end will have to put "?" if they are 0
    _name = "Unknown";
    _distanceFromEarth = 0.0;
    _discoveryDate = 0;
    _planetType = 0;
    _planetaryMass = 0.0;
}

Planet::Planet(string& name, float distance, float mass, int discovery, int type) {
    _name = name;
    _distanceFromEarth = distance;
    _planetaryMass = mass;
    _discoveryDate = discovery;
    _planetType = type;
}

// Getters
string Planet::getName() const {
    return _name;
}

float Planet::getDistance() const {
    return _distanceFromEarth;
}

float Planet::getMass() const {
    return _planetaryMass;
}

float Planet::getDiscoveryDate() const {
    return _discoveryDate;
}

float Planet::getType() const {
    return _planetType;
}

float Planet::getFavorability() const {
    return _favorability;
}

// TODO: will need to implement these functions depending on the dataset

// Print debug statements
void Planet::printPlanetInfo() const {
    return;
}

void Planet::printHabitability(const float &favorability) const {
    return;
}

// Arithmetic functions
float Planet::calculateFavorability() {
    return 0;
}

string Planet::habitabilityTier(const float &favorability) const {
    return "0";
}




