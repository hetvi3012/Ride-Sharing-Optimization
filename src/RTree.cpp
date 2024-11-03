// src/RTree.cpp
#include "RTree.h"
#include <algorithm>

// Insert a driver into the R-Tree
void RTree::insertDriver(const Driver& driver) {
    Point pt(driver.currentLat, driver.currentLon);
    rtree.insert(std::make_pair(pt, driver.driverID));
}

// Remove a driver from the R-Tree
void RTree::removeDriver(const Driver& driver) {
    Point pt(driver.currentLat, driver.currentLon);
    rtree.remove(std::make_pair(pt, driver.driverID));
}

// Find the nearest drivers to a given location
std::vector<Driver*> RTree::findNearestDrivers(double lat, double lon, size_t count, const std::vector<Driver>& driversList) {
    Point queryPoint(lat, lon);
    std::vector<RTreeValue> result_n;
    rtree.query(bgi::nearest(queryPoint, count), std::back_inserter(result_n));

    std::vector<Driver*> nearestDrivers;
    for(auto &val : result_n) {
        for(auto &driver : driversList) {
            if(driver.driverID == val.second && driver.available) {
                nearestDrivers.push_back(const_cast<Driver*>(&driver)); // Assuming driversList won't change
                break;
            }
        }
    }

    return nearestDrivers;
}

