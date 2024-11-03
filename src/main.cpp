// src/main.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include "AdminLogSplayTree.h"
#include "PassengerLogSplayTree.h"
#include "Driver.h"
#include "Passenger.h"
#include "RideRequest.h"
#include "FareCalculator.h"
#include "RTree.h"

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

// Struct for Locations
struct Location {
    int id;
    std::string name;
    double lat;
    double lon;
};

// Global Variables
std::vector<Location> locations;
std::vector<Driver> drivers;
std::vector<Passenger> passengers;
std::vector<RideRequest> rideRequests;
int rideCounter = 1;

// Splay Trees
AdminLogSplayTree adminLogTree;
PassengerLogSplayTree passengerLogTree;

// R-Tree instance
RTree rtree;

// Log Counters
int passengerLogCounter = 1001; // Starting log ID for Passenger Logs
int adminLogCounter = 1;         // Starting log ID for Admin Logs

// Function Declarations
void initializeLocations();
void initializeDrivers();
void initializePassengers();
void passengerMode();
void driverInterface();
void listLocations();
void listDrivers();
void listPassengers();
void adminInterface();
void passengerInterface();
void notifyPassenger(int rideID, int driverID, const std::string& driverName);

// Main Function
int main() {
    // Initialize Data
    initializeLocations();
    initializeDrivers();
    initializePassengers();

    // Insert all drivers into the R-Tree initially
    for(auto &driver : drivers) {
        rtree.insertDriver(driver);
    }

    int choice;
    bool running = true;

    while(running) {
        std::cout << "\n=== Ride-Sharing Optimization System ===\n";
        std::cout << "1. Admin Interface\n";
        std::cout << "2. Passenger Interface\n";
        std::cout << "3. Driver Interface\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if(choice == 1) {
            adminInterface();
        }
        else if(choice == 2) {
            passengerInterface();
        }
        else if(choice == 3) {
            driverInterface();
        }
        else if(choice == 4) {
            std::cout << "Exiting the system. Goodbye!\n";
            running = false;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Function Definitions

// Initialize predefined locations
void initializeLocations() {
    locations = {
        {1, "Downtown", 34.052235, -118.243683},
        {2, "Hollywood", 34.092809, -118.328661},
        {3, "Santa Monica", 34.019454, -118.491191},
        {4, "Beverly Hills", 34.073620, -118.400356},
        {5, "Culver City", 34.021122, -118.396466},
        {6, "Pasadena", 34.147785, -118.144516},
        {7, "Long Beach", 33.770050, -118.193741},
        {8, "Westwood", 34.063344, -118.445238},
        {9, "Marina Del Rey", 33.980600, -118.454545},
        {10, "Echo Park", 34.078655, -118.259079},
        {11, "Silver Lake", 34.081222, -118.285117},
        {12, "Koreatown", 34.073620, -118.240340},
        {13, "Glendale", 34.142508, -118.255075},
        {14, "West Hollywood", 34.090009, -118.361740},
        {15, "Echo Park Lake", 34.0794, -118.2605}
    };
}

// Initialize drivers
void initializeDrivers() {
    // Driver(int id, string name, double initialLat, double initialLon)
    drivers.emplace_back(1, "Alice", 34.052235, -118.243683);      // Downtown
    drivers.emplace_back(2, "Bob", 34.092809, -118.328661);        // Hollywood
    drivers.emplace_back(3, "Charlie", 34.019454, -118.491191);    // Santa Monica
    drivers.emplace_back(4, "Diana", 34.073620, -118.400356);      // Beverly Hills
    drivers.emplace_back(5, "Ethan", 34.021122, -118.396466);      // Culver City
}

// Initialize passengers
void initializePassengers() {
    // Passenger(int id, string name)
    passengers.emplace_back(1, "Passenger1");
    passengers.emplace_back(2, "Passenger2");
    passengers.emplace_back(3, "Passenger3");
    passengers.emplace_back(4, "Passenger4");
    passengers.emplace_back(5, "Passenger5");
    passengers.emplace_back(6, "Passenger6");
    passengers.emplace_back(7, "Passenger7");
    passengers.emplace_back(8, "Passenger8");
    passengers.emplace_back(9, "Passenger9");
    passengers.emplace_back(10, "Passenger10");
    // Add more passengers as needed
}

// Admin Interface
void adminInterface() {
    int choice;
    while (true) {
        std::cout << "\n=== Admin Interface ===\n";
        std::cout << "1. Add Admin Log\n";
        std::cout << "2. Search Admin Log\n";
        std::cout << "3. Delete Admin Log\n";
        std::cout << "4. Display All Admin Logs\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if(choice == 1) {
            AdminLog log;
            std::cout << "Enter Log ID: ";
            std::cin >> log.logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Timestamp (e.g., 2024-10-22 10:00:00): ";
            std::getline(std::cin, log.timestamp);
            std::cout << "Enter Category (Driver/Passenger/System): ";
            std::getline(std::cin, log.category);
            std::cout << "Enter Driver ID (-1 if not applicable): ";
            std::cin >> log.driverID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Details: ";
            std::getline(std::cin, log.details);
            adminLogTree.insertLog(log);
            std::cout << "Admin log added successfully.\n";
        }
        else if(choice == 2) {
            int logID;
            std::cout << "Enter Log ID to search: ";
            std::cin >> logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            AdminLog* log = adminLogTree.searchLog(logID);
            if(log) {
                std::cout << "Log Found:\n";
                std::cout << "Log ID: " << log->logID 
                          << " | Timestamp: " << log->timestamp 
                          << " | Category: " << log->category 
                          << " | Driver ID: " << log->driverID
                          << " | Details: " << log->details << "\n";
            }
            else {
                std::cout << "Log ID " << logID << " not found.\n";
            }
        }
        else if(choice == 3) {
            int logID;
            std::cout << "Enter Log ID to delete: ";
            std::cin >> logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            adminLogTree.deleteLog(logID);
            std::cout << "Admin log deletion attempted.\n";
        }
        else if(choice == 4) {
            std::cout << "\n=== All Admin Logs ===\n";
            adminLogTree.displayLogs();
        }
        else if(choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Passenger Interface
void passengerInterface() {
    int choice;
    while (true) {
        std::cout << "\n=== Passenger Interface ===\n";
        std::cout << "1. Add Passenger Log\n";
        std::cout << "2. Search Passenger Log\n";
        std::cout << "3. Delete Passenger Log\n";
        std::cout << "4. Display All Passenger Logs\n";
        std::cout << "5. Request a Ride\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if(choice == 1) {
            PassengerLog log;
            std::cout << "Enter Log ID: ";
            std::cin >> log.logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Passenger ID: ";
            std::cin >> log.passengerID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Timestamp (e.g., 2024-10-22 10:00:00): ";
            std::getline(std::cin, log.timestamp);
            std::cout << "Enter Action Type (RideBooking/Payment/ProfileUpdate/SecurityAction): ";
            std::getline(std::cin, log.actionType);
            std::cout << "Enter Driver ID (-1 if not applicable): ";
            std::cin >> log.driverID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Details: ";
            std::getline(std::cin, log.details);
            passengerLogTree.insertLog(log);
            std::cout << "Passenger log added successfully.\n";
        }
        else if(choice == 2) {
            int logID;
            std::cout << "Enter Log ID to search: ";
            std::cin >> logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            PassengerLog* log = passengerLogTree.searchLog(logID);
            if(log) {
                std::cout << "Log Found:\n";
                std::cout << "Log ID: " << log->logID 
                          << " | Passenger ID: " << log->passengerID 
                          << " | Timestamp: " << log->timestamp 
                          << " | Action: " << log->actionType 
                          << " | Driver ID: " << log->driverID
                          << " | Details: " << log->details << "\n";
            }
            else {
                std::cout << "Log ID " << logID << " not found.\n";
            }
        }
        else if(choice == 3) {
            int logID;
            std::cout << "Enter Log ID to delete: ";
            std::cin >> logID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            passengerLogTree.deleteLog(logID);
            std::cout << "Passenger log deletion attempted.\n";
        }
        else if(choice == 4) {
            std::cout << "\n=== All Passenger Logs ===\n";
            passengerLogTree.displayLogs();
        }
        else if(choice == 5) {
            passengerMode();
        }
        else if(choice == 6) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Passenger Mode: Request a Ride
void passengerMode() {
    int passengerID;
    std::cout << "\nEnter Passenger ID (1-" << passengers.size() << "): ";
    std::cin >> passengerID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Validate Passenger ID
    if(passengerID < 1 || passengerID > static_cast<int>(passengers.size())) {
        std::cout << "Invalid Passenger ID.\n";
        return;
    }

    // Display Locations
    listLocations();

    int pickupLocID, dropoffLocID;
    std::cout << "Enter Pickup Location ID: ";
    std::cin >> pickupLocID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Drop-off Location ID: ";
    std::cin >> dropoffLocID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validate Location IDs
    if(pickupLocID < 1 || pickupLocID > static_cast<int>(locations.size()) ||
       dropoffLocID < 1 || dropoffLocID > static_cast<int>(locations.size())) {
        std::cout << "Invalid Location ID(s).\n";
        return;
    }

    // Get Pickup and Drop-off Coordinates
    double pickupLat, pickupLon, dropoffLat, dropoffLon;
    for(auto &loc : locations) {
        if(loc.id == pickupLocID) {
            pickupLat = loc.lat;
            pickupLon = loc.lon;
        }
        if(loc.id == dropoffLocID) {
            dropoffLat = loc.lat;
            dropoffLon = loc.lon;
        }
    }

    // Calculate Fare
    double distance = calculateDistance(pickupLat, pickupLon, dropoffLat, dropoffLon);
    double fare = calculateFare(distance);
    std::cout << "Calculated Fare: $" << fare << "\n";

    // Create RideRequest
    RideRequest newRequest = {rideCounter, passengerID, pickupLat, pickupLon, dropoffLat, dropoffLon, fare, false, -1};
    rideRequests.push_back(newRequest);

    // Log the ride booking with unique logID
    PassengerLog passengerLog = {passengerLogCounter++, passengerID, "2024-10-22 10:00:00", "RideBooking", -1, "Booked Ride ID " + std::to_string(rideCounter)};
    passengerLogTree.insertLog(passengerLog);

    // Find Top 3 Closest Drivers using RTree
    std::vector<Driver*> nearestDrivers = rtree.findNearestDrivers(pickupLat, pickupLon, 3, drivers);

    // Filter available drivers
    std::vector<Driver*> availableDrivers;
    for(auto &driver : nearestDrivers) {
        if(driver->available) {
            availableDrivers.push_back(driver);
        }
    }

    size_t topN = availableDrivers.size();
    if(topN == 0) {
        std::cout << "No available drivers nearby. Please try again later.\n";
        return;
    }

    // Notify Top 3 Drivers
    std::cout << "\nNotifying Top " << topN << " Drivers...\n";
    for(auto &driver : availableDrivers) {
        driver->notifyOfRequest(newRequest.requestID);
    }

    std::cout << "Ride request sent to top " << topN << " drivers. Waiting for acceptance...\n";

    // In a real system, this would be event-driven.
    // For simulation, prompt the user to switch to driver interface and accept the ride.

    std::cout << "Press Enter to return to Main Menu and proceed to Driver Interface to accept the ride.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // After returning from driver interface, check if the ride has been accepted
    bool rideAssigned = false;
    int assignedDriverID = -1;
    for(auto &ride : rideRequests) {
        if(ride.requestID == newRequest.requestID && ride.isAccepted) {
            assignedDriverID = ride.driverID;
            rideAssigned = true;
            break;
        }
    }

    if(rideAssigned) {
        // Find driver name
        std::string driverName = "N/A";
        for(auto &driver : drivers) {
            if(driver.driverID == assignedDriverID) {
                driverName = driver.name;
                break;
            }
        }
        std::cout << "Ride ID " << newRequest.requestID << " has been accepted by Driver " << driverName 
                  << " (Driver ID: " << assignedDriverID << ").\n";
        notifyPassenger(newRequest.requestID, assignedDriverID, driverName);
    }
    else {
        std::cout << "No driver has accepted the ride yet.\n";
    }

    rideCounter++; // Increment ride counter for next ride
}

// Driver Interface
void driverInterface() {
    int driverID;
    std::cout << "\nEnter Driver ID (1-" << drivers.size() << "): ";
    std::cin >> driverID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Validate Driver ID
    if(driverID < 1 || driverID > static_cast<int>(drivers.size())) {
        std::cout << "Invalid Driver ID.\n";
        return;
    }

    auto driverIt = std::find_if(drivers.begin(), drivers.end(),
                                 [driverID](const Driver& d) { return d.driverID == driverID; });

    if(driverIt == drivers.end()) {
        std::cout << "Driver not found.\n";
        return;
    }

    Driver& driver = *driverIt;

    if(driver.activeRequests.empty()) {
        std::cout << "No active ride requests for you.\n";
        return;
    }

    std::cout << "\n=== Driver Interface ===\n";
    std::cout << "Active Ride Requests:\n";
    for(auto &reqID : driver.activeRequests) {
        auto reqIt = std::find_if(rideRequests.begin(), rideRequests.end(),
                                  [&](const RideRequest& r) { return r.requestID == reqID; });
        if(reqIt != rideRequests.end() && !reqIt->isAccepted) { // Only show not accepted rides
            std::cout << "Ride ID: " << reqIt->requestID 
                      << " | Passenger ID: " << reqIt->passengerID
                      << " | Pickup: (" << reqIt->pickupLat << ", " << reqIt->pickupLon << ")"
                      << " | Drop-off: (" << reqIt->dropoffLat << ", " << reqIt->dropoffLon << ")"
                      << " | Fare: $" << reqIt->fare << "\n";
        }
    }

    int requestID;
    std::cout << "Enter Ride Request ID to accept (0 to decline): ";
    std::cin >> requestID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(requestID == 0) {
        std::cout << "Declined to accept any ride.\n";
        return;
    }

    auto reqIt = std::find_if(rideRequests.begin(), rideRequests.end(),
                              [&](const RideRequest& r) { return r.requestID == requestID; });

    if(reqIt == rideRequests.end()) {
        std::cout << "Ride request not found.\n";
        return;
    }

    if(reqIt->isAccepted) {
        std::cout << "Ride request is already accepted by another driver.\n";
        return;
    }

    // Assign the ride
    reqIt->isAccepted = true;
    reqIt->driverID = driverID;
    driver.available = false;

    // Consider the ride instantly completed
    // Update driver's location to drop-off
    rtree.removeDriver(driver);
    driver.updateLocation(reqIt->dropoffLat, reqIt->dropoffLon);
    rtree.insertDriver(driver);

    // Log the ride acceptance with unique logID
    AdminLog adminLog = {adminLogCounter++, "2024-10-22 10:30:00", "Driver", driverID, "Driver accepted Ride ID " + std::to_string(requestID)};
    adminLogTree.insertLog(adminLog);

    // Log the ride assignment for the passenger with unique logID
    PassengerLog passengerLog = {passengerLogCounter++, reqIt->passengerID, "2024-10-22 10:30:00", "RideAssignment", driverID, "Ride ID " + std::to_string(requestID) + " assigned to Driver ID " + std::to_string(driverID)};
    passengerLogTree.insertLog(passengerLog);

    // Notify passenger
    notifyPassenger(reqIt->requestID, driverID, driver.name);

    // Remove the ride from driver's active requests
    driver.activeRequests.erase(requestID);

    // Remove the ride from other drivers' active requests
    for(auto &d : drivers) {
        if(d.driverID != driverID) {
            d.removeRequestNotification(requestID);
        }
    }

    // Set driver as available since ride is instantly completed
    driver.available = true;

    std::cout << "Ride ID " << reqIt->requestID << " accepted and considered completed by you.\n";
}

// Function to notify passenger about the assigned driver
void notifyPassenger(int rideID, int driverID, const std::string& driverName) {
    auto rideIt = std::find_if(rideRequests.begin(), rideRequests.end(),
                               [&](const RideRequest& r) { return r.requestID == rideID; });

    if(rideIt != rideRequests.end()) {
        int passengerID = rideIt->passengerID;
        auto passengerIt = std::find_if(passengers.begin(), passengers.end(),
                                       [&](const Passenger& p) { return p.passengerID == passengerID; });
        if(passengerIt != passengers.end()) {
            std::cout << "Passenger " << passengerIt->name << " has been notified about Driver " 
                      << driverName << " (Driver ID: " << driverID << ").\n";
        }
    }
}

// List All Locations
void listLocations() {
    std::cout << "\nAvailable Locations:\n";
    std::cout << "ID\tName\t\t\tLatitude\tLongitude\n";
    for(auto &loc : locations) {
        std::cout << loc.id << "\t" << loc.name << "\t\t" << loc.lat << "\t" << loc.lon << "\n";
    }
}

// List All Drivers
void listDrivers() {
    std::cout << "\nList of Drivers:\n";
    std::cout << "Driver ID\tName\t\tLatitude\tLongitude\tAvailability\n";
    for(auto &driver : drivers) {
        std::cout << driver.driverID << "\t\t" << driver.name << "\t\t" 
                  << driver.currentLat << "\t" << driver.currentLon << "\t\t" 
                  << (driver.available ? "Available" : "Unavailable") << "\n";
    }
}

// List All Passengers
void listPassengers() {
    std::cout << "\nList of Passengers:\n";
    std::cout << "Passenger ID\tName\n";
    for(auto &passenger : passengers) {
        std::cout << passenger.passengerID << "\t\t" << passenger.name << "\n";
    }
}

