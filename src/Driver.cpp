// src/Driver.cpp
#include "Driver.h"

// Constructor
Driver::Driver(int id, const std::string& driverName, double initialLat, double initialLon)
    : driverID(id), name(driverName), currentLat(initialLat), currentLon(initialLon), available(true) {}

// Update location
void Driver::updateLocation(double lat, double lon) {
    currentLat = lat;
    currentLon = lon;
}

// Notify of ride request
void Driver::notifyOfRequest(int requestID) {
    activeRequests.insert(requestID);
    std::cout << "Driver " << name << " notified of Ride Request " << requestID << ".\n";
}

// Remove ride request notification
void Driver::removeRequestNotification(int requestID) {
    if(activeRequests.erase(requestID)) {
        std::cout << "Driver " << name << " removed notification for Ride Request " << requestID << ".\n";
    }
}

