#pragma once
#include <string>
#include <utility>
using namespace std;

class Planet {
    // TODO: will need to update these data types below depending on the dataset
    string _name;
    float _distanceFromEarth;
    float _planetaryMass;
    int _discoveryDate;
    int _planetType;
    float _favorability;

    float calculateFavorability();
    string habitabilityTier(const float& favorability) const;
public:
    // TODO: will need to update these functions depending on the dataset
    Planet();
    Planet(string& name, float distance, float mass, int discovery, int type);

    void printPlanetInfo() const;
    void printHabitability(const float& favorability) const;

    string getName() const;
    float getDistance() const;
    float getFavorability() const;
    float getMass() const;
    float getType() const;
    float getDiscoveryDate() const;

};
