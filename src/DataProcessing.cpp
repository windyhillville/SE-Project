#include "DataProcessing.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <set>
using namespace std;

// function implementations will be placed here

void inputParser(vector<Planet*>& planets, const string& filename) {
    string filepath = "../data/";
    filepath += filename;
    ifstream file(filepath);

    string firstLine;
    getline(file, firstLine);

    if (file.is_open()) {
//            cout << "File is open." << endl << endl;

        string line;
        while (getline(file, line)) {
            istringstream stream(line);

            string name;
            getline(stream, name, ',');

            string orbit;
            getline(stream, orbit, ',');

            string radius;
            getline(stream, radius, ',');

            string mass;
            getline(stream, mass, ',');

            string equilTemp;
            getline(stream, equilTemp, ',');

            string starTemp;
            getline(stream, starTemp, ',');

            string starRadius;
            getline(stream, starRadius, ',');

            string distance;
            getline(stream, distance, ',');

            Planet *planet = new Planet(name, stof(distance), stof(mass), stof(radius), stof(orbit), stof(equilTemp), stof(starTemp), stof(starRadius));
            planets.push_back(planet);
        }
    }
    else {
        throw invalid_argument("Could not open file: " + filename + ".");
    }
}

void Sort(vector<Planet*>& planets, const string& sortBy){
    // Alphabetical descending
    if (sortBy == "alphabetical"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getName() < planet2->getName();
        });
    }
        // Distance descending
    else if (sortBy == "distance") {
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getDistance() > planet2->getDistance();
        });
    }
        // Mass descending
    else if (sortBy == "mass"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getMass() > planet2->getMass();
        });
    }
        // Radius descending
    else if (sortBy == "radius"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getRadius() > planet2->getRadius();
        });
    }
        // Habitability
    else if (sortBy == "habitability"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getHabitability() > planet2->getHabitability();
        });
    }
        // Type
    else if (sortBy == "type"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getType() > planet2->getType();
        });
    }
        // Gravity
    else if (sortBy == "gravity"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getGravity() > planet2->getGravity();
        });
    }
    else {
        throw invalid_argument("Invalid Value to Sort By: " + sortBy + "." );
    }
}

int binarySearch(const vector<Planet*>& planets, const string& searchBy, const string& target) {
    if (searchBy == "alphabetical") {
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getName() == target) {
                return middle;
            }
            else if (target < planets[middle]->getName()) {
                end = middle - 1;
            }
            else {
                start = middle + 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target.compare(planets[end]->getName())) <= abs(target.compare(planets[start]->getName()))) {
            return end;
        }
        else {
            return start;
        }
    }
    else if (searchBy == "type") {
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getType() == target) {
                return middle;
            }
            else if (target < planets[middle]->getType()) {
                start = middle + 1;
            }
            else {
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target.compare(planets[end]->getType())) <= abs(target.compare(planets[start]->getType()))) {
            return end;
        }
        else {
            return start;
        }
    }
    else
        throw invalid_argument("Mismatch: string is only used with search by name and type.");;
}

int binarySearch(const vector<Planet*>& planets, const string& searchBy, const float& target) {
    if (searchBy == "distance") {
        // Catches the invalid input of negative distance
        if (target < 0) {
            throw invalid_argument("Invalid Value: distance cannot be negative!");
        }
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getDistance() == target) {
                return middle;
            }
            else if (target < planets[middle]->getDistance()) {
                start = middle + 1;
            }
            else {
                //planets[middle]->getTemperature() < target
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target - planets[end]->getDistance()) <= abs(target - planets[start]->getDistance())) {
            return end;
        }
        else {
            return start;
        }
    }
    else if (searchBy == "mass") {
        // Catches the invalid input of negative mass
        if (target < 0) {
            throw invalid_argument("Invalid Value: mass cannot be negative!");
        }
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getMass() == target) {
                return middle;
            }
            else if (target < planets[middle]->getMass()) {
                start = middle + 1;
            }
            else {
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target - planets[end]->getMass()) <= abs(target - planets[start]->getMass())) {
            return end;
        }
        else {
            return start;
        }
    }
    else if (searchBy == "radius") {
        // Catches the invalid input of negative radius
        if (target < 0) {
            throw invalid_argument("Invalid Value: radius cannot be negative!");
        }
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getRadius() == target) {
                return middle;
            }
            else if (target < planets[middle]->getRadius()) {
                start = middle + 1;
            }
            else {
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target - planets[end]->getRadius()) <= abs(target - planets[start]->getRadius())) {
            return end;
        }
        else {
            return start;
        }
    }
    else if (searchBy == "habitability") {
        // Catches the invalid input of negative habitability
        if (target < 0) {
            throw invalid_argument("Invalid Value: habitability cannot be negative!");
        }
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getHabitability() == target) {
                return middle;
            }
            else if (target < planets[middle]->getHabitability()) {
                start = middle + 1;
            }
            else {
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target - planets[end]->getHabitability()) <= abs(target - planets[start]->getHabitability())) {
            return end;
        }
        else {
            return start;
        }
    }
    else if (searchBy == "gravity") {
        // Catches the invalid input of negative gravity
        if (target < 0) {
            throw invalid_argument("Invalid Value: gravity cannot be negative!");
        }
        // Searches for the planet and returns the index
        int start = 0, end = planets.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (planets[middle]->getGravity() == target) {
                return middle;
            }
            else if (target < planets[middle]->getGravity()) {
                start = middle + 1;
            }
            else {
                end = middle - 1;
            }
        }
        // avoids out of bounds errors
        if (end < 0) { end = 0; }
        if (start > planets.size()-1) { start = planets.size()-1; }

        if (abs(target - planets[end]->getGravity()) <= abs(target - planets[start]->getGravity())) {
            return end;
        }
        else {
            return start;
        }
    }
    else
        throw invalid_argument("Mismatch: float is only used with search by distance, mass, radius, habitability, and gravity.");
}

vector<Planet*> searchNearest(vector<Planet*>& planets, const string& searchBy, const string& target_) {
    int planetIndex;

    // ensure the search parameter is valid and convert target type if necessary
    set<string> floatParameters = {"distance", "mass", "radius", "habitability", "gravity"};
    if (floatParameters.find(searchBy) != floatParameters.end()) {
        try {
            float target = stof(target_);
            // sort planets by appropriate parameter
            Sort(planets, searchBy);
            // locate nearest index
            planetIndex = binarySearch(planets, searchBy, target);
        }
        catch (const out_of_range&) {
            throw invalid_argument("Mismatch: input for this search parameter must be a float.");
        }
    }
    else if (searchBy == "alphabetical" or searchBy == "type") {
        string target = target_;
        // sort planets by appropriate parameter
        Sort(planets, searchBy);
        // locate nearest index
        planetIndex = binarySearch(planets, searchBy, target);
    }
    else {
        throw invalid_argument("Invalid Value to Search By: " + searchBy + "." );
    }

    // initialize vector of planet pointers
    vector<Planet*> nearest;
    // find ~10 planets before and after the nearest planet (if possible)
    for (int i = planetIndex - 5; i < planetIndex + 5; i++) {
        if (i >= 0 && i < planets.size()) {
            nearest.push_back(planets[i]);
        }
    }
    return nearest;
}

Planet* GetRandomPlanet(const vector<Planet*>& planets, mt19937& gen) {
    uniform_int_distribution<> dist(0, planets.size()-1);
    return planets.at(dist(gen));
}

void loadUsers (vector<User*>& users, const string& filename){
    // loads all existing user accounts from file
    string filepath = "../users/";
    filepath += filename;
    ifstream file(filepath);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream stream(line);

            string user;
            getline(stream, user, ':');

            string pass;
            getline(stream, pass, ':');

            User* User_ = new User(user, pass);
            users.push_back(User_);
        }
    }
    else {
        throw invalid_argument("Could not open file: " + filename + ".");
    }
}

string saveUser(vector<User*>& users, const string &filename, const string& username, const string& password){
    // creates a new user account
    string filepath = "../users/";
    filepath += filename;
    ofstream file(filepath, ios::app);

    // checks if there are duplicate accounts with exact same username

    for(User* user : users){
        if(user->getUsername() == username){
            return "Username already exists!";
        }
    }

    // username requirements
    // needs at least 5 characters
    if (username.length() < 5) {
        return "Username must be 5 or more characters!";
    }
    if (username.find_first_of(' ') != string::npos){
        return "Username must have no spaces!";
    }

    // password requirements
    // needs at least 5 characters, 1 special character defined as !@#$%^&*"
    if(password.length() < 5){
        return "Password must be 5 or more characters!";
    }
    if(password.find_first_of("!@#$%^&*") == string::npos){
        return "Password needs at least one special character!";
    }
    if (password.find_first_of(' ') != string::npos){
        return "Password must have no spaces!";
    }

    // writes account to file
    User* User_ = new User(username, hashPassword(password));
    users.push_back(User_);
    file << username << ":" << hashPassword(password) << ":";
    return "Account successfully created!";
}

string hashPassword(const string& password){
    // hashes password as a security measure
    return to_string(hash<string>{}(password));
}

bool loginUser(vector<User*>& users, const string& username, const string& password) {
    // logins user if account exists in file

    for (User *user: users) {
        if (user->getUsername() == username && user->getPassword() == hashPassword(password)) {
            user->loggedIn = true;
            return true;
        }
    }

    return false;
}

string favoritePlanet(User*& currentUser, const vector<Planet*>& planets, const string& username, const string& planetName){
    string name;
    ifstream inFile("../users/favorites/" + username + ".txt");

    while (getline(inFile, name)) {
        if (name == planetName)
            return "Planet has already been added!";
    }
    inFile.clear();
    inFile.seekg(0);

    string line;
    int counter = 0;
    while (getline(inFile, line)) {
        ++counter;
    }
    inFile.close();

    // favorites the planet based on input from user
    ofstream file("../users/favorites/" + username + ".txt", std::ios::app);

    if(!file.is_open()){
        throw runtime_error("Could not open file.");
    }

    if (counter >= 5) {
        file.close();
        return "Your favorites are full!";
    }
    else
        file << planetName << "\n";

    file.close();

    if (currentUser != nullptr) {
        int index = binarySearch(planets, "alphabetical", planetName);
        currentUser->favorites.push_back(planets[index]);
    }
    return  planetName + " has been added to your favorites!";
}

string unfavoritePlanet(vector<User*> users, const string& username, const string& planetName){

    // Removes favorite from user object's vector
    for (User* user : users) {
        for (int i = 0; i < user->favorites.size(); i++) {
            if (user->favorites[i]->getName() == planetName) {
                user->favorites.erase(user->favorites.begin() + i);
                i--;
                break;
            }
        }
    }

    // Removes favorite from file
    ifstream file("../users/favorites/" + username + ".txt", std::ios::app);

    if(!file.is_open()){
        throw runtime_error("Could not open file.");
    }

    vector<string> lines;
    string line;

    while(getline(file, line)){
        if(line != planetName){
            lines.push_back(line);
        }
    }
    file.close();

    ofstream write_file("../users/favorites/" + username + ".txt", std::ios::trunc);

    if(!write_file.is_open()){
        throw runtime_error("Could not open file.");
    }

    for(const auto& line : lines){
        write_file << line << "\n";
    }
    write_file.close();

    return "Successfully removed " + planetName;
}

string loadFavorites(vector<User*>& users, vector<Planet*>& planets, const string& username){
    // loads all favorites from the user's dedicated file
    ifstream file("../users/favorites/" + username + ".txt");
    vector<string> favorites;

    if(!file.is_open()){
        return "You don't have any favorites saved.";
    }

    string line;
    while(getline(file, line)){
        favorites.push_back(line);
    }

    User* currentUser = nullptr;
    for (User* user : users) {
        if (user->getUsername() == username) {
            currentUser = user;
            break;
        }
    }
    findFavorites(currentUser, planets, favorites);

    return "Successfully loaded favorites!";
}

void findFavorites(User*& currentUser, vector<Planet*>& planets, vector<string>& favorites){
    // finds the favorites based on name from the user's file
    Sort(planets, "alphabetical");
    for (const string& favName : favorites) {
        if (currentUser != nullptr) {
            int index = binarySearch(planets, "alphabetical", favName);
            currentUser->favorites.push_back(planets[index]);
        }
    }
}

void clearFile(){
    // for testing purposes
    ofstream file("../users/accounts.txt", std::ios::trunc);
    if(!file.is_open()){
        throw runtime_error("Could not open file.");
    }

    file.close();
}

void clearFavFile(){
    // for testing purposes
    ofstream file("../users/favorites/test_account.txt", std::ios::trunc);
    if(!file.is_open()){
        throw runtime_error("Could not open file.");
    }

    file.close();
}