#pragma once
#include "Planet.h"
#include <vector>
#include <random>
#include <unordered_map>
using namespace std;

// user class
class User {
    string _username;
    string _password;

public:
    vector<Planet*> favorites;
    bool loggedIn;
    // Constructor
    User(string username, string password){_username = username; _password = password; loggedIn = false;}
    // Get functions
    string getUsername(){return _username;}
    string getPassword(){return _password;}
};

// function definitions will be stored here for all backend processes
void inputParser(vector<Planet*>& planets, const string& filename);
void Sort(vector<Planet*>& planets, const string& sortBy);

// search functions
int binarySearch(const vector<Planet*>& planets, const string& searchBy, const string& target);
int binarySearch(const vector<Planet*>& planets, const string& searchBy, const float& target);
vector<Planet*> searchNearest(vector<Planet*>& planets, const string& searchBy, const string& target);
Planet* GetRandomPlanet(const vector<Planet*>& planets, mt19937& gen);

// login functions
void loadUsers (vector<User*>& users, const string& filename);
string saveUser(vector<User*>& users, const string &filename, const string& username, const string& password);
string hashPassword(const string& password);
string loginUser(vector<User*>& users, const string& username, const string& password);

// favorite functions
string favoritePlanet(const string& username, const string& planetName);
string unfavoritePlanet(vector<User*> users, const string& username, const string& planetName);
string loadFavorites(vector<User*>& users, vector<Planet*>& planets,const string& username);
void findFavorites(vector<User*>& users, vector<Planet*>& planets, vector<string>& favorites);

// utility
void clearFile();
void clearFavFile();
