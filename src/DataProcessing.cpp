#include "DataProcessing.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// function implementations will be placed here

void inputParser(vector<Planet*>& planets, const string& filename) {
        string filepath = "../";
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

                string distance;
                getline(stream, distance, ',');

                string mass;
                getline(stream, mass, ',');

                string date;
                getline(stream, date, ',');

                Planet *planet = new Planet(name, stof(distance), stof(mass), stoi(date));
                planets.push_back(planet);
            }
        }
    else {
        throw invalid_argument("Could not open file: " + filename + ".");
    }
}

void Sort(vector<Planet*>& planets, const string& sortBy){
    // Distance descending
    if(sortBy == "distance") {
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getDistance() > planet2->getDistance();
        });
    }
    // Alphabetical descending
    else if (sortBy == "alphabetical"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getName() < planet2->getName();
        });
    }
    // Mass descending
    else if (sortBy == "mass"){
        sort(planets.begin(), planets.end(), [](Planet *planet1, Planet *planet2) {
            return planet1->getMass() > planet2->getMass();
        });
    }
    else {
        throw invalid_argument("Invalid Value to Sort By: " + sortBy + "." );
    }
}

int binarySearch(const vector<Planet*>& planets, const float& target) {
    // Catches the invalid input of negative distance
    if(target < 0){
        throw invalid_argument("Invalid Value: distance cannot be negative!");
    }

    // Searches for the planet and returns the index
    int start = 0, end = planets.size() - 1;
    while (start < end) {
        int middle = start + (end - start) / 2;

        if (planets[middle]->getDistance() == target) {
            return middle;
        }

        else if (target < planets[middle]->getDistance()) {
            start = middle + 1;
            middle += (end - middle)/2;
        }

        else { //planets[middle]->getTemperature() < target
            end = middle - 1;
            middle -= (end - start)/2;
        }
    }
    if (abs(target - planets[end]->getDistance()) <= abs(target - planets[start]->getDistance())) {
        return end;
    }
    else {
        return start;
    }
}
