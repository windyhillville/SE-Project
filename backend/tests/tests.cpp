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
            Planet("Proxima Centauri b", 1.30f, 1.27f, 1.08f, 0.0485f, 234.0f, 3042.0f, 0.14f),
            Planet("Kepler-22b", 183.96f, 36.0f, 2.38f, 0.85f, 262.0f, 5518.0f, 0.979f),
            Planet("HD 209458 b", 48.12f, 220.0f, 1.38f, 0.047f, 1320.0f, 6075.0f, 1.15f),
            Planet("Gliese 581 d", 6.22f, 7.7f, 2.2f, 0.22f, 222.0f, 3480.0f, 0.29f),
            Planet("51 Pegasi b", 15.62f, 150.0f, 1.9f, 0.052f, 1255.0f, 5793.0f, 1.237f)
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
        REQUIRE(planets[i]->getRadius() == Approx(correct_planets[i]->getRadius()).margin(0.001));
        REQUIRE(planets[i]->getOrbitalDistance() == Approx(correct_planets[i]->getOrbitalDistance()).margin(0.0001));
        REQUIRE(planets[i]->getEquilibriumTemp() == Approx(correct_planets[i]->getEquilibriumTemp()).margin(0.1));
        REQUIRE(planets[i]->getStarTemp() == Approx(correct_planets[i]->getStarTemp()).margin(0.1));
        REQUIRE(planets[i]->getStarRadius() == Approx(correct_planets[i]->getStarRadius()).margin(0.001));
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

    int planetIndex = binarySearch(planets, "distance", 183.96);
    REQUIRE(planets[planetIndex]->getDistance() == Approx(183.96).margin(0.001));
}

TEST_CASE("Binary Search Distance Exception", "[negative]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");
    Sort(planets, "distance");

    REQUIRE_THROWS_AS(binarySearch(planets, "distance", -50), invalid_argument);
}

TEST_CASE("Search Nearest Distance", "[positive]"){
    vector<Planet*> planets;
    inputParser(planets, "testplanets.csv");
    Sort(planets, "distance");

    vector<Planet*> planets2 = searchNearest(planets, "distance", "183.96");
    REQUIRE(planets == planets2);
}

TEST_CASE("Search Nearest Name", "[positive]"){
    vector<Planet*> planets;
    inputParser(planets, "ExoPlanets.csv");
    Sort(planets, "alphabetical");

    vector<Planet*> planets2 = searchNearest(planets, "alphabetical", "Kepler");
    REQUIRE(planets2.size() == 10);
}

TEST_CASE("Creating Account and Login", "[positive]"){
    vector<User*> users;

    REQUIRE((saveUser(users, "accounts.txt", "test_account", "testing!23") == "Account successfully created!"));
    REQUIRE((loginUser(users, "test_account", "testing!23") == true));
    clearFile();
}

TEST_CASE("Login Without Creating Account", "[negative]"){
    vector<User*> users;
    REQUIRE(loginUser(users,"test_account", "testing") == false);
}

TEST_CASE("Creating Account with invalid length", "[negative]"){
    vector<User*> users;
    REQUIRE(saveUser(users,"accounts.txt","test_account", "A") == "Password must be 5 or more characters!");
}

TEST_CASE("Creating Account with no special characters", "[negative]"){
    vector<User*> users;
    REQUIRE(saveUser(users,"accounts.txt","test_account", "testing123") == "Password needs at least one special character!");
}

TEST_CASE("Creating Duplicate Account", "[negative]"){
    vector<User*> users;
    saveUser(users,"accounts.txt", "test_account", "testing!23");
    REQUIRE(saveUser(users,"accounts.txt","test_account", "testing!23") == "Username already exists!");
    clearFile();
}

TEST_CASE("Favoriting Planet", "[postive]"){
    vector<Planet*> planets;
    inputParser(planets, "TestPlanets.csv");
    vector<User*> users;
    User* currentUser = nullptr;
    saveUser(users,"accounts.txt", "test_account", "testing!23");

    favoritePlanet(currentUser, planets, "test_account", "Kepler-22b");
    loadFavorites(users, planets, "test_account");

    REQUIRE(users[0]->favorites[0]->getName() == "Kepler-22b");
    clearFile();
    clearFavFile();
}

TEST_CASE("Unfavoriting Planet", "[negative]"){
    vector<Planet*> planets;
    inputParser(planets, "TestPlanets.csv");
    vector<User*> users;
    User* currentUser = nullptr;
    saveUser(users,"accounts.txt", "test_account", "testing!23");

    favoritePlanet(currentUser, planets, "test_account", "Kepler-22b");
    loadFavorites(users, planets, "test_account");

    unfavoritePlanet(users, "test_account", "Kepler-22b");

    bool foundPlanet = false;
    for (User* user : users) {
        if (user->getUsername() == "test_account") {
            for (Planet* planet : user->favorites) {
                if (planet && planet->getName() == "Kepler-22b") {
                    foundPlanet = true;
                }
            }
        }
    }

    REQUIRE(foundPlanet == false);
    clearFile();
}

TEST_CASE("Unfavoriting With Multiple Planets", "[negative]"){
    vector<Planet*> planets;
    inputParser(planets, "TestPlanets.csv");
    vector<User*> users;
    User* currentUser = nullptr;
    saveUser(users,"accounts.txt", "test_account", "testing!23");

    favoritePlanet(currentUser, planets, "test_account", "Kepler-22b");
    favoritePlanet(currentUser, planets, "test_account", "Proxima Centauri b");
    favoritePlanet(currentUser, planets, "test_account", "HD 209458 b");
    loadFavorites(users, planets, "test_account");

    unfavoritePlanet(users, "test_account", "Kepler-22b");

    bool foundDeletedPlanet = false;
    bool foundFavoritePlanet1 = false;
    bool foundFavoritePlanet2 = false;
    for (User* user : users) {
        if (user->getUsername() == "test_account") {
            for (Planet* planet : user->favorites) {
                if (planet && planet->getName() == "Kepler-22b") {
                    foundDeletedPlanet = true;
                }
                else if (planet && planet->getName() == "Proxima Centauri b") {
                    foundFavoritePlanet1 = true;
                }
                else if (planet && planet->getName() == "HD 209458 b") {
                    foundFavoritePlanet2 = true;
                }
            }
        }
    }

    REQUIRE(foundDeletedPlanet == false);
    REQUIRE(foundFavoritePlanet1 == true);
    REQUIRE(foundFavoritePlanet2 == true);
    clearFile();
    clearFavFile();
}