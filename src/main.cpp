#include "crow.h"
#include "Planet.h"
#include "DataProcessing.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
using namespace std;

int main () {

    // Setup server
    crow::SimpleApp app;

    random_device rd;
    mt19937 gen(rd());

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

    // test
    CROW_ROUTE(app, "/test").methods("POST"_method)
        ([](const crow::request& req) {

            // Retrieves body of HTTP request sent from Processing
            auto body = crow::json::load(req.body);

            // Checks if there IS a body
            if (!body) {
                crow::json::wvalue error;
                error["result"] = "Invalid JSON!";
                return crow::response(400, error);
            }

            // Retrieves a string of a keys corresponding value
            string input = body["input"].s();
            string result = "Processed: " + input;

            // Creates JSON Object and stores "result" into it
            crow::json::wvalue response;
            response["result"] = result;

            // Sends processed request back to Processing
            return crow::response(response);
        });

    // Receives POST request from Processing and then sends a JSON object back to Processing
    CROW_ROUTE(app, "/planet/random").methods("POST"_method)
        ([&planets, &gen](const crow::request& req) {
            Planet* p = GetRandomPlanet(planets, gen);

            // Creates a writable JSON Object
            crow::json::wvalue planet;
            planet["name"] = p->getName();
            planet["mass"] = p->getMass();
            planet["distanceFromEarth"] = p->getDistance();
            planet["type"] = p->getType();
            planet["radius"] = p->getRadius();
            planet["starTemp"] = p->getStarTemp();
            planet["habitability"] = p->getHabitability();

            // Sends processed request back to Processing
            return crow::response(planet);
        });

    // Listens for any HTTP request from a client (Processing)
    app.port(5001).multithreaded().run();
    return 0;
}