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

    // Setup random generator
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

    string currentUsername = "";
    User* currentUser = nullptr;

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

    CROW_ROUTE(app, "/loginScreen/signIn").methods("POST"_method)
        ([&users, &currentUser](const crow::request& req) {

            auto body = crow::json::load(req.body);

            // Checks if there IS a body
            if (!body) {
                crow::json::wvalue error;
                error["result"] = "Invalid JSON!";
                return crow::response(400, error);
            }

            string currentUsername = body["username"].s();
            string password = body["password"].s();

            crow::json::wvalue result;
            result["truthValue"] = loginUser(users, currentUsername, password);

            crow::json::rvalue view = crow::json::load(result.dump());
            if (view["truthValue"].b()) {
                for (User* user : users) {
                    if (currentUsername == user->getUsername())
                        currentUser = user;
                }
            }
//            string userInformation = "User Data stored:\nUsername: " + username + "\nPassword: " + password + "\n";

            return crow::response(result);
        });

    CROW_ROUTE(app, "/loginScreen/createAccount").methods("POST"_method)
            ([&users](const crow::request& req) {

                auto body = crow::json::load(req.body);

                // Checks if there IS a body
                if (!body) {
                    crow::json::wvalue error;
                    error["result"] = "Invalid JSON!";
                    return crow::response(400, error);
                }

                string username = body["username"].s();
                string password = body["password"].s();

                crow::json::wvalue result;
                result["result"] = saveUser(users, "accounts.txt", username, password);

//                string userInformation = "User Data stored:\nUsername: " + username + "\nPassword: " + password + "\n";

                return crow::response(result);
            });

    // Receives POST request from Processing and then sends a Random Planet JSON object back to Processing
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
                planet["gravity"] = p->getGravity();

                // Sends processed request back to Processing
                return crow::response(planet);
            });

    CROW_ROUTE(app, "/mainMenu/addFavorite").methods("POST"_method)
            ([&users, &currentUser, &planets](const crow::request& req) {
                auto body = crow::json::load(req.body);

                // Checks if there IS a body
                if (!body) {
                    crow::json::wvalue error;
                    error["result"] = "Invalid JSON!";
                    return crow::response(400, error);
                }

                string planetName = body["planetName"].s();
                crow::json::wvalue result;

                // Add favorite planet
                for (User* user : users) {
                     if (currentUser->getUsername() == user->getUsername()) {
                         result["result"] = favoritePlanet(currentUser, planets, currentUser->getUsername(), planetName);
                         break;
                     }
                }
                return crow::response(result);
            });

    CROW_ROUTE(app, "/mainMenu/removeFavorite").methods("POST"_method)
            ([&users, &currentUser, &planets](const crow::request& req) {
                auto body = crow::json::load(req.body);

                // Checks if there IS a body
                if (!body) {
                    crow::json::wvalue error;
                    error["result"] = "Invalid JSON!";
                    return crow::response(400, error);
                }

                string planetName = body["planetName"].s();

                string message;
                for (User* user : users) {
                    if (currentUser->getUsername() == user->getUsername())
                        message = unfavoritePlanet(users, currentUser->getUsername(), planetName);
                }

                crow::json::wvalue result;
                result["result"] = message;

                return crow::response(result);
            });

    CROW_ROUTE(app, "/mainMenu/loadFavorites").methods("POST"_method)
            ([&users, &currentUser, &planets](const crow::request& req) {
                crow::json::wvalue result;
                crow::json::wvalue favoritesJSON = crow::json::wvalue::list();

                for (User* user : users) {
                    if (currentUser->getUsername() == user->getUsername())
                        loadFavorites(users, planets, currentUser->getUsername());
                }

                int index = 0;
                for (Planet* favPlanet : currentUser->favorites) {
                    crow::json::wvalue planetJSON;
                    planetJSON["name"] = favPlanet->getName();
                    planetJSON["mass"] = favPlanet->getMass();
                    planetJSON["distanceFromEarth"] = favPlanet->getDistance();
                    planetJSON["type"] = favPlanet->getType();
                    planetJSON["radius"] = favPlanet->getRadius();
                    planetJSON["starTemp"] = favPlanet->getStarTemp();
                    planetJSON["habitability"] = favPlanet->getHabitability();
                    planetJSON["gravity"] = favPlanet->getGravity();

                    favoritesJSON[index++] = std::move(planetJSON);
                }
//                result["favorites"] = std::move(favoritesJSON);

                return crow::response(favoritesJSON);
            });

    // Listens for any HTTP request from a client (Processing)
    app.port(5001).multithreaded().run();
    return 0;
}