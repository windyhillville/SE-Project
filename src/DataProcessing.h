#pragma once
#include "Planet.h"
#include <vector>
#include <random>
using namespace std;

// function definitions will be stored here for all backend processes
void inputParser(vector<Planet*>& planets, const string& filename);
void Sort(vector<Planet*>& planets, const string& sortBy);
int binarySearch(const vector<Planet*>& planets, const string& searchBy, const string& target);
int binarySearch(const vector<Planet*>& planets, const string& searchBy, const float& target);
vector<Planet*> searchNearest(vector<Planet*>& planets, const string& searchBy, const string& target);
Planet* GetRandomPlanet(const vector<Planet*>& planets, mt19937& gen);