#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "../src/Planet.h"
#include "../src/DataProcessing.h"
using namespace std;

TEST_CASE("Input Parser", "[positive]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");

    // Creates class objects for all the planets in the test dataset
    vector<Planet> expected = {
            Planet("Proxima Centauri b", 1.30f, 1.27f, 2016),
            Planet("Kepler-22b", 183.96f, 36.0f, 2011),
            Planet("HD 209458 b", 48.12f, 220.0f, 1999),
            Planet("Gliese 581 d", 6.22f, 7.7f, 2007),
            Planet("51 Pegasi b", 15.62f, 150.0f, 1995)
    };

    // Creates pointers of those class objects
    vector<Planet*> correct_planets;
    for(Planet& planet : expected){
        correct_planets.push_back(new Planet(planet));
    }


    REQUIRE(planets.size() == correct_planets.size());
    // Checks to see if each object's properties are the same
    for(int i = 0; i < planets.size() - 1; i++){
        REQUIRE(planets[i]->getName() == correct_planets[i]->getName());
        REQUIRE(planets[i]->getDistance() == Approx(correct_planets[i]->getDistance()).margin(0.001));
        REQUIRE(planets[i]->getMass() == Approx(correct_planets[i]->getMass()).margin(0.001));
        REQUIRE(planets[i]->getDiscoveryDate() == correct_planets[i]->getDiscoveryDate());
    }
}

TEST_CASE("Input Parser Exception", "[negative]"){
    vector<Planet*> planets;
    REQUIRE_THROWS_AS(inputParser(planets, "testplanets.txt"), invalid_argument);
}

TEST_CASE("Sort Distance", "[positive]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");
    Sort(planets, "distance");

    bool sorted = true;
    for(int i = 0; i < planets.size() - 1; i++){
        if(planets[i]->getDistance() < planets[i + 1]->getDistance()){
            sorted = false;
            break;
        }
    }

    REQUIRE(sorted);
}

TEST_CASE("Sort Distance Exception", "[negative]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");

    REQUIRE_THROWS_AS(Sort(planets, "dist"), invalid_argument);
}

TEST_CASE("Binary Search Distance", "[positive]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");
    Sort(planets, "distance");

    int planetIndex = binarySearch(planets, 183.96);
    REQUIRE(planets[planetIndex]->getDistance() == Approx(183.96).margin(0.001));
}

TEST_CASE("Binary Search Distance Exception", "[negative]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");
    Sort(planets, "distance");

    REQUIRE_THROWS_AS(binarySearch(planets, -50), invalid_argument);
}