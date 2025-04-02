#pragma once
#include <string>
#include <utility>
using namespace std;

class Planet {
    string _name;
    float _distanceFromEarth;
    float _planetaryMass;
    float _planetaryRadius;
    float _planetaryOrbit;
    float _planetaryEquilTemp;
    int _planetType;
    float _favorability;

    // Host Star
    float _starTemp;
    float _starRadius;

    float calculateFavorability();
    string habitabilityTier(const float& favorability) const;
public:
    // TODO: will need to update these functions depending on the dataset
    Planet();
    Planet(string name, float distance, float mass, float radius, float orbit, float equilTemp, float starTemp, float starRadius);

    void printPlanetInfo() const;
    void printHabitability(const float& favorability) const;

    string getName() const;
    float getDistance() const;
    float getMass() const;
    float getRadius() const;
    float getOrbitalDistance() const;
    float getEquilibriumTemp() const;
    float getStarTemp();
    float getStarRadius();

    float getFavorability() const;
    float getType() const;


};
