#include "Planet.h"


// Constructors
Planet::Planet() {
    // default constructor
    // catch all if there is no data
    // front end will have to put "?" if they are 0
    _name = "Unknown";
    _distanceFromEarth = 0.0;
    _planetaryMass = 0.0;
    _planetaryRadius = 0.0;
    _planetaryOrbit = 0.0;
    _planetaryEquilTemp = 0.0; // If it exists, if it does not, will need to calculate

    _starTemp = 0.0;
    _starRadius = 0.0;
}

Planet::Planet(string name, float distance, float mass, float radius, float orbit, float equilTemp, float starTemp, float starRadius) {
    _name = name;
    _distanceFromEarth = distance;
    _planetaryMass = mass;
    _planetaryRadius = radius;
    _planetaryOrbit = orbit;
    _planetaryEquilTemp = equilTemp;

    _starTemp = starTemp;
    _starRadius = starRadius;
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

float Planet::getRadius() const {
    return _planetaryRadius;
}

float Planet::getOrbitalDistance() const {
    return _planetaryOrbit;
}

float Planet::getEquilibriumTemp() const {
    return _planetaryEquilTemp;
}

float Planet::getStarTemp() {
    return _starTemp;
}

float Planet::getStarRadius() {
    return _starRadius;
}

float Planet::getType() const {
    return _planetType;
}

float Planet::getFavorability() const {
    return _favorability;
}



// TODO: will need to implement these functions depending on the dataset

//// Print debug statements
//void Planet::printPlanetInfo() const {
//    return;
//}
//
//void Planet::printHabitability(const float &favorability) const {
//    return;
//}
//
//// Arithmetic functions
//float Planet::calculateFavorability() {
//    return 0;
//}
//
//string Planet::habitabilityTier(const float &favorability) const {
//    return "0";
//}




