// src/FareCalculator.cpp
#include "FareCalculator.h"
#include <cmath>

// Constants
const double EARTH_RADIUS_KM = 6371.0; // Radius of the Earth in kilometers

// Converts degrees to radians.
double deg2rad(double degrees) {
    return degrees * M_PI / 180.0;
}

// Implements the Haversine formula to calculate the distance between two geographic points.
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c; // Distance in kilometers
}

// Calculates the fare based on the distance.
// Example: $1.5 per kilometer.
double calculateFare(double distance) {
    return distance * 1.5;
}

