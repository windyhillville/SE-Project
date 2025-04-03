#pragma once
#include <string>
#include <utility>
using namespace std;

class Planet {
    // Input Planetary Data
    string _name;
    float _distanceFromEarth;
    float _planetaryMass;
    float _planetaryRadius;
    float _planetaryOrbit;
    float _planetaryEquilTemp;

    // Calculated Data
    int _planetType;
    float _habitability;
    float _planetaryGravity;
    float _planetaryScaleHeight;

    // Host Star
    float _starTemp;
    float _starRadius;

    // Calculation functions
    int calculatePlanetType();
    void calculatePlanetConditions();
public:
    // Constructors
    Planet();
    Planet(string name, float distance, float mass, float radius, float orbit, float equilTemp, float starTemp, float starRadius);

    // Print debug
    void printPlanetInfo() const;

    // Input Planetary Data
    string getName() const;
    float getDistance() const;
    float getMass() const;
    float getRadius() const;
    float getOrbitalDistance() const;
    float getEquilibriumTemp() const;
    float getStarTemp();
    float getStarRadius();

    // Calculated Data
    float getHabitability() const;
    string getType() const;
    float getGravity() const;
    float getScaleHeight() const;

};
