// include/RTree.h
#ifndef RTREE_H
#define RTREE_H

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include "Driver.h"
#include <vector>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

// Type definitions for Boost.Geometry R-Tree
typedef bg::model::point<double, 2, bg::cs::geographic<bg::degree>> Point;
typedef std::pair<Point, int> RTreeValue; // Pair of point and driverID

class RTree {
public:
    bgi::rtree<RTreeValue, bgi::quadratic<16>> rtree;

    void insertDriver(const Driver& driver);
    void removeDriver(const Driver& driver);
    std::vector<Driver*> findNearestDrivers(double lat, double lon, size_t count, const std::vector<Driver>& driversList);
};

#endif // RTREE_H

