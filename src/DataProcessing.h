#pragma once
#include "Planet.h"
#include <vector>
using namespace std;

// function definitions will be stored here for all backend processes
void inputParser(vector<Planet*>& planets, const string& filename);
void Sort(vector<Planet*>& planets, const string& sortBy);
int binarySearch(const vector<Planet*>& planets, const float& target);
