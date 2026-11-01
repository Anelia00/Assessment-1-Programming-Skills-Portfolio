// Estimates the CO2 emissions of a car journey from distance and fuel type.

#include <iostream>
#include <iomanip>
using namespace std;

// This asks the user how far they have travelled
double getDistance() {
    double distance;

    cout << "\nEnter the distance of your journey in miles: ";
    cin >> distance;

    return distance;
}

// This lets the user choose their car's fuel type
int getFuelType() {
    int fuel;

    cout << "\nWhat type of fuel does your car use?" << endl;
    cout << "1. Petrol" << endl;
    cout << "2. Diesel" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> fuel;

    return fuel;
}

// This calculate CO2 emissions based on distance and fuel
double calculateCO2(double distance, int fuel) {

    // These are fixed values provided in the assessment
    const double fuelConsumption = 9.66;
    const double petrolEmission = 2.31;
    const double dieselEmission = 2.68;

    // This works out how many litres of fuel were used
    double fuelUsed = (distance * fuelConsumption) / 100;
    double emissions = 0;

    // This uses the correct emission value for the fuel type
    if (fuel == 1) {
        emissions = fuelUsed * petrolEmission;
    }
    else if (fuel == 2) {
        emissions = fuelUsed * dieselEmission;
    }

    return emissions;
}

int main() {

    // This displays the program title and welcome message
    cout << "==================================" << endl;
    cout << "       CO2 Emissions Calculator   " << endl;
    cout << "==================================" << endl;

    cout << "\nWelcome to the CO2 Calculator!" << endl;
    cout << "This program estimates the CO2 emissions" << endl;
    cout << "produced during your car journey." << endl;

    // This gets the journey information from the user
    double distance = getDistance();
    int fuel = getFuelType();

    // This checks for invalid distance or fuel selection
    if (distance < 0 || (fuel != 1 && fuel != 2)) {
        cout << "\nInvalid input! Please restart the program." << endl;
        return 1;
    }

    // This calculates the estimated CO2 emissions
    cout << "\nCalculating your journey emissions..." << endl;
    double result = calculateCO2(distance, fuel);

    // This displays the results to the user
    cout << fixed << setprecision(2);
    cout << "\n========== YOUR RESULTS ==========" << endl;
    cout << "Distance travelled: " << distance << " miles" << endl;

    if (fuel == 1) {
        cout << "Fuel type: Petrol" << endl;
    }
    else {
        cout << "Fuel type: Diesel" << endl;
    }

    cout << "Estimated CO2 emissions: "
         << result << " kg CO2" << endl;

    cout << "\nThank you for using the CO2 Calculator!" << endl;

    return 0;
}
