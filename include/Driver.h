// include/Driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <set>
#include <iostream> // Included to use std::cout

class Driver {
public:
    int driverID;
    std::string name;
    double currentLat, currentLon;
    bool available;
    std::set<int> activeRequests; // Active ride requests

    Driver(int id, const std::string& driverName, double initialLat, double initialLon);

    void updateLocation(double lat, double lon);
    void notifyOfRequest(int requestID);
    void removeRequestNotification(int requestID);
};

#endif // DRIVER_H

