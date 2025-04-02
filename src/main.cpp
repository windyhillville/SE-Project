#include <iostream>
#include "Planet.h"
#include "DataProcessing.h"
#include <vector>
using namespace std;

int main () {

    vector<Planet*> planets;
    // placeholder csv file until we get the entire dataset
    inputParser(planets, "ExoPlanets.csv");
    // call to create the user interface will go here

    return 0;
}