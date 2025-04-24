#include "Planet.h"
#include <cmath>
#include <iostream>

// Constants
const double SOLAR_RADIUS = 6.955e8;
const double ASTRONOMICAL_UNITS = 1.496e11;
const double EARTH_MASS = 5.972e24;
const double EARTH_RADIUS = 6.371e6;
const double GRAVITATIONAL_CONSTANT = 6.67430e-11;
const double BOLTZMANN_CONSTANT = 1.380649e-23;
const double AVOGADRO_NUMBER = 6.02214076e23;
const double PLANET_ALBEDO = 0.3;             // Earth-like


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
    _planetType = 0;
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
    _planetType = calculatePlanetType();
    calculatePlanetConditions();
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

string Planet::getType() const {
    string type;
    if(_planetType == 1){
        type = "Terrestrial";
    }
    else if(_planetType == 2){
        type = "Super Earth";
    }
    else if(_planetType == 3){
        type = "Mini-Neptune";
    }
    else if (_planetType == 4){
        type = "Neptune-like";
    }
    else if (_planetType == 5){
        type = "Gas Giant";
    }
    else {
        throw invalid_argument("Invalid planet type: " + type + "!");
    }

    return type;
}

float Planet::getHabitability() const {
    return _habitability;
}

float Planet::getGravity() const {
    return _planetaryGravity;
}

float Planet::getScaleHeight() const {
    return _planetaryScaleHeight;
}

// Print debug statements
void Planet::printPlanetInfo() const {
    cout << "Planet name: " << _name << endl;
    cout << "Planet distance from Earth: " << _distanceFromEarth << " Parsecs(pc)" << endl;
    cout << "Planet mass: " << _planetaryMass << " Earth masses (M)" << endl;
    cout << "Planet radius: " << _planetaryRadius << " Earth radii(R)" << endl;
    cout << "Planet orbital distance: " << _planetaryOrbit << " Astronomical Units (AU)" << endl;
    cout << "Planet equilibrium temperature: " << _planetaryEquilTemp << " Kelvin (K)" << endl;
    cout << "Planet gravity: " << _planetaryGravity << " Meters per second squared (m/s^2)" << endl;
    cout << "Planet scale height: " << _planetaryScaleHeight << " Kilometers (km)" << endl;
    cout << "Planet type: " << getType() << endl;
    cout << "Planet habitability: " << _habitability << "%" << endl;
    cout << endl;
    cout << "Planet's star temperature: " << _starTemp << " Kelvin (K)" << endl;
    cout << "Planet's star radius: " << _starRadius << " Solar radii (R)" << endl;
    cout << endl;
}

// Arithmetic functions
int Planet::calculatePlanetType() {
    // Planetary type being based off the radius of the planet
    if(_planetaryRadius < 1.25){
        // Terrestrial
        return 1;
    }
    else if(_planetaryRadius < 2.0){
        // Super Earth
        return 2;
    }
    else if(_planetaryRadius < 4.0){
        // Mini-Neptune
        return 3;
    }
    else if(_planetaryRadius < 6.0){
        // Neptune-like
        return 4;
    }
    else {
        // Gas Giant
        return 5;
    }
}

void Planet::calculatePlanetConditions() {
    // Unit Conversions
    double starRadius = _starRadius * SOLAR_RADIUS;
    double orbitalDistance = _planetaryOrbit * ASTRONOMICAL_UNITS;
    double planetRadius = _planetaryRadius * EARTH_RADIUS;
    double planetMass = _planetaryMass * EARTH_MASS;

    // If there is no data for the equilibrium temp
    if(_planetaryEquilTemp == 0){
        _planetaryEquilTemp = _starTemp * sqrt(starRadius / (2.0 * orbitalDistance)) * pow(1.0 - PLANET_ALBEDO, 0.25);
    }

    // Finds the molecular weight for the planet based on its type
    double molecular_weight;
    switch(_planetType) {
        case 1: // Terrestrial
            molecular_weight = 0.029;
            break;
        case 2: // Super Earth
            molecular_weight = 0.033;
            break;
        case 3: // Mini-Neptune
            molecular_weight = 0.003;
            break;
        case 4: // Neptune-Like
            molecular_weight = 0.002;
            break;
        case 5: // Gas Giant
            molecular_weight = 0.002;
            break;
        default: // Earth-like
            molecular_weight = 0.0029;
    }

    _planetaryGravity = GRAVITATIONAL_CONSTANT * planetMass / (planetRadius * planetRadius);
    _planetaryScaleHeight = ((BOLTZMANN_CONSTANT * _planetaryEquilTemp) / ((molecular_weight / AVOGADRO_NUMBER) * _planetaryGravity)) / 1000.0;


    // Calculating the habitability
    double score = 0;
    // The score is going to out of 10, the higher the number, the more habitable it is
    // Temp best between 240-310K
    if(_planetaryEquilTemp >= 240 && _planetaryEquilTemp <= 310){
        score += 4;
    }
    else if(_planetaryEquilTemp >= 200 && _planetaryEquilTemp <= 340){
        score += 2;
    }
    else if(_planetaryEquilTemp > 540 || _planetaryEquilTemp < 180){
        _habitability = 0;
        // Both extremes, too hot and too cold
        return;
    }

    // Want a gravity close to Earth's
    if(_planetaryGravity >= 6 && _planetaryGravity <= 14){
        score += 3;
    }
    else if(_planetaryGravity < 3){
        _habitability = 0;
        return ;
        // Can't hold an atmosphere with this little gravity
    }

    //  Want a scale height between 5 km to 60km
    if(_planetaryScaleHeight >= 5 && _planetaryScaleHeight <= 60){
        score += 3;
    }

    _habitability = (score / 10.0) * 100.0;

    // Adds an arbitrary modifier based on its planet type
    switch(_planetType){
        case 1: // Terrestrial
        case 2: // Super Earth
            break;
        case 3: // Mini-Neptune
            _habitability *= 0.2;
            break;
        case 4: // Neptune-Like
            _habitability *= 0.1;
            break;
        case 5: // Gas Giant
            _habitability = 0;
            break;
    }
}


